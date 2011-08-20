#include "global.h"
#include "cktvengine.h"

#ifdef _DEBUG
int main(int argv, char* argc[])
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
    if(ENGINE.init())
    {
        global::g_pHGE = ENGINE.GetHGE();

        ENGINE.SetScene("AD");
        ENGINE.start();
        ENGINE.close();
    }

    return 0;
}
