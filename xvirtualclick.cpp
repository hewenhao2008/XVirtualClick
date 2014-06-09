#include "xvirtualclick.h"

XVirtualClick::XVirtualClick()
{
}
XVirtualClick::~XVirtualClick()
{
}
void XVirtualClick::X7fQuickAccess()
{
    XDlClick();
    XPressKey(13);
}

//单击，WINDOWSAPI
void XVirtualClick::XClick()
{
    POINT lpPoint;
    GetCursorPos(&lpPoint);
    SetCursorPos(lpPoint.x, lpPoint.y);
    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
}


void XVirtualClick::XDlClick()
{
    POINT lpPoint;
    GetCursorPos(&lpPoint);
    SetCursorPos(lpPoint.x, lpPoint.y);
    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
}

//按键，WINDOWSAPI
void XVirtualClick::XPressKey(unsigned char keyByte)

{
    keybd_event(keyByte,0,0,0);
    keybd_event(keyByte,0,KEYEVENTF_KEYUP,0);
}
