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


#ifndef ZIPKIN_IMPORT_H
#define ZIPKIN_IMPORT_H

#include <sys/socket.h>
#include <arpa/inet.h>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include "thrift/Scribe.h"
#include "thrift/zipkinCore_types.h"
#include "thrift/zipkinCore_constants.h"

#include <boost/tokenizer.hpp>
#include <boost/unordered_map.hpp>
#include <boost/make_shared.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/adaptor/map.hpp>

#include <fstream>
#include <exception>

using namespace apache::thrift;
using apache::thrift::protocol::TProtocol;
using apache::thrift::transport::TTransport;
using apache::thrift::transport::TSocket;
using apache::thrift::transport::TMemoryBuffer;

using std::ifstream;
using std::vector;
using std::string;
using boost::shared_ptr;
using boost::tokenizer;
using boost::escaped_list_separator;
using boost::make_shared;

class SendToThriftServer {
public:
    virtual ~SendToThriftServer() throw() {}

    virtual void init(string host, int port);
    virtual void send_span(Span span) = 0;


protected:
    string host;
    shared_ptr<TSocket> socket;
    shared_ptr<TTransport> transport;
    shared_ptr<TProtocol> protocol;
    shared_ptr<TMemoryBuffer> buffer;
    shared_ptr<TProtocol> buf_protocol;
};

class SendToScribeServer : public SendToThriftServer {
public:
    void init(string host);
    void send_span(Span span);

    virtual ~SendToScribeServer() throw() {}
};

class Importer {
public:
    Importer() : endpoints(), spans() {}
    virtual ~Importer() throw() {}

    typedef boost::unordered_map<int64_t, shared_ptr<Span> > span_map_t;
    typedef boost::range_detail::select_second_mutable_range<span_map_t> span_range_t;

protected:
    typedef boost::unordered_map<string, shared_ptr<Endpoint> > ep_map_t;
    ep_map_t endpoints;

    typedef boost::iterator_range<span_map_t::const_iterator> span_map_range_t;
    span_map_t spans;

    vector<Annotation> annotations;
};

class CSVImporter : public Importer {
public:
    CSVImporter(string csv_path) : Importer(), csv_path(csv_path),
                                   csv_stream() { }

    virtual ~CSVImporter() throw() {}

    span_range_t process_new();


protected:
    string csv_path;
    std::ifstream csv_stream;

    typedef tokenizer<escaped_list_separator<char> > Tokenizer;
    shared_ptr<Endpoint> read_endpoint(string& ep_name, vector<string> vec);
    shared_ptr<Span> read_span(vector<string> vec);
    void read_annotation(vector<string> vec);

private:
    class InvalidLineException : public std::exception { };
};

#endif /* #ifndef ZIPKIN_IMPORT_H */
