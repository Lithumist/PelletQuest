/*
    state_main_menu.h

    The main menu state, the first thing that appears in the game
*/

#pragma once

#include "state.h"

class StateMainMenu : public State
{
public:

    void Initialize(Engine* engine_p);
    void Uninitialize();

	void OnPause();
	void OnResume();

	void Events();
	void Update();
	void Draw();


    static StateMainMenu* GetInstance(){ return &instance_m; }

protected:

    StateMainMenu() {}

private:

    static StateMainMenu instance_m;
    Engine* engine_m;

    sf::Sprite spr_title_m;

};