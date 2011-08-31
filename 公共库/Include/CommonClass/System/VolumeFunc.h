#ifndef VOLUMEFUNC_H
#define VOLUMEFUNC_H

#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>
#pragma comment(lib, "winmm.lib")

enum VOLUME_DEV_FLAG
{
    VDF_MAIN = 0,
    VDF_WAVE = 1,
    VDF_MIDI = 2,
    VDF_LINE_IN = 3
};

class VolumeFunc
{
public:
    VolumeFunc(void);
    virtual ~VolumeFunc(void);

    bool WINAPI                         SetVolume(long vol, VOLUME_DEV_FLAG dev = VDF_MAIN);
    DWORD WINAPI                        GetVolume(VOLUME_DEV_FLAG dev = VDF_MAIN);
    
    bool WINAPI                         SetMute(bool vol, VOLUME_DEV_FLAG dev = VDF_MAIN);
    bool WINAPI                         GetMute(VOLUME_DEV_FLAG dev = VDF_MAIN);
};

#endif
