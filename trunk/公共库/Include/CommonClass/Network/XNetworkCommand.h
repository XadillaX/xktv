#ifndef XNETWORKCOMMAND_H
#define XNETWORKCOMMAND_H

#define MAX_PACKAGE_SIZE                    10240
#define XNETWORK_MAGIC_NUM                  (int)("Xadi")

struct XNetworkHead
{
    int                 MagicNum;
    int                 MainID;
    int                 SubID;

    size_t              Size;
};
#define MAIN_KEEP_ONLINE                    0
#define SUB_KEEP_ONLINE                     0

#endif
