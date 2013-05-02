// main.cpp
#include <iostream>
#include <string>
#include <windows.h>

const std::string HandString[3] = { "R", "S", "P" };
const std::string ResultString[3] = { "WinnerA", "Even", "WinnerB" };

const std::string dllName("PlayerSample.dll");
const std::string funcName("GetNextHand");

int judge( const int playerA, const int playerB );

int main()
{
    HINSTANCE handler[2] = {0};
    int (*func[2])( const int previousHand ) = {0};

    for ( int i = 0; i < 2; ++i )
    {
        handler[i] = ::LoadLibraryA( dllName.c_str() );
        if ( handler[i] == 0 )
        {
            std::cout << "Load Error" << std::endl;
            exit(-1);
        }

        func[i] = reinterpret_cast<int (*)(const int)>( ::GetProcAddress( handler[i], funcName.c_str() ) );
        if ( func[i] == 0 )
        {
            std::cout << "Get Error" << std::endl;
            exit(-1);
        }
    }

    int playerA = 0;
    int playerB = 0;
    for ( int times = 0; times < 100; ++times )
    {
        playerA = func[0]( playerA );
        playerB = func[1]( playerB );

        int judgeResult = judge( playerA, playerB );

        std::cout << HandString[playerA] << " vs " << HandString[playerB] << " : " << ResultString[judgeResult+1] << std::endl;
    }

    for ( int i = 0; i < 2; ++i )
    {
        ::FreeLibrary( handler[i] );
    }

    return 0;
}

int judge( const int playerA, const int playerB )
{
    // Aの勝ちなら -1
    // あいこなら   0
    // Bの勝ちなら  1

    int result = playerA - playerB;
    if ( result == -2 )
    {
        result = 1;
    }
    else if ( result == 2 )
    {
        result = -1;
    }
    else
    {
    }
    return result;
}
