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

#include <memory>
#include <string>
#include <sstream>

#include <boost/make_shared.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>

#include "zipkin_import.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

void SendToThriftServer::init(std::string host, int port) {
    socket = boost::make_shared<class TSocket>(host, port);
    transport = boost::make_shared<class TFramedTransport>(socket);
    protocol = boost::make_shared<TBinaryProtocol>(transport);

    buffer = boost::make_shared<class TMemoryBuffer>();
    buf_protocol = boost::make_shared<TBinaryProtocol>(buffer);
}

/*
 Convert up to len bytes of binary data in src to base64 and store it in dest

 \param dest Destination buffer to hold the base64 data.
 \param src Source binary data.
 \param len The number of bytes of src to convert.

 \return The number of characters written to dest.
*/

static std::string
base64_encode(const char *src, size_t len)
{
    using namespace boost::archive::iterators;

    std::stringstream os;
    const std::string base64_padding[] = {"", "==","="};

    typedef base64_from_binary<transform_width<const char *, 6, 8> > base64_enc;

    std::copy(base64_enc(src), base64_enc(src + len),
              std::ostream_iterator<char>(os));

    os << base64_padding[len % 3];

    return os.str();
}

void SendToScribeServer::init(std::string host)
{
    /* Use default port for scribe */
    SendToThriftServer::init(host, 1463);
}

void SendToScribeServer::send_span(Span span)
{
    LogEntry le;
    std::vector<LogEntry> messages;

    /* serialize the span to memory */
    unsigned char *inbuf;
    uint32_t len;

    span.write(buf_protocol.get());
    buffer->getBuffer(&inbuf, &len);

    /* Base64 encode the serialized span */
    std::string base64_str = base64_encode((const char *)inbuf, len);

    /* Create a LogEntry, category: zipkin: message the Base64 encoded span */
    le.__set_category("zipkin");
    le.__set_message(base64_str);
    messages.insert(messages.begin(), le);

    /* Send to the Scribe server */
    ScribeClient client(protocol);
    transport->open();
    ResultCode::type result = client.Log(messages);
    if (result != ResultCode::OK)
        std::cerr << "Error sending span to the Scribe server.\n";
    transport->close();
}
