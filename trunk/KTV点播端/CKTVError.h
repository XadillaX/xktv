//////////////////////////////////////////////////////////////////////////
//
//	KTVÅ×³ö´íÎóÀà
//
//	Program by ËÀÔÂ(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/25
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVERROR_H
#define CKTVERROR_H

#pragma once
#include <string>
using namespace std;

#define THROW_KTV_ERROR(num, what)      (throw CKTVError(num, what, __FILE__, __FUNCTION__, __LINE__))

class CKTVError
{
public:
    CKTVError(int num, string what, string file = "", string function = "", int line = 0) :
        num(num),
        what(what),
        file(file),
        function(function),
        line(line)
    {
    }
    virtual ~CKTVError(void);

    void                        Show();
    string                      ToString();

    int                         Num() { return num; }
    string                      What() { return what; }
    string                      File() { return file; }
    string                      Function() { return function; }
    int                         Line() { return line; }

private:
    int                         num;
    string                      what;
    string                      file;
    string                      function;
    int                         line;
};

#endif
