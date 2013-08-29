/*
    path.h

    A class that represents a path trough a map that anything can follow.
    Uses A* pathfinding algorithm and assumes that all nodes are equal.

    Also declares a tile map structure that it uses to juge walkable tiles from solid ones.
    The level class has a method to generate this
*/

#pragma once



#include "base.h"

#include <vector>





// Collision Map structure

enum COLLISION_MAP_TILE { WALKABLE, SOLID };

struct CollisionMap
{
    COLLISION_MAP_TILE position[MAP_WIDTH][MAP_HEIGHT];
};




// Path class
class Path
{
public:

    Path();
    Path(int x_start_p, int y_start_p, int x_target_p, int y_target_p, CollisionMap collision_map_p); // just calls the GeneratePath() method

    bool GeneratePath(int x_start_p, int y_start_p, int x_target_p, int y_target_p, CollisionMap collision_map_p);



    std::vector<DIRECTION> path_m; // The final path generated in GeneratePath()


protected:

    // The tile collision map
    CollisionMap collision_map_m;

    // Start and end points
    int x_start_m, y_start_m;
    int x_target_m, y_target_m;

private:
};