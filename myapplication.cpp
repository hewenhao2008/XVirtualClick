#include "myapplication.h"
#include<QTextStream>
#include<QLocalSocket>
#include<QString>
#include<QStringList>
#include<QFile>

MyApplication::MyApplication(int argc, char **argv):QApplication(argc,argv)
{
    setQuitOnLastWindowClosed(false);

    _isRunning=false;

    QCoreApplication::setApplicationName("localserver");
    QString serverName=QCoreApplication::applicationName();

    QLocalSocket socket;
    socket.connectToServer(serverName);

        if(socket.waitForConnected(500))
        {
            QTextStream stream(&socket);
            QStringList args=QCoreApplication::arguments();

            if(args.count()>1)
            {
                stream<<args.last();
            }else
            {
                stream<<QString();
            }
            stream.flush();
            qDebug()<<"Connected server,program will quit";

            socket.waitForBytesWritten();

            _isRunning=true;

            return;
        }

        qDebug()<<"Can't connect to server,build a server";
        server=new QLocalServer(this);
        connect(server,SIGNAL(newConnection()),this,SLOT(newLocalConnection()));

        if(server->listen(serverName))
        {
            //防止程序崩溃时,残留进程服务,移除之
            if(server->serverError()==QAbstractSocket::AddressInUseError&&QFile::exists(server->serverName()))
            {
                QFile::remove(server->serverName());
                server->listen(serverName);
            }
        }


    }


    void MyApplication::newLocalConnection()
    {
        QLocalSocket *socket=server->nextPendingConnection();
        if(!socket)
            return;

        socket->waitForReadyRead(1000);

        //显示传入参数值
        QTextStream in(socket);
        QString vl;
        in>>vl;
        qDebug()<<"The value is: "<<vl;

        delete socket;
    }


    bool MyApplication::isRunning()
    {
        return _isRunning;
    }
