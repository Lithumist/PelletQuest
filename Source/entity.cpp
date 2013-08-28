// Implements entity.h

#include "entity.h"
#include "base.h"

#include <iostream>




//####################################################################
//
// Entity::Entity()
//
Entity::Entity()
{
}




//####################################################################
//
// Entity::SetEngine()
//
void Entity::SetEngine(Engine* engine_p)
{
    // Start engine_m to be null
    engine_m = NIL;

    // Handle null pointer error
    if(engine_p == NIL)
    {
        std::cout << "ERROR: null pointer. Entity::Entity()\n";
    }

    // Set the engine pointer
    engine_m = engine_p;
}