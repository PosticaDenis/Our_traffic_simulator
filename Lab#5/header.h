
#include <windows.h>
#define ID_TIMER 1

using namespace std;

class traffic_lights
{
public:
    POINT position;
    static bool tls;
    void setTL(POINT position, bool tls);
    bool SwitchTL(const HDC &hdc,HBRUSH &hBrush);
};
