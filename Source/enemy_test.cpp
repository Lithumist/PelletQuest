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
    if(IsPointerNull((void*)engine_m,"EnemyTest::LoadAssets()"))
        return;

    engine_m->LoadTexture("resources/textures/player.png");
    sprite_m.setTexture(*engine_m->GetTexture("resources/textures/player.png"));

    move_speed_m = 2;
}








// EnemyTest::Events()
//
void EnemyTest::Events(sf::Event e)
{
    if(IsPointerNull((void*)engine_m,"EnemyTest::Events()"))
        return;
    if(IsPointerNull((void*)level_m,"EnemyTest::Events()"))
        return;
}



// EnemyTest::EventsLoop()
//
void EnemyTest::EventsLoop(sf::Event e)
{
    if(IsPointerNull((void*)engine_m,"EnemyTest::EventsLoop()"))
        return;
    if(IsPointerNull((void*)level_m,"EnemyTest::EventsLoop()"))
        return;
}




// EnemyTest::Update()
//
void EnemyTest::Update()
{
    if(IsPointerNull((void*)engine_m,"EnemyTest::Update()"))
        return;
    if(IsPointerNull((void*)level_m,"EnemyTest::Update()"))
        return;

    // Move right
    Move(D_RIGHT);

    // Handle movement
    Enemy::UpdateMovement();
}



// EnemyTest::Draw()
//
void EnemyTest::Draw()
{

    if(IsPointerNull((void*)engine_m,"EnemyTest::Draw()"))
        return;
    if(IsPointerNull((void*)level_m,"EnemyTest::Draw()"))
        return;

    sprite_m.setPosition(x_m,y_m);
    engine_m->sfml_window_m.draw(sprite_m);

}