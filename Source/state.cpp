// Implements state.h


#include "state.h"


State::State()
{
    is_paused_m = false;
}

void State::Pause(){ is_paused_m = true; }
void State::Resume(){ is_paused_m = false; }

void State::U()
{
    if(!is_paused_m)
        Update();
}


void State::D()
{
    if(!is_paused_m)
        Draw();
}

