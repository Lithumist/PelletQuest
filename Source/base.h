/*
    base.h

    Declares macros and enums that improve readability
*/

#pragma once


#include <iostream>
#include <string>



// NIL
#define NIL 0



 // DIRECTION
enum DIRECTION {D_UP, D_DOWN, D_LEFT, D_RIGHT};



// Map dimensions
#define MAP_WIDTH 20
#define MAP_HEIGHT 15



// Max entities
#define MAX_ENTITIES 1024



// NULL pointer checking function. Outputs error
inline bool IsPointerNull(void* pointer_p, std::string function_name_p)
{
    if(pointer_p == NIL)
    {
        std::cout << "ERROR. NULL POINTER. " << function_name_p << std::endl;
        return true;
    }
    else
        return false;
}