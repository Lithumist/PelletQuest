// Implements state_gameplay.h

#include "state_gameplay.h"

#include <iostream>

StateGameplay StateGameplay::instance_m;



// StateGameplay::Initialize()
//
void StateGameplay::Initialize(Engine* engine_p)
{
    engine_m = engine_p;

    // load all game textures
    engine_m->LoadTexture("resources/textures/tiles.png");
    engine_m->LoadTexture("resources/textures/player.png");

    // Load a test map
    level_m.LoadFromFile("resources/maps/test.txt", engine_p);
}



// StateGameplay::Uninitialize()
//
void StateGameplay::Uninitialize()
{
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

        // Handle level events
        level_m.EventsLoop(engine_m, e);
    }


    level_m.Events(engine_m, e);

}



// StateGameplay::Update()
//
void StateGameplay::Update()
{

    // Update level, enemies and the player
    level_m.Update(engine_m);

}



// StateGameplay::Draw()
//
void StateGameplay::Draw()
{

    // Draw level, enemies and the player
    level_m.Draw(engine_m);

}