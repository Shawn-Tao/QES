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

#include <QCoreApplication>
#include <QtDebug>
#include "http_server.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

using namespace YAML;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

// read and analysis yaml config file;
    std::string config_path = "../config.yaml";
    YAML::Node yamlconf =  YAML::LoadFile(config_path);
    std::cout<<"name: "<<yamlconf["project_name"].as<std::string>() << std::endl;

// Create http server
    QString port ="8888";
    Http_Server *server = new Http_Server(port);
    QThread thread;

    // while the server emit the Start_detect sinal
    QObject::connect(server,&Http_Server::Start_detect,[=]{
        qDebug()<<"Start Detection Task!\n";
    });

    server->start();
    qDebug()<<"Test if main thread is influenced by server!\n";

    return a.exec();
}
