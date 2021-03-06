// Implements player.h

#include "player.h"
#include "level.h"

#include <iostream>




// Player::Player()
//
Player::Player()
{

    // Initialize everything to default values
    NewLevel(0,0);

    direction_m = 90; // up
}





// Player::NewLevel()
//
void Player::NewLevel(int x_p, int y_p)
{

    x_m = (float)(x_p*32);
    y_m = (float)(y_p*32);
    x_speed_m = 0.0f;
    y_speed_m = 0.0f;

    // Doesn't set direction

    moving_m = false;
    target_x_m = 0.0f;
    target_y_m = 0.0f;

}



// Player::SetTextures()
//
void Player::SetTextures()
{
    if(IsPointerNull((void*)engine_m,"Player::SetTextures()"))
        return;

    // Attempt to get player textures
    spr_player_m.setTexture(*engine_m->GetTexture("resources/textures/player.png"));


}




// Player::Events()
//
void Player::Events(sf::Event e)
{

    if(IsPointerNull((void*)engine_m,"Player::Events()"))
        return;
    if(IsPointerNull((void*)level_m,"Player::Events()"))
        return;

    int tile_x, tile_y;
    tile_x = (int)(x_m/32);
    tile_y = (int)(y_m/32);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && level_m->PlaceWalkable(tile_x+1,tile_y))
        MoveToTile(tile_x+1,tile_y);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && level_m->PlaceWalkable(tile_x-1,tile_y))
        MoveToTile(tile_x-1,tile_y);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && level_m->PlaceWalkable(tile_x,tile_y+1))
        MoveToTile(tile_x,tile_y+1);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && level_m->PlaceWalkable(tile_x,tile_y-1))
        MoveToTile(tile_x,tile_y-1);

}



// Player::EventsLoop()
//
void Player::EventsLoop(sf::Event e)
{
    if(IsPointerNull((void*)engine_m,"Player::EventsLoop()"))
        return;
    if(IsPointerNull((void*)level_m,"Player::EventsLoop()"))
        return;
}



// Player::Update()
//
void Player::Update()
{

    if(IsPointerNull((void*)engine_m,"Player::Update()"))
        return;
    if(IsPointerNull((void*)level_m,"Player::Update()"))
        return;
    

    // This code is only executed whilst the player is in motion
    if(moving_m)
    {
        // Check if the player reached the target it was moving towards
        if(x_m == target_x_m && y_m == target_y_m)
        {
            moving_m = false;
            x_speed_m = 0.0f;
            y_speed_m = 0.0f;
        }

        // Check for out of map events
        if(y_m < 0)
            level_m->PlayerOutsideLevel(D_UP);
        if(y_m+32 > 480)
            level_m->PlayerOutsideLevel(D_DOWN);
        if(x_m+32 > 640)
            level_m->PlayerOutsideLevel(D_RIGHT);
        if(x_m < 0)
            level_m->PlayerOutsideLevel(D_LEFT);
    }


    // Move player
    x_m += x_speed_m;
    y_m += y_speed_m;

}



// Player::Draw()
//
void Player::Draw()
{

    if(IsPointerNull((void*)engine_m,"Player::Draw()"))
        return;
    if(IsPointerNull((void*)level_m,"Player::Draw()"))
        return;


    spr_player_m.setPosition(x_m,y_m);

    engine_m->sfml_window_m.draw(spr_player_m);

}



// Player::MoveToTile
void Player::MoveToTile(int x_tile_p, int y_tile_p)
{

    // Dont initialize a new move if the player is moving already
    if(moving_m)
        return;

    // Calculate pixel coordinates
    target_x_m = (float)(x_tile_p*32);
    target_y_m = (float)(y_tile_p*32);

    // Check if the player is already there
    if(x_m == target_x_m && y_m == target_y_m)
        return;

    // Calculate x and y speed
    int xdif, ydif, len;
    xdif = (int)(target_x_m-x_m);
    ydif = (int)(target_y_m-y_m);
    len = (int)sqrt( (xdif*xdif) + (ydif*ydif) );

    if(xdif != 0)
    {
        x_speed_m = (int)(xdif / len);
        x_speed_m *= PLAYER_SPEED;
        x_speed_m = (int)floor(x_speed_m+0.5);
    }
    else
        x_speed_m = 0.0f;

    if(ydif != 0)
    {
        y_speed_m = (int)(ydif / len);
        y_speed_m *= PLAYER_SPEED;
        y_speed_m = (int)floor(y_speed_m+0.5);
    }
    else
        y_speed_m = 0.0f;

    // Make the update loop check to see if the player reached the target
    moving_m = true;

}