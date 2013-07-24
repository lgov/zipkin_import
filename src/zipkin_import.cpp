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

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <iostream>

#include "zipkin_import.h"

namespace po = boost::program_options;

using std::cout;
using std::string;
using std::vector;

int main(int argc, char **argv)
{
    bool use_scribe;
    std::string csv_file, host;

    po::options_description desc("Allowed options");

    desc.add_options()
    ("help", "produce help message")
    ("scribe", "connect to a scribe server")
/*    ("zipkin", "connect to a zipkin collector") */
    ("csv", po::value< vector<string> >(), "import a .csv file")
    ("host", po::value< vector<string> >(), "hostname")
/*    ("-f", "wait for additional data to arrive") */
    ;

    /* the unnamed argument is host[:post] */
    po::positional_options_description p;
    p.add("host", 1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
              options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << std::endl;
        return 1;
    }

    use_scribe = vm.count("scribe") > 0;

    if (vm.count("csv")) {
        vector<string> csv_files = vm["csv"].as< vector<string> >();
        csv_file = csv_files[0];
        cout << "csv: " << csv_file << std::endl;
    }
    if (vm.count("host")) {
        vector<string> hosts = vm["host"].as< vector<string> >();
        host = hosts[0];
        cout << "host: " << host << std::endl;
    }

    SendToScribeServer sts;
    sts.init(host);

    return 0;
}
