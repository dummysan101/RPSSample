// playersample.cpp
#include <cstdlib>
#include "playersample.h"

int GetNextHand( const int previousHand )
{
    return rand() % 3;
}
