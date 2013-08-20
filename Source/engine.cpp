// Implements engine.h

#include "engine.h"

int Engine::Run(State* initial_state_p)
{
	states_m.push_back(initial_state_p);
}