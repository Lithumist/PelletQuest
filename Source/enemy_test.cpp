// Implements enemy_test.h

#include "enemy_test.h"

#include <iostream>






// EnemyTest::OnSpawn()
//
void EnemyTest::OnSpawn()
{
    x_m = 0;
    y_m = 0;
}



// EnemyTest::LoadAssets()
//
void EnemyTest::LoadAssets()
{
    if(engine_m == NIL) {
        std::cout << "ERROR: NULL POINTER. EnemyTest::LoadAssets() engine_m is NULL.\n";
        return;
    }

    engine_m->LoadTexture("resources/textures/player.png");
    sprite_m.setTexture(*engine_m->GetTexture("resources/textures/player.png"));

    move_speed_m = 2;
}








// EnemyTest::Events()
//
void EnemyTest::Events(sf::Event e)
{
}



// EnemyTest::Update()
//
void EnemyTest::Update()
{
    // Move right
    Move(D_RIGHT);

    // Handle movement
    Enemy::UpdateMovement();
}



// EnemyTest::Draw()
//
void EnemyTest::Draw()
{

    sprite_m.setPosition(x_m,y_m);
    engine_m->sfml_window_m.draw(sprite_m);

}