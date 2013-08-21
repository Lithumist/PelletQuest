// Implements state_main_menu.h

#include "state_main_menu.h"

#include <iostream>

StateMainMenu StateMainMenu::instance_m;



// StateMainMenu::Initialize()
//
void StateMainMenu::Initialize(Engine* engine_p)
{
    engine_m = engine_p;
    
    // Load all textures
    engine_m->LoadTexture("resources/textures/title.png");

    // Configure all sprites
    spr_title_m.setTexture(*engine_m->GetTexture("resources/textures/title.png"));
}



// StateMainMenu::Uninitialize()
//
void StateMainMenu::Uninitialize()
{
    std::cout << "Uninitialize.\n";
}



// StateMainMenu::OnPause()
//
void StateMainMenu::OnPause()
{
}



// StateMainMenu::OnResume()
//
void StateMainMenu::OnResume()
{
}



// StateMainMenu::Events()
//
void StateMainMenu::Events()
{

    sf::Event e;
    while(engine_m->sfml_window_m.pollEvent(e))
    {
        if(e.type == sf::Event::Closed)
            engine_m->Exit(0);

        if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::S)
        {
            // Temp new game start
        }
    }

}



// StateMainMenu::Update()
//
void StateMainMenu::Update()
{
}



// StateMainMenu::Draw()
//
void StateMainMenu::Draw()
{
    engine_m->sfml_window_m.draw(spr_title_m);
}