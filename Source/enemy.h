/*
    enemy.h

    An abstract base class that represents an enemy.
    it's main purpose is to provide movement and pathfinding functions and utilities to the child classes.
*/

#pragma once


#include "base.h"
#include "entity.h"




class Enemy : public Entity
{
public:


    Enemy();


    // Event methods
    virtual void OnSpawn() = 0;
    virtual void LoadAssets() = 0;

    // Handles movement
    void UpdateMovement();


    // Movement
    void Move(DIRECTION direction_p);


protected:

    // The speed of movement, should be assigned in the child's constructor
    float move_speed_m;

    // A flag that, when true, indicates that the enemy is in motion
    bool moving_m;

private:

    // Used by the Move() method
    float target_x_m, target_y_m;
};