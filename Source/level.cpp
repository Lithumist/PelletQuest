// Implements level.h

#include "level.h"
#include "enemy_test.h"

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
            //std::cout << tiles_m[x][y] << " ";
        }
        //std::cout << std::endl;
    }

    // Read collision
    for(int y=0; y<MAP_HEIGHT; y++)
    {
        for(int x=0; x<MAP_WIDTH; x++)
        {
            level_file >> collision_m[x][y];
            //std::cout << tiles_m[x][y] << " ";
        }
        //std::cout << std::endl;
    }


    // Read boundry warp data (north, south, east, west)
    std::string use_pos;

    // North
    level_file >> warp_north_m.filename; //std::cout << warp_north_m.filename << std::endl;
    if(warp_north_m.filename != "none")
    {
        warp_north_active_m = true;
        level_file >> use_pos;
        if(use_pos == "p") // 'p' for position
        {
            warp_north_m.use_position = true;
            level_file >> warp_north_m.x;
            level_file >> warp_north_m.y;
        }
        else
            warp_north_m.use_position = false;
    }
    else
        warp_north_active_m = false;


    // South
    level_file >> warp_south_m.filename; //std::cout << warp_south_m.filename << std::endl;
    if(warp_south_m.filename != "none")
    {
        warp_south_active_m = true;
        level_file >> use_pos;
        if(use_pos == "p")
        {
            warp_south_m.use_position = true;
            level_file >> warp_south_m.x;
            level_file >> warp_south_m.y;
        }
        else
            warp_south_m.use_position = false;
    }
    else
        warp_south_active_m = false;


    // East
    level_file >> warp_east_m.filename; //std::cout << warp_east_m.filename << std::endl;
    if(warp_east_m.filename != "none")
    {
        warp_east_active_m = true;
        level_file >> use_pos;
        if(use_pos == "p")
        {
            warp_east_m.use_position = true;
            level_file >> warp_east_m.x;
            level_file >> warp_east_m.y;
        }
        else
            warp_east_m.use_position = false;
    }
    else
        warp_east_active_m = false;


    // West
    level_file >> warp_west_m.filename; //std::cout << warp_west_m.filename << std::endl;
    if(warp_west_m.filename != "none")
    {
        warp_west_active_m = true;
        level_file >> use_pos;
        if(use_pos == "p")
        {
            warp_west_m.use_position = true;
            level_file >> warp_west_m.x;
            level_file >> warp_west_m.y;
        }
        else
            warp_west_m.use_position = false;
    }
    else
        warp_west_active_m = false;


    // Close the level file
    level_file.close();


    // Initialize the player and add him to the map
    player_m.SetTextures(engine_p, this);
    player_m.SetPosition(0.0f,0.0f);
    player_m.SetEngine(engine_p);
    entities_m.push_back(&player_m);

    // Add a test enemy
    enemy_m.SetEngine(engine_p);
    enemy_m.LoadAssets();
    entities_m.push_back(&enemy_m);

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
            collision_m[x][y] = 0;
        }
    }


    // Clear boundry warp data
    warp_north_m.Clear(); warp_north_active_m = false;
    warp_south_m.Clear(); warp_south_active_m = false;
    warp_east_m.Clear(); warp_east_active_m = false;
    warp_west_m.Clear(); warp_west_active_m = false;


    // Clear entities
    entities_m.clear();


    // Unvalidate the collision map
    generated_collision_map_m = false;

}



// Level::Events()
//
void Level::Events()
{

    // Handle all entity events
    for(unsigned int e=0; e<entities_m.size(); e++)
        entities_m[e]->Events();

}



// Level::Update()
//
void Level::Update(Engine* engine_p)
{

    // Update all entities
    for(unsigned int e=0; e<entities_m.size(); e++)
        entities_m[e]->Update();
    





    ////////////////////////////////////////
    ////// React to map boundry warps //////
    //                                    //
    //                                    //
    // This code doesn't belong here :/   //
    //                                    //
    // The player should have a pointer   //
    // to thelevel instance and do this   //
    // itself                             //
    //                                    //
    //                                    //
    ////////////////////////////////////////

    // North
    //
    if(player_m.flag_outside_map_north && warp_north_active_m)
    {
        int xtile, ytile; // the position to warp the player to
        if(warp_north_m.use_position)
        {
            xtile = warp_north_m.x;
            ytile = warp_north_m.y;
        }
        else
        {
            xtile = player_m.GetTileX();
            ytile = 14;
        }
        LoadFromFile(warp_north_m.filename, engine_p);
        player_m.NewLevel(xtile, ytile);
    }

    // South
    //
    if(player_m.flag_outside_map_south && warp_south_active_m)
    {
        int xtile, ytile;
        if(warp_south_m.use_position)
        {
            xtile = warp_south_m.x;
            ytile = warp_south_m.y;
        }
        else
        {
            xtile = player_m.GetTileX();
            ytile = 0;
        }
        LoadFromFile(warp_south_m.filename, engine_p);
        player_m.NewLevel(xtile, ytile);
    }

    // East
    //
    if(player_m.flag_outside_map_east && warp_east_active_m)
    {
        int xtile, ytile;
        if(warp_east_m.use_position)
        {
            xtile = warp_east_m.x;
            ytile = warp_east_m.y;
        }
        else
        {
            xtile = 0;
            ytile = player_m.GetTileY();
        }
        LoadFromFile(warp_east_m.filename, engine_p);
        player_m.NewLevel(xtile, ytile);
    }

    // West
    //
    if(player_m.flag_outside_map_west && warp_west_active_m)
    {
        int xtile, ytile;
        if(warp_west_m.use_position)
        {
            xtile = warp_west_m.x;
            ytile = warp_west_m.y;
        }
        else
        {
            xtile = 19;
            ytile = player_m.GetTileY();
        }
        LoadFromFile(warp_west_m.filename, engine_p);
        player_m.NewLevel(xtile, ytile);
    }

}



// Level::Draw()
//
void Level::Draw(Engine* engine_p)
{

    // Draw map tiles
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


    // Draw all entities
    for(unsigned int e=0; e<entities_m.size(); e++)
    {
        entities_m[e]->Draw();
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



// Level::GetCollisionMap()
//
CollisionMap Level::GetCollisionMap()
{

    if(!generated_collision_map_m)
        GenerateCollisionMap();

    return collision_map_m;

}



// Level::GenerateCollisionMap()
//
void Level::GenerateCollisionMap()
{

    for(int y=0; y<MAP_HEIGHT; y++)
    {
        for(int x=0; x<MAP_WIDTH; x++)
        {
            if(collision_m[x][y] == 1)
                collision_map_m.position[x][y] = SOLID;
            else
                collision_map_m.position[x][y] = WALKABLE;
        }
    }

}



// Level::PlaceWalkable()
//
bool Level::PlaceWalkable(int x_tile_p, int y_tile_p)
{

    if(collision_m[x_tile_p][y_tile_p] == 1)
        return false;
    else
        return true;

}