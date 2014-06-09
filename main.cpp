#include "mainwindow.h"
#include <QApplication>
#include"myapplication.h"

int main(int argc, char *argv[])
{
    MyApplication app(argc, argv);
    if(app.isRunning())
        return 0;
    MainWindow w;
    //w.show();
    return app.exec();
}
