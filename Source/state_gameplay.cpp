// Implements state_gameplay.h

#include "state_gameplay.h"

#include <iostream>

StateGameplay StateGameplay::instance_m;



// StateGameplay::Initialize()
//
void StateGameplay::Initialize(Engine* engine_p)
{
    engine_m = engine_p;

    // load the tiles
    engine_m->LoadTexture("resources/textures/tiles.png");

    // Load a test map
    level_m.LoadFromFile("resources/maps/test.txt");
}



// StateGameplay::Uninitialize()
//
void StateGameplay::Uninitialize()
{
    std::cout << "Uninitialize.\n";
}



// StateGameplay::OnPause()
//
void StateGameplay::OnPause()
{
}



// StateGameplay::OnResume()
//
void StateGameplay::OnResume()
{
}



// StateGameplay::Events()
//
void StateGameplay::Events()
{

    sf::Event e;
    while(engine_m->sfml_window_m.pollEvent(e))
    {
        if(e.type == sf::Event::Closed)
            engine_m->Exit(0);
    }

    level_m.Events();

}



// StateGameplay::Update()
//
void StateGameplay::Update()
{

    // Update level, enemies and the player
    level_m.Update();

}



// StateGameplay::Draw()
//
void StateGameplay::Draw()
{

    // Draw level, enemies and the player
    level_m.Draw(engine_m);

}