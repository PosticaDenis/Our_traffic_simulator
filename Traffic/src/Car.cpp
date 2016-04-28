#include "Car.h"

Car::Car(POINT center,const int &speed) {
    const char arr[3] = {0, 1, 2};
    right = arr[rand()%3];
    this->center=center;
    this->xSpeed=speed;
    this->ySpeed=speed;
    clr=RGB(255,0,0);

}
bool Car::Accelerate(const int& dSpeedX,const int& dSpeedY) {
    xSpeed=dSpeedX;
    ySpeed=dSpeedY;
    return TRUE;
}

bool Car::Move(const HDC &hdc,const RECT& rect,HBRUSH &hBrush) {
    hBrush=CreateSolidBrush(clr);
    SelectObject(hdc,hBrush);
    Collision(rect);
    if (semafor==false){
        center.x=center.x;
    } else {
        center.x+=xSpeed;
    }
    if (xSpeed==0 && right==0){
        center.y+=-abs(ySpeed);

    } else if (xSpeed==0 && right==1){
        center.y+=abs(ySpeed);

    } else if (xSpeed==0 && right==2){
        xSpeed=4;
        center.x+=xSpeed;

    }


    Rectangle(hdc,center.x-25,center.y-25,center.x+25,center.y+25);
    SelectObject(hdc,GetStockObject(WHITE_BRUSH));
    DeleteObject(hBrush);
    return TRUE;

}


void Car::SetSemafor(bool sem){
    semafor=sem;
}


bool Car::Collision(const RECT &rect) {

    if(( (right==0) && (center.x-25>(rect.right-1)/2)) || ((right==1) && (center.x+55>(rect.right-1)/2) )){
      xSpeed=0;
    }

    return TRUE;
}
bool Car::Coll(Car &c2){
    if((semafor==false) && (c2.center.x>center.x-80)){
        c2.SetSemafor(false);
    }
 return TRUE;
}
