/*
    level.h

    A class that loads and renders levels from files.
    The Level class controls the player and enemy classes
*/

#pragma once

#include "engine.h"
#include "player.h"

#include <string>

#define MAP_WIDTH 20
#define MAP_HEIGHT 15

class Level
{
public:

    Level();
    Level(std::string filename_p, Engine* engine_p);

    bool LoadFromFile(std::string filename_p, Engine* engine_p);
    void Clear();

    void Events();
    void Update();
    void Draw(Engine* engine_p);



    Player player_m;

protected:

    // Tile array (fixed size)
    int tiles_m[MAP_WIDTH][MAP_HEIGHT];

    // Tile rectangle coordinates table (initialized in constructor)
    // (Should be part of the engine class)
    sf::IntRect tile_rects_[512];

private:

    // Calculates tile_rects_
    void CalculateTileRects();

};