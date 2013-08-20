// Implements engine.h

#include "engine.h"
#include "state.h"



// Engine::Engine()
//
Engine::Engine()
{
    running_m = false;
}



// Engine::Run()
//
int Engine::Run(State* initial_state_p)
{
    // Initialize first state
	states_m.push_back(initial_state_p);
    initial_state_p->Initialize(this);

    // Run the main loop
    running_m = true;
    while(running_m)
    {
        State* current_state = states_m.back();
        current_state->Events();
        current_state->U(); // update
        current_state->D(); // draw
    }

    // Game has exites
    for(unsigned int s=0; s<states_m.size(); s++)
        states_m[s]->Uninitialize();

    return return_value_m;

}



// Engine::Exit()
//
void Engine::Exit(int return_code_p)
{
    return_value_m = return_code_p;
    running_m = false;
}



// Engine::ChangeState()
//
void Engine::ChangeState(State* new_state_p)
{
    states_m.back()->Uninitialize();
    states_m.pop_back();

    states_m.push_back(new_state_p);
    new_state_p->Initialize(this);
}



// Engine::PushState()
//
void Engine::PushState(State* new_state_p)
{
    states_m.back()->Pause();

    states_m.push_back(new_state_p);
    new_state_p->Initialize(this);
}



// Engine::PopState()
//
void Engine::PopState()
{
    states_m.back()->Uninitialize();
    states_m.pop_back();

    states_m.back()->Resume();
}