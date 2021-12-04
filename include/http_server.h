#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <QObject>
#include <QThread>
#include <QString>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "workflow/HttpMessage.h"
#include "workflow/HttpUtil.h"
#include "workflow/WFServer.h"
#include "workflow/WFHttpServer.h"
#include "workflow/WFFacilities.h"
#include "workflow/WFTaskFactory.h"
#include <QtDebug>

static WFFacilities::WaitGroup wait_group(1);

class Http_Server : public QThread
//class Http_Server : public QObject
{
    Q_OBJECT
public:
    explicit Http_Server(QString port = "8888", QObject *parent = 0);
    void process(WFHttpTask *server_task);
//    void sig_handler(int signo);
    unsigned short port;


protected:
    void run();
private:
    std::function<void (WFHttpTask *)> process_request;
signals:
    void Start_detect();  //处理完成信号
};

#endif // HTTP_SERVER_H
