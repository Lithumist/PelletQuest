// Implements enemy.h

#include "enemy.h"

#include <math.h>




// Enemy::Move()
//
void Enemy::Move(DIRECTION direction_p)
{

    // Dont initialize a new move if the player is moving already
    if(moving_m)
        return;

    // Get target pixel coordinates
    switch(direction_p)
    {
        case D_UP:
            target_x_m = (float)( GetTileX() * 32 );
            target_y_m = (float)( (GetTileY()-1) * 32 );
        break;

        case D_DOWN:
            target_x_m = (float)( GetTileX() * 32 );
            target_y_m = (float)( (GetTileY()+1) * 32 );
        break;

        case D_LEFT:
            target_x_m = (float)( (GetTileX()-1) * 32 );
            target_y_m = (float)( GetTileY() * 32 );
        break;

        case D_RIGHT:
            target_x_m = (float)( (GetTileX()+1) * 32 );
            target_y_m = (float)( GetTileY() * 32 );
        break;
    }

    // Check if the player is already there
    if(x_m == target_x_m && y_m == target_y_m)
        return;

    // Calculate x and y speed
    int xdif, ydif, len;
    xdif = (int)(target_x_m-x_m);
    ydif = (int)(target_y_m-y_m);
    len = (int)sqrt( (float)(xdif*xdif) + (ydif*ydif) ); // float cast to select one overload

    if(xdif != 0)
    {
        x_speed_m = (int)(xdif / len);
        x_speed_m *= move_speed_m;
        x_speed_m = (int)floor(x_speed_m+0.5);
    }
    else
        x_speed_m = 0.0f;

    if(ydif != 0)
    {
        y_speed_m = (int)(ydif / len);
        y_speed_m *= move_speed_m;
        y_speed_m = (int)floor(y_speed_m+0.5);
    }
    else
        y_speed_m = 0.0f;

    // Make the update loop check to see if the player reached the target
    moving_m = true;

}



// Enemy::Update()
//
void Enemy::Update()
{

    if(moving_m)
    {
        // Check if the player reached the target it was moving towards
        if(x_m == target_x_m && y_m == target_y_m)
        {
            moving_m = false;
            x_speed_m = 0.0f;
            y_speed_m = 0.0f;
        }
    }


    // Move player
    x_m += x_speed_m;
    y_m += y_speed_m;

}