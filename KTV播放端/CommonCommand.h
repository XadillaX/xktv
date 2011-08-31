#ifndef COMMONCOMMAND_H
#define COMMONCOMMAND_H

#define MAINID_REQUEST_SONG                         1

#define SUBID_REQUEST_NEXT_SONG                     1
struct tagRequestNextSong
{
    char                path[256];
    int                 vol;
};

#define SUBID_REQUEST_PAUSE                         2
struct tagRequestPause
{
    bool                paused;
};

#define SUBID_REQUEST_CUTDOWN                       3
#define SUBID_REQUEST_SET_VALUME                    4
struct tagRequestValume
{
    int                 volume;
};

#endif
