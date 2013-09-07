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
    engine_m = NIL;
    debug_view_m = false;
}




// Level::~Level()
//
Level::~Level()
{
    // Free all memory
    Clear();
}




// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Level::Level()
//
Level::Level(std::string filename_p, Engine* engine_p)
{
    engine_m = NIL;
    debug_view_m = false;

    // Save engine pointer and spit out errors
    /*
        WARNING!!!!! BAD DESIGN!!!!!

        
        Do not just update this method with engine pointer setting.
        The method below it needs to be updated as well!!

    */
    IsPointerNull((void*)engine_p,"Level::Level()");
    engine_m = engine_p;
    weather.SetEngine(engine_p);

    LoadFromFile(filename_p, engine_p);
}





// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Level::LoadFromFile()
//
// *Doesn't check for invalid inputs*
//
//
bool Level::LoadFromFile(std::string filename_p, Engine* engine_p)
{
    // Clear the level class
    Clear();


    // Save engine pointer and spit out errors
    IsPointerNull((void*)engine_p,"Level::Level()");
    engine_m = engine_p;
    weather.SetEngine(engine_p);


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







    // Loads enemies from file and adds to level
    //
    // Note this needs to be at the end of the level loading code to work!
    //
    while(!level_file.eof())
    {

        std::string enemy_type;
        int enemy_position_x, enemy_position_y;

        level_file >> enemy_type;
        level_file >> enemy_position_x;
        level_file >> enemy_position_y;


        if(enemy_type == "ENEMY_TEST")
        {

            EnemyTest* enemy = new EnemyTest;
            enemy->SetEngine(engine_p);
            enemy->SetLevel(this);
            enemy->LoadAssets();
            enemy->SetPosition(float(enemy_position_x*32), float(enemy_position_y*32));

            AddEntity(enemy);

        }


        else if(enemy_type == "ENEMY_TEST2")
        {

            std::cout << "ENEMY_TEST2 NOT IMPLEMENTED YET!\n";

        }



        else // Error, undefined enemy type
            std::cout << "ERROR: BAD MAP FILE. " << filename_p << " undefined enemy type " << enemy_type << "." << std::endl;



    }


    // Close the level file
    level_file.close();

    
    // Initialize the player and add him to the map
    player_m = new Player;
    player_m->SetEngine(engine_p);
    player_m->SetLevel(this);
    player_m->SetTextures();
    player_m->SetPosition(0.0f,0.0f);
    AddEntity(player_m);
    //player_m.SetTextures(engine_p, this);
    //player_m.SetPosition(0.0f,0.0f);
    //player_m.SetEngine(engine_p);
    //entities_m.push_back(&player_m);

    // Add a test enemy
    /*
    EnemyTest* enemy = new EnemyTest;
    enemy->SetEngine(engine_p);
    enemy->SetLevel(this);
    enemy->LoadAssets();
    AddEntity(enemy);
    //enemy_m.SetEngine(engine_p);
    //enemy_m.LoadAssets();
    //entities_m.push_back(&enemy_m);
    */








    // Do the OnSpawn events of all the enemies
    for(Enemy* e : enemies_m)
    {
        e->OnSpawn();
    }

    return true;
}





// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Level::Clear()
//
void Level::Clear()
{
    // Stop weather
    weather.StopWeather();

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


    // Delete all used memory by entities
    for(unsigned int e=0; e < entities_m.size(); e++)
    {
        if(entities_m[e] != NIL)
        {
            delete entities_m[e];
            entities_m[e] = NIL;
        }
    }
    // Clear the vector
    entities_m.clear();
    // Reserve space for all entities
    entities_m.reserve(MAX_ENTITIES);


    // Clear the enemies vector
    enemies_m.clear();


    // Unvalidate the collision map
    generated_collision_map_m = false;

}





// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Level::Events()
// 
void Level::Events(sf::Event ee)
{

    if(IsPointerNull((void*)engine_m,"LevelTest::Events()"))
        return;


    // Handle all entity events
    for(unsigned int e=0; e<entities_m.size(); e++)
        entities_m[e]->Events(ee);

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Level::EventsLoop()
// 
// Note this is called within a while loop polling for events
//
void Level::EventsLoop(sf::Event ee)
{

    if(IsPointerNull((void*)engine_m,"LevelTest::EventsLoop()"))
        return;



    if(ee.type == sf::Event::KeyPressed && ee.key.code == sf::Keyboard::D)
        ToggleDebugView();

    if(ee.type == sf::Event::KeyPressed && ee.key.code == sf::Keyboard::W)
    {
        if(weather.IsPlaying() == W_NONE)
            weather.StartWeather(W_SNOW);
        else
            weather.StopWeather();
    }

    // Handle all entity events
    for(unsigned int e=0; e<entities_m.size(); e++)
        entities_m[e]->EventsLoop(ee);

}





// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Level::Update()
//
void Level::Update()
{
     if(IsPointerNull((void*)engine_m,"LevelTest::Update()"))
        return;

    // Update all entities
    for(unsigned int e=0; e<entities_m.size(); e++)
        entities_m[e]->Update();

    // Update weather system
    weather.Update();

}





// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Level::Draw()
//
void Level::Draw()
{

    if(IsPointerNull((void*)engine_m,"LevelTest::Draw()"))
        return;



    // Draw map tiles
    sf::Texture* tiles_texture = engine_m->GetTexture("resources/textures/tiles.png");

    for(int y=0; y<MAP_HEIGHT; y++)
    {
        for(int x=0; x<MAP_WIDTH; x++)
        {
            int tile_number = tiles_m[x][y];

            sf::Sprite tile;
            tile.setTexture(*tiles_texture);
            tile.setTextureRect(sf::IntRect(engine_m->tile_rects_m[tile_number].left,engine_m->tile_rects_m[tile_number].top,32,32));
            tile.setPosition((float)x*32,(float)y*32);

            engine_m->sfml_window_m.draw(tile);
        }
    }


    // Draw all entities
    for(unsigned int e=0; e<entities_m.size(); e++)
    {
        entities_m[e]->Draw();
    }


    // Draw debug view collision tiles
    if(debug_view_m)
    {
        for(int y=0; y<MAP_HEIGHT; y++)
        {
            for(int x=0; x<MAP_WIDTH; x++)
            {
                int tile_number = collision_m[x][y];

                if(tile_number == 1)
                {
                    sf::Sprite tile;
                    tile.setTexture(*engine_m->GetErrorTexture());
                    tile.setScale(0.5,0.5); // Make it 32*32 (error texture is 64*64)
                    tile.setPosition((float)x*32,(float)y*32);
                    tile.setColor( sf::Color(255,255,255,128) );

                    engine_m->sfml_window_m.draw(tile);
                }

            }
        }
    }


    // Draw weather
    weather.Draw();

}





// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Level::GetCollisionMap()
//
CollisionMap Level::GetCollisionMap()
{

    if(!generated_collision_map_m)
        GenerateCollisionMap();

    return collision_map_m;

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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






// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Level::PlaceWalkable()
//
bool Level::PlaceWalkable(int x_tile_p, int y_tile_p)
{

    // If tile is outside of map boundries, say that it's walkable
    if(x_tile_p < 0)
        return true;
    if(x_tile_p > MAP_WIDTH-1)
        return true;
    if(y_tile_p < 0)
        return true;
    if(y_tile_p > MAP_HEIGHT-1)
        return true;


    // Check the collision map for tiles within the map's boundries
    if(collision_m[x_tile_p][y_tile_p] == 1)
        return false;
    else
        return true;

}







// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Level::PlayerOutsideLevel()
//
void Level::PlayerOutsideLevel(DIRECTION direction_outside_p)
{

    if(IsPointerNull((void*)engine_m,"LevelTest::PlayerOutsideLevel()"))
        return;




    // North
    //
    if(direction_outside_p == D_UP && warp_north_active_m)
    {
        int xtile, ytile; // the position to warp the player to
        if(warp_north_m.use_position)
        {
            xtile = warp_north_m.x;
            ytile = warp_north_m.y;
        }
        else
        {
            xtile = player_m->GetTileX();
            ytile = MAP_HEIGHT-1;
        }
        LoadFromFile(warp_north_m.filename,engine_m);
        player_m->NewLevel(xtile, ytile);
    }

    // South
    //
    if(direction_outside_p == D_DOWN && warp_south_active_m)
    {
        int xtile, ytile;
        if(warp_south_m.use_position)
        {
            xtile = warp_south_m.x;
            ytile = warp_south_m.y;
        }
        else
        {
            xtile = player_m->GetTileX();
            ytile = 0;
        }
        LoadFromFile(warp_south_m.filename, engine_m);
        player_m->NewLevel(xtile, ytile);
    }

    // East
    //
    if(direction_outside_p == D_RIGHT && warp_east_active_m)
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
            ytile = player_m->GetTileY();
        }
        LoadFromFile(warp_east_m.filename, engine_m);
        player_m->NewLevel(xtile, ytile);
    }

    // West
    //
    if(direction_outside_p == D_LEFT && warp_west_active_m)
    {
        int xtile, ytile;
        if(warp_west_m.use_position)
        {
            xtile = warp_west_m.x;
            ytile = warp_west_m.y;
        }
        else
        {
            xtile = MAP_WIDTH-1;
            ytile = player_m->GetTileY();
        }
        LoadFromFile(warp_west_m.filename, engine_m);
        player_m->NewLevel(xtile, ytile);
    }

}








// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Level::AddEntity()
//
bool Level::AddEntity(Entity* entity_p)
{

    if(entities_m.size() >= MAX_ENTITIES)
    {
        std::cout << "ERROR, MAX ENTITIES HIT, Level::AddEntity() failed, max entities reached.\n";
        return false; // Failure
    }


    // There's space for another entity


    // Add the new entity
    entities_m.push_back(entity_p);

    // Register it with the enemy vector if it's an enemy
    if(entity_p->type_m == 1)
        enemies_m.push_back((Enemy*)entity_p);

    // Success
    return true;

}