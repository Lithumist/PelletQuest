/*
    player.h

    A class that handles the player
*/

#pragma once

#include "engine.h"
#include "entity.h"



// Player Constants
#define PLAYER_SPEED 4.0f;




class Level;




class Player : public Entity
{
public:

    Player();

    void SetTextures(Engine* engine_p);

    // Resets the player for a new level.
    // x_p and y_p are it's new position (in tiles)
    void NewLevel(int x_p, int y_p);

    void Events() override;
    void Update() override;
    void Draw() override;

    void MoveToTile(int x_tile_p, int y_tile_p);



    // Event flags
    bool flag_outside_map_north;
    bool flag_outside_map_south;
    bool flag_outside_map_east;
    bool flag_outside_map_west;


protected:
private:





    sf::Sprite spr_player_m;

    int direction_m; // 0-right, 90-up, 180-left, 270-down
    bool moving_m;

    float target_x_m, target_y_m;

};