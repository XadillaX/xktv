#include "System/VolumeFunc.h"
#include <cstdio>

bool                                GetVolumeControl(HMIXER hmixer, long componentType, long ctrlType, MIXERCONTROL* mxc);
long                                GetMuteValue(HMIXER hmixer, MIXERCONTROL* mxc);
bool                                SetMuteValue(HMIXER hmixer, MIXERCONTROL* mxc, bool mute);

DWORD                               GetVolumeValue(HMIXER hmixer, MIXERCONTROL* mxc);
bool                                SetVolumeValue(HMIXER hmixer, MIXERCONTROL* mxc, DWORD volume);

VolumeFunc::VolumeFunc(void)
{
}

VolumeFunc::~VolumeFunc(void)
{
}

bool GetVolumeControl(HMIXER hmixer, long componentType, long ctrlType, MIXERCONTROL *mxc)
{
    MIXERLINECONTROLS mxlc;
    MIXERLINE mxl;

    mxl.cbStruct = sizeof(mxl);   
    mxl.dwComponentType = componentType;
    int err;
    if(MMSYSERR_NOERROR == (err = mixerGetLineInfo((HMIXEROBJ)hmixer, &mxl, MIXER_GETLINEINFOF_COMPONENTTYPE)))   
    {   
        mxlc.cbStruct = sizeof(mxlc);   
        mxlc.dwLineID = mxl.dwLineID;   
        mxlc.dwControlType = ctrlType;   
        mxlc.cControls = 1;   
        mxlc.cbmxctrl = sizeof(MIXERCONTROL);
        mxlc.pamxctrl = mxc;   
        if(mixerGetLineControls((HMIXEROBJ)hmixer, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE)) return 0;   
        else return 1;
    }
    
    printf("%d\n", err);

    return 0;
}

long GetMuteValue(HMIXER hmixer, MIXERCONTROL* mxc)
{
    MIXERCONTROLDETAILS mxcd;
    MIXERCONTROLDETAILS_BOOLEAN mxcdMute;
    mxcd.hwndOwner = 0;
    mxcd.cbStruct = sizeof(mxcd);
    mxcd.dwControlID = mxc->dwControlID;
    mxcd.cbDetails = sizeof(mxcdMute);
    mxcd.paDetails = &mxcdMute;
    mxcd.cChannels = 1;
    mxcd.cMultipleItems = 0;
    if(mixerGetControlDetails((HMIXEROBJ)hmixer, &mxcd,MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE))
    {
        return -1;
    }
    
    return mxcdMute.fValue;
}

DWORD GetVolumeValue(HMIXER hmixer, MIXERCONTROL *mxc)
{
    MIXERCONTROLDETAILS mxcd;   
    MIXERCONTROLDETAILS_UNSIGNED vol;
    vol.dwValue = 0;     
    mxcd.hwndOwner = 0;   
    mxcd.cbStruct = sizeof(mxcd);     
    mxcd.dwControlID = mxc->dwControlID;     
    mxcd.cbDetails = sizeof(vol);     
    mxcd.paDetails = &vol;   
    mxcd.cChannels = 1;   
    if(mixerGetControlDetails((HMIXEROBJ)hmixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE))
    {
        return -1;
    }

    return vol.dwValue;   
}

bool SetMuteValue(HMIXER hmixer, MIXERCONTROL* mxc, bool mute)
{
    MIXERCONTROLDETAILS mxcd;     
    MIXERCONTROLDETAILS_BOOLEAN mxcdMute;
    mxcdMute.fValue = mute;     
    mxcd.hwndOwner = 0;   
    mxcd.dwControlID = mxc->dwControlID;     
    mxcd.cbStruct = sizeof(mxcd);   
    mxcd.cbDetails = sizeof(mxcdMute);     
    mxcd.paDetails = &mxcdMute;     
    mxcd.cChannels = 1;     
    mxcd.cMultipleItems = 0;   
    if(mixerSetControlDetails((HMIXEROBJ)hmixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE)) 
    {
        return 0;   
    }

    return 1;     
}

bool SetVolumeValue(HMIXER hmixer, MIXERCONTROL* mxc, DWORD volume)
{
    MIXERCONTROLDETAILS mxcd;     
    MIXERCONTROLDETAILS_UNSIGNED vol;
    vol.dwValue = volume;     
    mxcd.hwndOwner = 0;   
    mxcd.dwControlID = mxc->dwControlID;     
    mxcd.cbStruct = sizeof(mxcd);   
    mxcd.cbDetails = sizeof(vol);   
    mxcd.paDetails = &vol;   
    mxcd.cChannels = 1;   
    if(mixerSetControlDetails((HMIXEROBJ)hmixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE))  
    {
        return 0;
    }

    return 1;  
}

DWORD WINAPI VolumeFunc::GetVolume(VOLUME_DEV_FLAG dev)
{
      long device;
      DWORD rt = 0;     
      MIXERCONTROL volCtrl;     
      HMIXER hmixer;     
      switch (dev)   
      {   
      case VDF_WAVE: device = MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT; break;     
      case VDF_MIDI: device = MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER; break;     
      case VDF_LINE_IN:
          {
              //   device=MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC;   break;   //   cd   音量     
              //   device=MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE;   break;   //麦克风音量     
              //   device=MIXERLINE_COMPONENTTYPE_SRC_LINE;   break;   //PC   扬声器音量     
              device = MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC; break;
          }
        
      default: device = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;     
      }   
        
      if(mixerOpen(&hmixer, 0, 0, 0, 0)) return 0;   
      if(!GetVolumeControl(hmixer, device, MIXERCONTROL_CONTROLTYPE_VOLUME, &volCtrl)) return 0;   
      rt = GetVolumeValue(hmixer, &volCtrl) * 100 / volCtrl.Bounds.lMaximum;   
      mixerClose(hmixer);   
      return rt;   
}

bool WINAPI VolumeFunc::SetVolume(long vol, VOLUME_DEV_FLAG dev)
{   
    // dev = 0, 1, 2 分别表示主音量, 波形, MIDI, LINE IN   
    // vol = 0 - 100 表示音量的大小, 设置与返回音量的值用的是百分比, 即音量从0 - 100, 而不是设备的绝对值   
    // retrun false 表示设置音量的大小的操作不成功   
    // retrun true 表示设置音量的大小的操作成功   

    long device;   
    bool rc = false;   
    MIXERCONTROL volCtrl;   
    HMIXER hmixer;   
    switch (dev)   
    {   
    case VDF_WAVE: device = MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT; break;   
    case VDF_MIDI: device = MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER; break;   
    case VDF_LINE_IN: device = MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC; break;   

    default: device = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;  
    }     

    if(mixerOpen(&hmixer, 0, 0, 0, 0)) return 0;   

    if(GetVolumeControl(hmixer, device, MIXERCONTROL_CONTROLTYPE_VOLUME, &volCtrl))     
    {     
        vol = vol * volCtrl.Bounds.lMaximum / 100;     
        if(SetVolumeValue(hmixer, &volCtrl, vol))   
        rc = true;   
    }
    mixerClose(hmixer);     
    return rc;     
}

bool WINAPI VolumeFunc::SetMute(bool vol, VOLUME_DEV_FLAG dev)
{   
    //   dev   =0,1,2   分别表示主音量,波形,MIDI   ,LINE   IN   
    //   vol=0,1   分别表示取消静音,设置静音   
    //   retrun   false   表示取消或设置静音操作不成功   
    //   retrun   true   表示取消或设置静音操作成功   

    long device;   
    bool rc = false;   
    MIXERCONTROL volCtrl;   
    HMIXER hmixer;   
    switch(dev)   
    {   
    case VDF_WAVE: device = MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT; break;   
    case VDF_MIDI:  device=MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER; break;   
    case VDF_LINE_IN: device=MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC; break;     

    default: device = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;   
    }     

    if(mixerOpen(&hmixer, 0, 0, 0, 0)) return 0;     
    if(GetVolumeControl(hmixer, device, MIXERCONTROL_CONTROLTYPE_MUTE,&volCtrl))     
        if(SetMuteValue(hmixer,&volCtrl,(bool)vol))
        {
            rc = true;   
        }

    mixerClose(hmixer);     
    return rc;   
}

bool WINAPI VolumeFunc::GetMute(VOLUME_DEV_FLAG dev)  
{   
    //dev   =0,1,2   分别表示主音量，波形,MIDI   ,LINE   IN   
    //   retrun   false   表示没有静音   
    //   retrun   true   表示静音   
    long device;   
    bool rc = false;   
    MIXERCONTROL volCtrl;   
    HMIXER hmixer;   
    switch(dev)   
    {   
    case VDF_WAVE: device = MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT; break;   
    case VDF_MIDI: device = MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER; break;   
    case VDF_LINE_IN: device = MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC; break;   
    default: device = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;   
    }     

    if(mixerOpen(&hmixer, 0, 0, 0, 0)) return 0;     

    if(GetVolumeControl(hmixer, device, MIXERCONTROL_CONTROLTYPE_MUTE, &volCtrl))   
        rc = GetMuteValue(hmixer, &volCtrl);   
    mixerClose(hmixer);   
    return rc;   
}