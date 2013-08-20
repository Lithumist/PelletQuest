/*
	main.cpp

	Entry point of the whole program, only invokes the engine.
*/

#include "engine.h"
#include "state_main_menu.h"

int main()
{

	Engine e;
    e.Run(StateMainMenu::GetInstance());

	return 0;
}