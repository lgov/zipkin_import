/* Copyright 2013 Lieven Govaerts
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <exception>

#include <boost/tokenizer.hpp>
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "zipkin_import.h"

using namespace boost::algorithm;

using boost::tokenizer;
using boost::escaped_list_separator;
using boost::make_shared;
using std::cout;
using std::endl;
using std::ostream_iterator;

void CSVImporter::process_new()
{
    csv_stream.open(csv_path.c_str());
    if (!csv_stream.is_open())
        throw std::exception();

    /* Use ; as separator between columns. */
    escaped_list_separator<char> els('\\', ';', '\"');
    typedef tokenizer<escaped_list_separator<char> > Tokenizer;

    vector<string> vec;
    string line;

    while (getline(csv_stream,line)) {

        Tokenizer tok(line, els);
        vec.assign(tok.begin(),tok.end());

        /* ignore empty lines */
        if (!vec.size())
            continue;

        string type = vec[0];

        /* ignore comment lines */
        if (type[0] == '#')
            continue;

        if (type == "endpoint") {
            if (vec.size() != 5)
                continue;

            shared_ptr<Endpoint> ep = make_shared<Endpoint>();
            string epname = vec[1];
            ep->__set_service_name(vec[2]);
//            ep->__set_ipv4(read_host_ip(vec[3]));
            ep->__set_port(boost::lexical_cast<int>(vec[4]));

            cout << "Endpoint: " << epname << ", " << ep->service_name << ", "
                                 << (uint16_t)ep->port <<  endl;
        }
    }
}
