#include "aboutdialog.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPixmap>
#include<QDesktopServices>
#include<QUrl>
#include<QFile>
#include<QTextStream>
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    init();
}

void AboutDialog::init()
{
    label_Logo=new QLabel;
    label_Logo->setMinimumSize(370,45);

    label_Info=new QLabel;
    label_Info->setMinimumSize(370,45);

    textEdit=new QTextEdit;
    textEdit->setMinimumSize(370,115);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setReadOnly(true);


    btn_confirm=new QPushButton("确定");
    btn_confirm->setMinimumSize(75,25);
    QHBoxLayout* hlayout=new QHBoxLayout;
    hlayout->addStretch();
    hlayout->addWidget(btn_confirm);
    hlayout->setMargin(4);

    QVBoxLayout* vlayout=new QVBoxLayout;
    vlayout->addWidget(label_Logo);
    vlayout->addWidget(label_Info);
    vlayout->addWidget(textEdit);

    vlayout->addLayout(hlayout);
    vlayout->setMargin(0);

    setLayout(vlayout);

    this->setMinimumSize(370,254);
    this->setMaximumSize(370,254);
    setBackground();

    connect(btn_confirm,SIGNAL(clicked()),this,SLOT(close()));


}

void AboutDialog::setLogo(const QString filename)
{
    QPixmap pixmap(filename);
    label_Logo->setPixmap(pixmap);

}
void AboutDialog::setInfo(const QString info)
{
    label_Info->setText(info);
    connect(label_Info,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));
}

void AboutDialog::setText(const QString str, bool isFileName)
{
    if(isFileName==false)
        textEdit->setText(str);
    else if(isFileName==true)
    {
        QFile file(str);

        if(file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QTextStream in(&file);
            QString s;
            s=in.readAll();
            textEdit->setText(s);
            file.close();
        }
    }

}

void AboutDialog::setBackground(const QString styleSheet)
{
    if(styleSheet=="default")
    {
        this->setStyleSheet("AboutDialog{background: rgb(238, 241, 255);}");
    }
    else
        setStyleSheet(styleSheet);
}

void AboutDialog::openUrl(QString url)
{
    QDesktopServices::openUrl(QUrl(url));
}
