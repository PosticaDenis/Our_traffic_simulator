#include "header.h"
#include "Car.h"
#include <windows.h>

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

char szClassName[ ] = "WindowsApp";
static Car *car[50];

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;

    wincl.hbrBackground =NULL;
    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
           0,
           szClassName,
           "CrazyBubbles",
           WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           800,
           800,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );

    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}


bool LoadAndBlitBitmap(char* szFileName, HDC hWinDC)
{
	// Load the bitmap image file
	HBITMAP hBitmap;
	hBitmap = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE);
	// Verify that the image was loaded
	if (hBitmap == NULL) {
		::MessageBox(NULL, TEXT("LoadImage Failed"), TEXT("Error"), MB_OK);
		return false;
	}

	// Create a device context that is compatible with the window
	HDC hLocalDC;
	hLocalDC = ::CreateCompatibleDC(hWinDC);
	// Verify that the device context was created
	if (hLocalDC == NULL) {
		::MessageBox(NULL, TEXT("CreateCompatibleDC Failed"), TEXT("Error"), MB_OK);
		return false;
	}

	// Get the bitmap's parameters and verify the get
	BITMAP qBitmap;
	int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP),
		reinterpret_cast<LPVOID>(&qBitmap));
	if (!iReturn) {
		::MessageBox(NULL, TEXT("GetObject Failed"), TEXT("Error"), MB_OK);
		return false;
	}

	// Select the loaded bitmap into the device context
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hLocalDC, hBitmap);
	if (hOldBmp == NULL) {
		::MessageBox(NULL, TEXT("SelectObject Failed"), TEXT("Error"), MB_OK);
		return false;
	}

	// Blit the dc which holds the bitmap onto the window's dc
	BOOL qRetBlit = ::BitBlt(hWinDC, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight,
		hLocalDC, 0, 0, SRCCOPY);
	if (!qRetBlit) {
		::MessageBox(NULL, TEXT("Blit Failed"), TEXT("Error"), MB_OK);
		return false;
	}

	// Unitialize and deallocate resources
	::SelectObject(hLocalDC, hOldBmp);
	::DeleteDC(hLocalDC);
	::DeleteObject(hBitmap);
	return true;
}


LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc,hdcMem,hdccMem;
    static PAINTSTRUCT ps;
    static RECT rect;
    static HBRUSH hBrush;
    static HBITMAP hbmMem;

    static HANDLE hOld;

    static int timerSpeed = 3000;

     RECT   rcClient;
    static BITMAP bitmap;
    static HBITMAP filll = NULL ;
    HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);


    static int tspeed=30,nrobjects=0;
    POINT coord;
    static traffic_lights TL[4];
    double a[4]={200,600,200,600};
    double b[4]={200,200,600,600};
    static bool tl[4]={TRUE,FALSE,FALSE,TRUE};
    switch (message)
    {
        case WM_CREATE:
        {
          hdc = GetDC(hwnd);
          GetClientRect(hwnd,&rect);

          for (int i=0;i<4;i++)
          {
              coord.x=a[i];
              coord.y=b[i];
              TL[i].setTL(coord,tl[i]);
          }
          SetTimer(hwnd, ID_TIMER1, timerSpeed, NULL);
          SetTimer(hwnd,ID_TIMER,tspeed,NULL);
        break;
        }

        case WM_MOUSEWHEEL:
        {
            if((short)HIWORD(wParam)<0)
            {
                timerSpeed+=100;
            }
            else
            {
                timerSpeed-=100;
                if (timerSpeed<0)
                {
                    timerSpeed=1;
                }
            }
            KillTimer(hwnd,ID_TIMER1);
            SetTimer(hwnd,ID_TIMER1,timerSpeed,NULL);
        break;
        }

        case WM_LBUTTONDOWN:

            POINT newobj;

            GetClientRect(hwnd, &rcClient);
			newobj.x = 100;
			newobj.y = (rcClient.bottom - rcClient.top)/2;

            car[nrobjects]=new Car(newobj,5+newobj.x%5);

            nrobjects++;
            break;

        case WM_PAINT:
        {
            hdc = BeginPaint(hwnd,&ps);
            GetClientRect(hwnd,&rect);

            LoadAndBlitBitmap(TEXT("map.bmp"), hdc);

            hdcMem = CreateCompatibleDC(hdc);
            hbmMem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
            hOld = SelectObject(hdcMem, hbmMem);

            FillRect(hdcMem, &rect,(HBRUSH)GetStockObject(WHITE_BRUSH));

            BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, SRCCOPY);
            SelectObject(hdcMem,hOld);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);

            EndPaint(hwnd,&ps);

        break;
        }

        case WM_TIMER:
        {
            RECT rectangle;
            hdc=GetDC(hwnd);
            switch (wParam)
            {
            case ID_TIMER1:
                for (int i=0;i<4;i++){
                    TL[i].SwitchTL(hdc,hBrush);
                }
                 return 0;

            case ID_TIMER:
            for(int i = 0; i < nrobjects; i++)
            {
                rectangle.bottom=car[i]->center.y+15;
                rectangle.left=car[i]->center.x-15;
                rectangle.top=car[i]->center.y-15;
                rectangle.right=car[i]->center.x+15;
                InvalidateRect(hwnd,&rectangle,true);
                car[i]->Move(hdc, rect, hBrush);
            }

                return 0;
            }
            ReleaseDC(hwnd, hdc);
        break;
        }

        case WM_DESTROY:
        {
            KillTimer(hwnd,ID_TIMER1);
            KillTimer(hwnd,ID_TIMER);

            PostQuitMessage (0);
        break;
        }

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}

