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