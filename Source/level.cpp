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
Level::Level(std::string filename_p)
{
    Clear();
    CalculateTileRects();
    LoadFromFile(filename_p);
}



// Level::LoadFromFile()
//
bool Level::LoadFromFile(std::string filename_p)
{

    Clear();

    // Load the tiles if they haven't been loaded already

    std::ifstream level_file(filename_p);
    if(!level_file.is_open())
        return false;

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

    level_file.close();

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

}



// Level::Events()
//
void Level::Events()
{
}



// Level::Update()
//
void Level::Update()
{
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