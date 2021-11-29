#include <QCoreApplication>
#include <QtDebug>
#include "http_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString port ="8888";
    Http_Server *server = new Http_Server(port);
    QThread thread;

    // while the server emit the Start_detect sinal
    QObject::connect(server,&Http_Server::Start_detect,[=]{
        qDebug()<<"Hello World!\n";
    });

    server->start();
    qDebug()<<"Test if main thread is influenced by server!\n";

    // using method of movethread will influence the main thread
    //    server->moveToThread(& thread);
    //    thread.start();
    //    qDebug()<<"hahahha!\n";
    //    server->run();
    //    server->run();

    return a.exec();
}
