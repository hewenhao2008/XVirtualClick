#ifndef XVIRTUALCLICK_H
#define XVIRTUALCLICK_H
#include<windows.h>
#include<QObject>
class XVirtualClick
{

public:
    XVirtualClick();
    ~XVirtualClick();
    void XPressKey(unsigned char keyByte);//虚拟按键
    void X7fQuickAccess();//快速进入起凡进行中房间
    void XDlClick();//双击
    void XClick();//单击

};

#endif // XVIRTUALCLICK_H
