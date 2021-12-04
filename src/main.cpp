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
