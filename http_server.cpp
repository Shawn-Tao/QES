#include "http_server.h"


Http_Server::Http_Server(QString port, QObject *parent)
{
    this->port = port.toUShort();
//    QObject::connect(this,&http_server::Start_detect,[=]{
//        qDebug()<<"Hello World!\n";
//    });
//    this->run();
}

void Http_Server::process(WFHttpTask *server_task)
{
    protocol::HttpRequest *req = server_task->get_req();
    protocol::HttpResponse *resp = server_task->get_resp();
    long long seq = server_task->get_task_seq();
    protocol::HttpHeaderCursor cursor(req);
    std::string name;
    std::string value;
    char buf[8192];
    int len;

    /* Set response message body. */
    resp->append_output_body_nocopy("<html>", 6);
    len = snprintf(buf, 8192, "<p>%s %s %s</p>", req->get_method(),
                   req->get_request_uri(), req->get_http_version());
    resp->append_output_body(buf, len);

    while (cursor.next(name, value))
    {
        len = snprintf(buf, 8192, "<p>%s: %s</p>", name.c_str(), value.c_str());
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
