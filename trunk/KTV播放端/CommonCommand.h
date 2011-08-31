#ifndef COMMONCOMMAND_H
#define COMMONCOMMAND_H

#define MAINID_REQUEST_SONG                         1

#define SUBID_REQUEST_NEXT_SONG                     1
struct tagRequestNextSong
{
    char                path[256];
};

#define SUBID_REQUEST_PAUSE                         2
struct tagRequestPause
{
    bool                paused;
};

#define SUBID_REQUEST_CUTDOWN                       3

#endif
