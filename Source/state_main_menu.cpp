// Implements state_main_menu.h

#include "state_main_menu.h"

#include <iostream>

StateMainMenu StateMainMenu::instance_m;



// StateMainMenu::Initialize()
//
void StateMainMenu::Initialize(Engine* engine_p)
{
    engine_m = engine_p;
    std::cout << "Initialize.\n";
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
}