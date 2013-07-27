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

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <boost/foreach.hpp>

#include "zipkin_import.h"

using namespace boost::algorithm;

using std::cout;
using std::endl;
using std::ostream_iterator;

shared_ptr<Endpoint>
CSVImporter::read_endpoint(string& ep_name, vector<string> vec)
{
    shared_ptr<Endpoint> ep = make_shared<Endpoint>();

    if (vec.size() != 5)
        throw InvalidLineException();

    ep_name = vec[1];
    ep->__set_service_name(vec[2]);
    //            ep->__set_ipv4(read_host_ip(vec[3]));
    ep->__set_port(boost::lexical_cast<int>(vec[4]));

    return ep;
}

shared_ptr<Span>
CSVImporter::read_span(vector<string> vec)
{
    shared_ptr<Span> span = make_shared<Span>();

    if (vec.size() != 5)
        throw InvalidLineException();

    span->__set_trace_id(boost::lexical_cast<int64_t>(vec[1]));
    span->__set_parent_id(boost::lexical_cast<int64_t>(vec[2]));
    int64_t span_id = boost::lexical_cast<int64_t>(vec[3]);
    span->__set_id(span_id);
    span->__set_name(vec[4]);

    return span;
}

void CSVImporter::read_annotation(vector<string> vec)
{
    if (vec.size() != 4)
        throw InvalidLineException();

    string ep_name = vec[1];
    int64_t span_id = boost::lexical_cast<int64_t>(vec[2]);

    shared_ptr<Endpoint> ep = endpoints[ep_name];
    shared_ptr<Span> span = spans[span_id];

    if (!ep || !span)
        throw InvalidLineException();

    Annotation ann;

    ann.__set_host(*ep);
    ann.__set_value(vec[3]);
    ann.__isset.value = true;
/*
   ann.timestamp = now + 500000;
   ann.__set_duration(10000);
 */
    span->annotations.push_back(ann);
}

Importer::span_range_t CSVImporter::process_new()
{
    csv_stream.open(csv_path.c_str());
    if (!csv_stream.is_open())
        throw std::exception();

    /* Use ; as separator between columns. */

    vector<string> vec;
    string line;
    const escaped_list_separator<char> els('\\', ';', '\"');

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

        try {
            if (type == "endpoint") {
                string ep_name;
                shared_ptr<Endpoint> ep = read_endpoint(ep_name, vec);

                endpoints[ep_name] = ep;
            } else if (type == "span") {
                shared_ptr<Span> span = read_span(vec);

                spans[span->id] = span;
            } else if (type == "annotation") {
                read_annotation(vec);
            }
        } catch (InvalidLineException) {
            /* Silently ignore invalid lines */
        }
    }

    using namespace boost::adaptors;
    span_map_range_t range = boost::make_iterator_range(spans.begin(), spans.end());

    return spans | map_values;
}
