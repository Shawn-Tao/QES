/*****************************************************************************
*  Copyright (c) 2021 BJTU, Inc.
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*      http://www.apache.org/licenses/LICENSE-2.0
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed outlookon an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*  Authors: Shawntao (shawntao-cn@outlook.com)
*  Date: 2021-12-04
*******************************************************************************/

#include "http_server.h"
#include<iostream>

Http_Server::Http_Server(QString port, QObject *parent)
{
    this->port = port.toUShort();
}

void Http_Server::process(WFHttpTask *server_task)
{
    protocol::HttpRequest *req = server_task->get_req();
    protocol::HttpResponse *resp = server_task->get_resp();
    long long seq = server_task->get_task_seq();
    protocol::HttpHeaderCursor cursor(req);
    protocol::HttpChunkCursor chunkcursor(req);

    //head
    std::string name;
    std::string value;
    //chunk
    const void *chunk;
    size_t size;
    char buf[8192];
    int len;

    /* Set response message body. */
    resp->append_output_body_nocopy("<html>", 6);


/****************************************************
 * req->get_method() : get request method
 * req->get_request_uri() : get request uri : the content after port in url
 * req->get_http_version() : get http_version , mostly be 1.1
 * cursor.next(name, value) : let name and value be the next one; defult there are accept-encoding,content-length,host,connection
 * chunkcursor.next(&chunk, &size) : get chunk and size maybe chunk can be regarded as char*;
*/
    len = snprintf(buf, 8192, "<p>%s %s %s</p>", req->get_method(),
                   req->get_request_uri(), req->get_http_version());
    resp->append_output_body(buf, len);

    while (cursor.next(name, value))
    {
        len = snprintf(buf, 8192, "<p>%s: %s</p>", name.c_str(), value.c_str());
        resp->append_output_body(buf, len);
    }

// parser chunk part, let the gcc regard it as char* ; chunk can have a lot part

    while (chunkcursor.next(&chunk, &size))
    {
        len = snprintf(buf, 8192, "<p>%s</p>", (char*)(chunk));
        resp->append_output_body(buf, len);
    }

    resp->append_output_body_nocopy("</html>", 7);

    /* Set status line if you like. */
    resp->set_http_version("HTTP/1.1");
    resp->set_status_code("200");
    resp->set_reason_phrase("OK");

    resp->add_header_pair("Content-Type", "text/html");
    resp->add_header_pair("Server", "Sogou WFHttpServer");
    if (seq == 9) /* no more than 10 requests on the same connection. */
        resp->add_header_pair("Connection", "close");

    /* print some log */
    char addrstr[128];
    struct sockaddr_storage addr;
    socklen_t l = sizeof addr;
    unsigned short port = 0;

    server_task->get_peer_addr((struct sockaddr *)&addr, &l);
    if (addr.ss_family == AF_INET)
    {
        struct sockaddr_in *sin = (struct sockaddr_in *)&addr;
        inet_ntop(AF_INET, &sin->sin_addr, addrstr, 128);
        port = ntohs(sin->sin_port);
    }
    else if (addr.ss_family == AF_INET6)
    {
        struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)&addr;
        inet_ntop(AF_INET6, &sin6->sin6_addr, addrstr, 128);
        port = ntohs(sin6->sin6_port);
    }
    else
        strcpy(addrstr, "Unknown");

    fprintf(stderr, "Peer address: %s:%d, seq: %lld.\n",
            addrstr, port, seq);
    emit(this->Start_detect());


}

void Http_Server::run(){
    // bind the process fun to server
    this->process_request = std::bind(&Http_Server::process,this,std::placeholders::_1);
    WFHttpServer server(process_request);
    if (server.start(this->port) == 0)
    {
        wait_group.wait();
//        exec();
        server.stop();
    }
    else
    {
        perror("Cannot start server");
        this->~Http_Server();
    }
}

//void http_server::Start_detect(){

//}

