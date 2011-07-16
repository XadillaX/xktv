#ifndef XSTRINGFUNC_H
#define XSTRINGFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;
#pragma once

class XStringFunc
{
public:
    XStringFunc();
    XStringFunc(string szStr);
    XStringFunc(const char* szStr);

    /** 去空格 */
    void                        LTrim();
    void                        RTrim();
    void                        LRTrim();
    void                        AllTrim();
    
    /** 分割 */
    int                         Split(string szCHR, string* szArr, int nMaxCount = 0);

    /** 类型转换 */
    static int                  ToInt(string szStr);
    static void                 ToInt(string* szArr, int* nArr, int nCount);
    static double               ToDouble(string szStr);
    static void                 ToDouble(string* szArr, double* fArr, int nCount);

    /** 获取结果 */
    void                        SetString(string szStr);
    void                        SetString(const char* szStr);
    string                      GetString();

private:
    string                      m_szStr;
};

#endif
