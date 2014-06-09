#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H
#include<QApplication>
#include<QLocalServer>
class MyApplication:public QApplication
{
    Q_OBJECT
public:
    MyApplication(int argc,char **argv);

    bool isRunning();

private slots:
    void newLocalConnection();

private:
    QLocalServer *server;

    bool _isRunning;
};

#endif // MYAPPLICATION_H
