// playersample.h
#include <windows.h>

#define EXPORT extern __declspec(dllexport)

extern "C"
{
EXPORT int GetNextHand( const int previousHand );
};
