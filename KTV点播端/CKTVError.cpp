#include "CKTVError.h"

CKTVError::~CKTVError(void)
{
}

void CKTVError::Show()
{
    printf("%s", ToString().c_str());
}

string CKTVError::ToString()
{
    char buf[2048];
    
#ifdef _DEBUG
    sprintf(buf, "[ERROR 0x%.8X]\nMessage:  %s\nFile:     %s\nFunction: %s\nLine:     %d\n\n", num, what.c_str(), file.c_str(), function.c_str(), line);
#else
    sprintf(buf, "[ERROR 0x%.8X] %s\n", num, what);
#endif

    return buf;
}
