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
