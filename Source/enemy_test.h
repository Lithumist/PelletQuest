/*
    enemy_test.h

    A test enemy to help be develop the framework
*/

#pragma once


#include "enemy.h"
#include "base.h"
#include "engine.h"


class EnemyTest : public Enemy
{
public:

    void OnSpawn();
    void LoadAssets();

    void Events(sf::Event e);
    void EventsLoop(sf::Event e);
    void Update();
    void Draw();

protected:

    sf::Sprite sprite_m;

private:
};