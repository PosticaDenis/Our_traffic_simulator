#include "header.h"
void traffic_lights::setTL(POINT position,bool tls )
{
    this->position=position;
    this->tls=tls;
    clr=RGB(255,0,0);
}
bool traffic_lights::Color(const COLORREF &clr)
{
    this -> clr = clr;
    return TRUE;
}
bool traffic_lights::CreateTL(const HDC &hdc,bool tls,POINT position)
{
    Ellipse(hdc, position.x-10, position.y-10, position.x+10, position.y+10 );
    if (tls==true)
    {
        Color(RGB(0,255,0));
    }
    else
    {
        Color(RGB(255,2,0));
    }
}
bool traffic_lights::SwitchTL(bool tls)
{
    if (tls==true)
    {
        Color(RGB(0,255,0));
    }
    else
    {
        Color(RGB(255,0,0));
    }
}

