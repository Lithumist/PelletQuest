// Implements level.h

#include "level.h"

#include <fstream>
#include <iostream> // debug only

#include<SFML/Graphics.hpp>



// Level::Level()
//
Level::Level()
{
    Clear();
    CalculateTileRects();
}



// Level::Level()
//
Level::Level(std::string filename_p, Engine* engine_p)
{
    Clear();
    CalculateTileRects();
    LoadFromFile(filename_p, engine_p);
}



// Level::LoadFromFile()
//
// *Doesn't check for invalid inputs*
//
//
bool Level::LoadFromFile(std::string filename_p, Engine* engine_p)
{
    // Clear the level class
    Clear();


    // Open the level file
    std::ifstream level_file(filename_p);
    if(!level_file.is_open())
    {
        std::cout << "Map loading failed, couldn't open file " << filename_p << std::endl;
        return false;
    }


    // Read tiles
    for(int y=0; y<MAP_HEIGHT; y++)
    {
        for(int x=0; x<MAP_WIDTH; x++)
        {
            level_file >> tiles_m[x][y];
            std::cout << tiles_m[x][y] << " ";
        }
        std::cout << std::endl;
    }


    // Read boundry warp data (north, south, east, west)
    level_file >> warp_north_m.filename; std::cout << warp_north_m.filename << std::endl;
    level_file >> warp_north_m.x;
    level_file >> warp_north_m.y;

    level_file >> warp_south_m.filename; std::cout << warp_south_m.filename << std::endl;
    level_file >> warp_south_m.x;
    level_file >> warp_south_m.y;

    level_file >> warp_east_m.filename; std::cout << warp_east_m.filename << std::endl;
    level_file >> warp_east_m.x;
    level_file >> warp_east_m.y;

    level_file >> warp_west_m.filename; std::cout << warp_west_m.filename << std::endl;
    level_file >> warp_west_m.x;
    level_file >> warp_west_m.y;


    // Close the level file
    level_file.close();


    // Initialize the player
    player_m.SetTextures(engine_p);
    player_m.SetPosition(0.0f,0.0f);

    return true;
}



// Level::Clear()
//
void Level::Clear()
{

    // Reset tiles
    for(int y=0; y<MAP_HEIGHT; y++)
    {
        for(int x=0; x<MAP_WIDTH; x++)
        {
            tiles_m[x][y] = 0;
        }
    }


    // Clear boundry warp data
    warp_north_m.Clear();
    warp_south_m.Clear();
    warp_east_m.Clear();
    warp_west_m.Clear();

}



// Level::Events()
//
void Level::Events()
{

    // Handle player events
    player_m.Events();

}



// Level::Update()
//
void Level::Update(Engine* engine_p)
{

    // Update the player
    player_m.Update();

    // React to map boundry warps
    if(player_m.flag_outside_map_north)
    {
        int xtile, ytile;        // -
        xtile = warp_north_m.x;  // - Save the previous map's warp location before loading the new one
        ytile = warp_north_m.y;  // -
        LoadFromFile(warp_north_m.filename, engine_p);
        player_m.NewLevel(xtile, ytile);
    }
    if(player_m.flag_outside_map_south)
    {
        int xtile, ytile;
        xtile = warp_south_m.x;
        ytile = warp_south_m.y;
        LoadFromFile(warp_south_m.filename, engine_p);
        player_m.NewLevel(xtile, ytile);
    }
    if(player_m.flag_outside_map_east)
    {
        int xtile, ytile;
        xtile = warp_east_m.x;
        ytile = warp_east_m.y;
        LoadFromFile(warp_east_m.filename, engine_p);
        player_m.NewLevel(xtile, ytile);
    }
    if(player_m.flag_outside_map_west)
    {
        int xtile, ytile;
        xtile = warp_west_m.x;
        ytile = warp_west_m.y;
        LoadFromFile(warp_west_m.filename, engine_p);
        player_m.NewLevel(xtile, ytile);
    }

}



// Level::Draw()
//
void Level::Draw(Engine* engine_p)
{

    // Draw tiles
    sf::Texture* tiles_texture = engine_p->GetTexture("resources/textures/tiles.png");

    for(int y=0; y<MAP_HEIGHT; y++)
    {
        for(int x=0; x<MAP_WIDTH; x++)
        {
            int tile_number = tiles_m[x][y];

            sf::Sprite tile;
            tile.setTexture(*tiles_texture);
            tile.setTextureRect(sf::IntRect(tile_rects_[tile_number].left,tile_rects_[tile_number].top,32,32));
            tile.setPosition((float)x*32,(float)y*32);

            engine_p->sfml_window_m.draw(tile);
        }
    }


    // Draw player
    player_m.Draw(engine_p);

}



// Level::CalculateTileRects()
//
void Level::CalculateTileRects()
{
    
    // Iterate through the 512 tile sheet tiles
    for(int y=0; y<32; y++)
    {
        for(int x=0; x<16; x++)
        {

            tile_rects_[y*16+x].left = 32*x;
            tile_rects_[y*16+x].top = 32*y;

            // (Doesn't set the width or height because they are a constant 32 pixels)

        }
    }

}