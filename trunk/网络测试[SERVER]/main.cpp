#include "CKTVNetwork121.h"
#include <iostream>
using namespace std;

void rec(int m, int s, char* d, size_t size)
{
    cout << m << ": " << s << ": " << d << endl;
}

int main()
{
    CKTVNetwork121("tcp://*:5555/", "tcp://127.0.0.1:5323/", rec);

    while(true)
    {
        Sleep(1);
    }

    return 0;
}
