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
    engine_m = NIL;
    level_m = NIL;
    type_m = 0;
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
    IsPointerNull((void*)engine_p,"Entity::SetEngine()");

    // Set the engine pointer
    engine_m = engine_p;
}





//####################################################################
//
// Entity::SetLevel()
//
void Entity::SetLevel(Level* level_p)
{
    // Start engine_m to be null
    level_m = NIL;

    // Handle null pointer error
    IsPointerNull((void*)level_p,"Entity::SetLevel()");

    // Set the engine pointer
    level_m = level_p;
}