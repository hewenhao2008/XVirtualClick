#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "xvirtualclick.h"
#include <QMainWindow>

#include <QSystemTrayIcon>

#include <QIcon>

#include <Qmenu>

#include <QAction>

#include<QActionGroup>
#include<QTimer>

class MainWindow: public QMainWindow,public XVirtualClick

{

    Q_OBJECT


private:

    int clickInterval;//点击间隔，MS

    bool isBegin;

    QSystemTrayIcon *iTrayIcon;

    QMenu *iTraymenu;

    QMenu *modeSelect;

    QActionGroup *modeGroup;

    QAction *modeOfDlClick;

    QAction *modeOfClick;

    QAction *intervalAction;

    QMenu *helpMenu;

    QAction *helpAction;

    QAction *aboutAction;

    QAction *quitAction;


    void addMenu();

    QTimer *timer;

public:

    MainWindow();

    enum{XCLMODE,XDLMODE}SelMode;

    void registerGlobalKey();

    virtual ~MainWindow();

    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private slots:

    void setClickMode();
    void setDlClickMode();

    void setInterval();
    void exeitProgram();

    void doHelpAct();
    void doAboutAct();

    void doXDlClick();
    void doXClick();

    void hotKeyF9Received();
    void hotKeyF10Received();
    void hotKeyF11Received();



signals:
    void hotKeyF9Pressed();
    void hotKeyF10Pressed();
    void hotKeyF11Pressed();



};

#endif // MAINWINDOW_H
