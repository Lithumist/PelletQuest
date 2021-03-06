/*
	engine.h

	A class for managing game states in a stack
*/

#pragma once

#include "base.h"

#include <vector>
#include <string>
#include <map>

#include "SFML/Graphics.hpp"




#define SCREENSHOT_BUTTON sf::Keyboard::C




class State;

class Engine
{
public:

    Engine();

	/////
	// Interface Methods
	/////

	// Called by main.cpp to run the engine
	int Run(State* initial_state_p);

    // Called by a state to exit the game immediately
    void Exit(int return_code_p);

	// Replaces the current state with a new one
	void ChangeState(State* new_state_p);

	// Pushes another state onto the stack and switches to it
	void PushState(State* new_state_p);

	// Pops the current state from the stack and switches to the one that was under it
	void PopState();

    // Loads an SFML texture (Doesn't load same texture twice)
    bool LoadTexture(std::string filename_p);

    // Returns a pointer to an SFML texture already loaded (Returns an error texture on failure to prevent crashing)
    sf::Texture* GetTexture(std::string filename_p);

    // Returns the error texture
    sf::Texture* GetErrorTexture();

    // Saves screenshot of screen
    void TakeScreenshot();



	/////
	// Interface Properties
	/////

	// The state stack
	std::vector<State*> states_m;

    // ...
    sf::RenderWindow sfml_window_m;

    // The rectangles that define the tile boundries on the tile sheet (calculated in the constructor)
    sf::IntRect tile_rects_m[512];

protected:

	/////
	// Properties
	/////
    
private:

    bool running_m;
    int return_value_m;
    bool loaded_new_texture_m;

    std::map<std::string, sf::Texture> textures_m;

};