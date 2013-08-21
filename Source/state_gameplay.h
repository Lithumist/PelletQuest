/*
    state_gameplay.h

    The gameplay state
*/

#pragma once

#include "state.h"

class StateGameplay : public State
{
public:

    void Initialize(Engine* engine_p);
    void Uninitialize();

	void OnPause();
	void OnResume();

	void Events();
	void Update();
	void Draw();


    static StateGameplay* GetInstance(){ return &instance_m; }

protected:

    StateGameplay() {}

private:

    static StateGameplay instance_m;
    Engine* engine_m;

};