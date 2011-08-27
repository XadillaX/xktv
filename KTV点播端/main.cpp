#define WIN32_LEAN_AND_MEAN
#include "../KTV²¥·Å¶Ë/cktvnetwork121.h"
#include "global.h"
#include "cktvengine.h"

#ifdef _DEBUG
int main(int argv, char* argc[])
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
    try
    {
        ENGINE.init();
        global::g_pHGE = ENGINE.GetHGE();

        ENGINE.SetScene("AD");
        ENGINE.start();
        ENGINE.close();
    }
    catch(CKTVError& e)
    {
        MessageBox(NULL, e.ToString().c_str(), "´íÎó", MB_ICONERROR);
    }

    return 0;
}
