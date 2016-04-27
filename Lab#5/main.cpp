#include "header.h"
#include <windows.h>
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
 //static traffic_lights *traffic_lights[4];
 double a[4]={200,100,20,100};
 double b[4]={200,20,100,100};
 POINT coord[4];
 static bool tl1[4]={true,false,false,true};

 VOID CALLBACK TimerProc(HWND, UINT, UINT, DWORD );

 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
 PSTR szCmdLine, int iCmdShow)
 {
 static char szAppName[] = "Beeper2";
 HWND hwnd;
 MSG msg;
 WNDCLASSEX wndclass;
 wndclass.cbSize = sizeof(wndclass);
 wndclass.style = CS_HREDRAW | CS_VREDRAW;
 wndclass.lpfnWndProc = WndProc;
 wndclass.cbClsExtra = 0;
 wndclass.cbWndExtra = 0;
 wndclass.hInstance = hInstance;
 wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
 wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
 wndclass.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH);
 wndclass.lpszMenuName = NULL;
 wndclass.lpszClassName = szAppName;
 wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
 RegisterClassEx(&wndclass);
 hwnd = CreateWindow(szAppName, "Beeper2 Timer Demo",
 WS_OVERLAPPEDWINDOW,
 CW_USEDEFAULT, CW_USEDEFAULT,
 CW_USEDEFAULT, CW_USEDEFAULT,
 NULL, NULL, hInstance, NULL);
 while(!SetTimer(hwnd, ID_TIMER, 1000,(TIMERPROC) TimerProc))
 if(IDCANCEL == MessageBox(hwnd,
 "Too many clocks or timers!", szAppName,
 MB_ICONEXCLAMATION | MB_RETRYCANCEL))
 return FALSE;
 ShowWindow(hwnd, iCmdShow);
 UpdateWindow(hwnd);
 while(GetMessage(&msg, NULL, 0, 0))
 {
 TranslateMessage(&msg);
 DispatchMessage(&msg);
 }
 return msg.wParam;
 }

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
 {
 //POINT coord[4];
 static HDC hdc;//hdcMem;
static RECT rect;
 switch(iMsg)
 {
 case WM_DESTROY :
 KillTimer(hwnd, ID_TIMER);
 PostQuitMessage(0);
 return 0;
 }
 return DefWindowProc(hwnd, iMsg, wParam, lParam);
 }
VOID CALLBACK TimerProc(HWND hwnd, UINT iMsg, UINT iTimerID, DWORD dwTime)
 {
     POINT coord;
     coord.x=10;
     coord.y=10;
     static bool b=true;
 static HDC hdc,hdcMem;
 HBRUSH hBrush;
 //PAINTSTRUCT ps;
 //static RECT rect;
     //for (int i=0;i<4;i++)
     //{

          //for (int i=0;i<4;i++)
             //{
             //hdcMem = CreateCompatibleDC(hdc);
                 //coord[0].x=a[0];
                 //coord[0].y=b[0];
                 //traffic_lights[0]->setTL(coord[0],tl1[0]);
                 //traffic_lights[0]->CreateTL(traffic_lights[0],hdcMem,tl1[0],coord[0]);
         //tl1[0]=!tl1[0];
         //traffic_lights[0]->SwitchTL(traffic_lights[0],tl1[0]);
     //}


    hBrush = CreateSolidBrush(RGB(0,0,255));
    SelectObject(hdc, hBrush);
    Rectangle(hdc, 25, 25, 45, 45 );
        //SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        DeleteObject(hBrush);
 traffic_lights tl;
tl.setTL(coord,b);
tl.CreateTL(hdcMem,b,coord);
b=!b;
tl.SwitchTL(b);
 }
