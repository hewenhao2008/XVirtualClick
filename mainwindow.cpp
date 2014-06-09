#include "mainwindow.h"
#include"windows.h"
//#include <QMessageBox>
//#include<QInputDialog>
#include"aboutdialog.h"
#include<QtGui>
#include<QtCore>
#include<QTimer>
#include<QInputDialog>
#include<QDebug>
#include<QMessageBox>

MainWindow::MainWindow():clickInterval(100),isBegin(false),SelMode(XCLMODE)

{
    registerGlobalKey();
    timer=new QTimer(this);


    iTrayIcon=new QSystemTrayIcon(this);

    iTrayIcon->setIcon( QIcon("://icon/trayIcon.png") );

    iTrayIcon->show();

    iTrayIcon->setToolTip(QString("提示：F9开启,F110暂停,F11退出！"));

    iTrayIcon->showMessage("XVirtualClick","程序已启动！");

    addMenu();

    registerGlobalKey();

    setWindowIcon(QIcon("://icon/trayIcon.png"));
    setWindowTitle("XVirtualClick");

    connect(this,SIGNAL(hotKeyF9Pressed()),this,SLOT(hotKeyF9Received()));
    connect(this,SIGNAL(hotKeyF10Pressed()),this,SLOT(hotKeyF10Received()));
    connect(this,SIGNAL(hotKeyF11Pressed()),this,SLOT(hotKeyF11Received()));



}

MainWindow::~MainWindow()

{

}

void MainWindow::addMenu()

{

    modeSelect=new QMenu("模式选择");


    modeOfClick=new QAction("单击模式",this);
    modeOfClick->setCheckable(true);
    connect(modeOfClick,SIGNAL(triggered()),this,SLOT(setClickMode()));

    modeOfDlClick=new QAction("双击模式",this);
    modeOfDlClick->setCheckable(true);
    connect(modeOfDlClick,SIGNAL(triggered()),this,SLOT(setDlClickMode()));

    modeGroup=new QActionGroup(this);

    modeGroup->addAction(modeOfClick);
    modeGroup->addAction(modeOfDlClick);

    modeOfClick->setChecked(true);
;
    modeSelect->addAction(modeOfClick);
    modeSelect->addAction(modeOfDlClick);

    intervalAction=new QAction("时间间隔",this);
    intervalAction->setToolTip("点击间隔，默认100ms");
    connect(intervalAction,SIGNAL(triggered()),this,SLOT(setInterval()));

    helpMenu=new QMenu("帮助");

    helpAction=new QAction("帮助",this);
    connect(helpAction,SIGNAL(triggered()),this,SLOT(doHelpAct()));

    aboutAction=new QAction("关于",this);
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(doAboutAct()));

    helpMenu->addAction(helpAction);
    helpMenu->addAction(aboutAction);
    quitAction=new QAction("退出",this);
    connect(quitAction,SIGNAL(triggered()),this,SLOT(exeitProgram()));

    iTraymenu=new QMenu;
    iTraymenu->addMenu(modeSelect);
    iTraymenu->addAction(intervalAction);
    iTraymenu->addMenu(helpMenu);
    iTraymenu->addAction(quitAction);

    iTrayIcon->setContextMenu(iTraymenu);
}


void  MainWindow::setClickMode()
{
    SelMode=XCLMODE;//单击模式
}
void  MainWindow::setDlClickMode()
{
    SelMode=XDLMODE;//双击模式
}

//时间间隔
void MainWindow::setInterval()
{
    bool ok;

    int i=QInputDialog::getInt(0,tr("修改时间间隔"),
                               tr("输入点击时间间隔"),
                               clickInterval,
                               0,2147480000,0,&ok);
    if(ok)
    {
        clickInterval=i;
    }


}

void MainWindow::exeitProgram()
{
    if(UnregisterHotKey(HWND(this->winId()),   0x78))
    {
        qDebug("F9 IS unREGISTED");

    }
    if(UnregisterHotKey(HWND(this->winId()),   0x79))
    {
        qDebug("F10 IS unREGISTED");
    }
    if(UnregisterHotKey(HWND(this->winId()),   0x7A))
    {
        qDebug("F11 IS unREGISTED");
    }

    iTrayIcon->showMessage("XVirtualClick","程序已退出！");
    iTrayIcon->hide();
    exit(0);
}

void MainWindow::registerGlobalKey()
{
    if(RegisterHotKey((HWND(this->winId())), 0x79,0,VK_F10))
    {
        qDebug("F10 IS REGISTED");
    }
    if(RegisterHotKey(HWND(this->winId()), 0x7A, 0, VK_F11))
    {
        qDebug("F11 IS REGISTED");
    }
    if(RegisterHotKey(HWND(this->winId()), 0x78, 0, VK_F9))
    {
        qDebug("F9 IS REGISTED");
    }

}
void MainWindow::hotKeyF9Received()
{
    isBegin=true;
    iTrayIcon->showMessage("XVirtualClick","已开启,F10暂停！");
    switch(SelMode)
    {

        case XCLMODE:

            connect( timer, SIGNAL(timeout()), this, SLOT(doXClick()) );
            timer->start(clickInterval);

            break;
        case XDLMODE:

            connect( timer, SIGNAL(timeout()), this, SLOT(doXDlClick()) );
            timer->start(clickInterval);

            break;
    }


}

void MainWindow::hotKeyF10Received()
{
        isBegin=false;
        timer->stop();
        iTrayIcon->showMessage("XVirtualClick","已暂停,F9开启！");
        qDebug("F11 is received");
        //disconnect(timer,SIGNAL(timeout()),this,0);//



}
void MainWindow::hotKeyF11Received()
{
    exeitProgram();

}


void MainWindow::doXClick()
{
    XClick();
}

void MainWindow::doXDlClick()
{
    XDlClick();
}

void MainWindow::doHelpAct()
{
  iTrayIcon->showMessage("XVitualClick帮助","F9开启，F10暂停，F11退出");
}


void MainWindow::doAboutAct()
{
    AboutDialog* aboutDialog=new AboutDialog(this);
    aboutDialog->setLogo("://icon/about-logo.png");
    aboutDialog->setText("://about.txt",true);
    aboutDialog->setInfo("<table border=\"0\"><tr height=\"22\"><td width=270 valign=\"middle\" ><b>XVirtualClick v1.2</b></td><td><a href=\"https://github.com/pansinm\">查看源代码</a></td></tr><tr height=\"22\"><td width=300 valign=\"middle\">by X_PAN</td><td>pansinm@163.com</td></tr></table>");
    aboutDialog->setWindowTitle("关于XVirtualClick");
    aboutDialog->show();
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if(eventType=="windows_generic_MSG")
    {
        qDebug("This is windows MSG");
        MSG* msg=static_cast<MSG*>(message);
        if(msg->message==WM_HOTKEY)
        {
            qDebug("This is HotKey!");
            if(msg->wParam==VK_F10)
            {
               // qDebug("F10 is Pressed");
                emit hotKeyF10Pressed();
            }
            if(msg->wParam==VK_F11)
            {
               // qDebug("F11 is Pressed");
                emit hotKeyF11Pressed();
            }
            if(msg->wParam==VK_F9)
            {
               qDebug("F9 is Pressed");
                emit hotKeyF9Pressed();
            }
            return true;
        }

    }
 return  false;

}

