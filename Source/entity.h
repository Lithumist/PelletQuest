/*
    entity.h

    An abstract base class that represents all game
    objects (player, enemies, pellets) at the most basic level
*/

#pragma once




#include <SFML/Graphics.hpp>



class Engine;


class Entity
{
public:



    // Get
    float GetX()        {   return x_m;   }
    float GetY()        {   return y_m;   }

    int GetTileX()      {   return (int)(x_m/32);   }
    int GetTileY()      {   return (int)(y_m/32);   }

    float GetXSpeed()   {   return x_speed_m;   }
    float GetYSpeed()   {   return y_speed_m;   }


#
    // Set
    void SetPosition(float x_p, float y_p) {
        x_m = x_p;
        y_m = y_p;
    }

    void SetSpeed(float x_speed_p, float y_speed_p) {
        x_speed_m = x_speed_p;
        y_speed_m = y_speed_p;
    }



    // Constructor
    Entity();

    // Set's the pointer to the engine instance
    void SetEngine(Engine* engine_p);



    // Game loop methods
    virtual void Events(sf::Event e) = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;




    // Type
    /*
        0 normal
        1 enemy
    */
    int type_m;


protected:


    // Pointer to the engine instance
    Engine* engine_m;

    // Positions
    float x_m, y_m;
    int x_tile_m, y_tile_m;

    // Speed
    float x_speed_m, y_speed_m;

private:
};