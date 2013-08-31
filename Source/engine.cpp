// Implements engine.h

#include "engine.h"
#include "state.h"

#include <iostream>



// Engine::Engine()
//
Engine::Engine()
{
    running_m = false;
    loaded_new_texture_m = true;


    // Iterate through the 512 tile sheet tiles
    for(int y=0; y<32; y++)
    {
        for(int x=0; x<16; x++)
        {

            tile_rects_m[y*16+x].left = 32*x;
            tile_rects_m[y*16+x].top = 32*y;

            // (Doesn't set the width or height because they are a constant 32 pixels)

        }
    }
}



// Engine::Run()
//
int Engine::Run(State* initial_state_p)
{
    // Initialize SFML
    sfml_window_m.create(sf::VideoMode(640,480,32),"Pellet Quest!",sf::Style::Close);
    sfml_window_m.setFramerateLimit(60);

    // Load error texture
    if(!LoadTexture("resources/textures/error.png"))
    {
        std::cout << "FATAL ERROR: Failed to load resources/textures/error.png\n";
        sfml_window_m.close();
        return 1;
    }

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

        // Draw
        sfml_window_m.clear(sf::Color::Black);
        current_state->D();
        sfml_window_m.display();
    }


    // *One of the states exited the game*


    // Unitialize all states
    for(unsigned int s=0; s<states_m.size(); s++)
        states_m[s]->Uninitialize();

    // Unitialize SFML
    sfml_window_m.close();

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



// Engine::LoadTexture()
//
bool Engine::LoadTexture(std::string filename_p)
{
    if(textures_m.count(filename_p) == 0)
    {
        // Load new texture
        sf::Texture texture;
        if(!texture.loadFromFile(filename_p))
        {
            //std::cout << "ERROR: Failed to load texture '" << filename_p << "'\n"; // Commented out because SFML outputs it's own error
            return false;
        }

        textures_m[filename_p] = texture;
        return true;

    }
    else // texture already loaded
        return true;
}



// Engine::GetTexture()
//
sf::Texture* Engine::GetTexture(std::string filename_p)
{

    std::map<std::string,sf::Texture>::iterator it = textures_m.find(filename_p);
    if(it == textures_m.end())
    {
        // Return error texture to prevent crashing
        return &textures_m["resources/textures/error.png"];
    }
    else
        return &textures_m[filename_p]; // return texture

}