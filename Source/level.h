/*
    level.h

    A class that loads levels from files. Updates, renders and switches them.
    The Level class controls the player and enemy classes

    Also declares a structure that holds map warp data
*/

#pragma once

#include "engine.h"
#include "player.h"
#include "entity.h"
#include "path.h"

#include <vector>
#include <string>






/*
    WarpData structure
*/
struct WarpData
{

    std::string filename; // the filename of the map to warp to (relative to game executable)
    bool use_position; // Weather to use the x and y values below (true), or start the player based on their position in the previous map
    int x; // the x position (in tiles) where the player will start
    int y; // ^


    // Resets the warp data to aid in debugging
    void Clear()
    {
        filename = "undefined";
        use_position = false;
        x = -1;
        y = -1;
    }

};





/*
    Level Class
*/
class Level
{
public:

    Level();
    Level(std::string filename_p, Engine* engine_p);

    bool LoadFromFile(std::string filename_p, Engine* engine_p);
    void Clear();

    void Events();
    void Update(Engine* engine_p);
    void Draw(Engine* engine_p);

    CollisionMap GetCollisionMap(); // return's the collision map and call's GenerateCollisionMap if one hasn't been generated yet
    void GenerateCollisionMap(); // Generate's a new collision map overriting the previous one



    std::vector<Entity*> entities_m;
    Player player_m; // player entity

protected:

    // Tile array (fixed size)
    int tiles_m[MAP_WIDTH][MAP_HEIGHT];

    // Collision array
    int collision_m[MAP_WIDTH][MAP_HEIGHT];

    // Tile rectangle coordinates table (initialized in constructor)
    // (Should be part of the engine class)
    sf::IntRect tile_rects_[512];

    // The map boundry warp data
    WarpData warp_north_m; bool warp_north_active_m;
    WarpData warp_south_m; bool warp_south_active_m;
    WarpData warp_east_m; bool warp_east_active_m;
    WarpData warp_west_m; bool warp_west_active_m;


    // The collision map
    CollisionMap collision_map_m;
    bool generated_collision_map_m; // if the collision map is valid

private:

    // Calculates tile_rects_
    void CalculateTileRects();

};