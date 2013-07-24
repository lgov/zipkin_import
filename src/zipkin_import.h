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


#include <sys/socket.h>
#include <arpa/inet.h>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include "thrift/Scribe.h"
#include "thrift/zipkinCore_types.h"
#include "thrift/zipkinCore_constants.h"

using namespace apache::thrift;
using apache::thrift::protocol::TProtocol;
using apache::thrift::transport::TTransport;
using apache::thrift::transport::TSocket;
using apache::thrift::transport::TMemoryBuffer;

class SendToThriftServer {
public:
    SendToThriftServer() {
    }
    virtual ~SendToThriftServer() throw() {}

    virtual void init(std::string host, int port);
    virtual void send_span(Span span) = 0;


protected:
    std::string host;
    boost::shared_ptr<TSocket> socket;
    boost::shared_ptr<TTransport> transport;
    boost::shared_ptr<TProtocol> protocol;
    boost::shared_ptr<TMemoryBuffer> buffer;
    boost::shared_ptr<TProtocol> buf_protocol;
};

class SendToScribeServer : public SendToThriftServer {
public:
    SendToScribeServer() {
    }
    void init(std::string host);
    void send_span(Span span);

    virtual ~SendToScribeServer() throw() {}
};
