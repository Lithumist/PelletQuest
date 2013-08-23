/*
    level.h

    A class that loads levels from files. Updates, renders and switches them.
    The Level class controls the player and enemy classes

    Also declares a structure that holds map warp data
*/

#pragma once

#include "engine.h"
#include "player.h"

#include <string>

#define MAP_WIDTH 20
#define MAP_HEIGHT 15




/*
    WarpData structure
*/
struct WarpData
{

    std::string filename; // the filename of the map to warp to (relative to game executable)
    int x; // the x position (in tiles) where the player will start
    int y; // ^


    // Resets the warp data to aid in debugging
    void Clear()
    {
        filename = "undefined";
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



    Player player_m;

protected:

    // Tile array (fixed size)
    int tiles_m[MAP_WIDTH][MAP_HEIGHT];

    // Tile rectangle coordinates table (initialized in constructor)
    // (Should be part of the engine class)
    sf::IntRect tile_rects_[512];

    // The map boundry warp data
    WarpData warp_north_m;
    WarpData warp_south_m;
    WarpData warp_east_m;
    WarpData warp_west_m;

private:

    // Calculates tile_rects_
    void CalculateTileRects();

};