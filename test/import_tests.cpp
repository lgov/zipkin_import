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

// #define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE csv_import_tests
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>
using namespace boost::unit_test;
using std::cout;
#include "zipkin_import.h"

BOOST_AUTO_TEST_SUITE(csv_import_suite)

BOOST_AUTO_TEST_CASE(basic_import_csv_test)
{
    CSVImporter csv_importer("test/endpoints.csv");

    csv_importer.process_new();
}

BOOST_AUTO_TEST_CASE(import_csv_spans_test)
{
    CSVImporter csv_importer("test/spans.csv");

    Importer::span_range_t spans = csv_importer.process_new();

    shared_ptr<Span> s;
    BOOST_FOREACH(s, spans) {
        cout << "boost span name: " << s->name << "\n";
    }

}

BOOST_AUTO_TEST_CASE(import_csv_annotations_test)
{
    CSVImporter csv_importer("test/annotations.csv");

    csv_importer.process_new();
}

BOOST_AUTO_TEST_SUITE_END()