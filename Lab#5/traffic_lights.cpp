#include "header.h"
void traffic_lights::setTL(POINT position,bool tls )
{
    this->position=position;
    this->tls=tls;
}
bool traffic_lights::SwitchTL(const HDC &hdc,HBRUSH &hBrush)
{
    this->tls=!this->tls;
    if (tls==true)
    {
        hBrush = CreateSolidBrush( RGB(0,255,0) );
        SelectObject(hdc, hBrush);
    }
    else
    {
        hBrush = CreateSolidBrush( RGB(255,0,0) );
        SelectObject(hdc, hBrush);
    }
    Ellipse(hdc, position.x-40, position.y-40, position.x+40, position.y+40 );
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    DeleteObject(hBrush);
    return TRUE;
}

