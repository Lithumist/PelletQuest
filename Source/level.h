/*
    level.h

    A class that loads levels from files. Updates, renders and switches them.
    The Level class controls the player and enemy classes

    Also declares a structure that holds map warp data
*/

#pragma once

#include "engine.h"
#include "player.h"
#include "enemy_test.h"
#include "entity.h"
#include "path.h"
#include "base.h"

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


    // Constructors and destructor
    Level(); // Creates a blank map
    Level(std::string filename_p, Engine* engine_p); // Load's a map from a file into the instance, Calls LoadFromFile()
    ~Level();

    // Loading and clearing
    bool LoadFromFile(std::string filename_p, Engine* engine_p); // Load's a map from a file into the instance
    void Clear(); // Clears the instance to a blank map (deallocates all entities)

    // Loop
    void Events(); // Handles the events that apply to the level as a whole
    void Update(Engine* engine_p); // Update's the level and it's individual entities within
    void Draw(Engine* engine_p); // Draw's the level and it's individual entities within

    // Events
    void PlayerOutsideLevel(DIRECTION direction_outside_p, Engine* engine_p); // Called by the player when it goes outside the screen

    // Adding entities
    bool AddEntity(Entity* entity_p); // Add's an entity to the level. Level class handles memory management (must be created on the heap) (assumes entity has been initialized and set up already)

    
    /*
        Get
    */

    // Collision Map
    CollisionMap GetCollisionMap(); // return's the collision map and call's GenerateCollisionMap if one hasn't been generated yet
    void GenerateCollisionMap(); // Generate's a new collision map overriting the previous 

    // Find out if a place is walkable
    bool PlaceWalkable(int x_tile_p, int y_tile_p);



    std::vector<Entity*> entities_m; // memory is managed here
    std::vector<Enemy*> enemies_m; // these pointers point to the same places as entities_m do
    Player* player_m; // player entity

protected:

    // ###############
    // Map Data
    // ###############

    // The graphical tile data
    int tiles_m[MAP_WIDTH][MAP_HEIGHT];

    // Tile collision data
    int collision_m[MAP_WIDTH][MAP_HEIGHT];

    // The map boundry warp data
    WarpData warp_north_m; bool warp_north_active_m;
    WarpData warp_south_m; bool warp_south_active_m;
    WarpData warp_east_m; bool warp_east_active_m;
    WarpData warp_west_m; bool warp_west_active_m;

    // The collision map
    CollisionMap collision_map_m;
    bool generated_collision_map_m; // if the collision map is valid

private:

};