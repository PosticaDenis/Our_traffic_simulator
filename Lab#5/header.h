
#include <windows.h>
#define ID_TIMER 1

using namespace std;

class traffic_lights
{
protected:
    COLORREF clr;
public:
    POINT position;
    bool tls;
    void setTL(POINT position, bool tls);
    bool CreateTL(const HDC &hdc,bool tls,POINT position);
    bool Color(const COLORREF &clr);
    bool SwitchTL(bool tls);
};
