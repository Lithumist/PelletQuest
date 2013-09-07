/*
    
    weather.h

    A particle system controller that the level class uses to control weather effects

*/


#include "base.h"
#include "engine.h"

#include <SFML/System.hpp>

#include <vector>




#define PARTICLE_COUNT 100

#define SPAWN_TIMER_LIMIT 50

#define PARTICLE_COLOUR_VARIATION 20

#define PARTICLE_BASE_SPEED_RAIN 8
#define PARTICLE_BASE_SPEED_SAND 6
#define PARTICLE_BASE_SPEED_SNOW 2

#define PARTICLE_MAX_SIZE_RAIN 5
#define PARTICLE_MAX_SIZE_SAND 4
#define PARTICLE_MAX_SIZE_SNOW 4



// PARTICLE_MAX_SIZE denotes the max size (in pixels) that a particle can be (square shape)
// SPAWN_TIMER_LIMIT is in milliseconds






enum WEATHER_TYPE {W_NONE, W_RAIN, W_SNOW, W_SAND};







class Particle
{
public:

    Particle();
    Particle(sf::Color colour_p, float x_p, float y_p, float base_speed_p, float max_size_p); // Calls Create()

    void Create(sf::Color colour_p, float x_p, float y_p, float base_speed_p, float max_size_p);
    bool IsDead();

    void Update();
    void Draw(Engine* engine_p);

protected:


    sf::Color colour_m;
    float size_m; // Length of the sides of the square
    float max_size_m;
    float x_m, y_m, x_speed_m, y_speed_m;
    float x_start_m, y_start_m;
    



    void GenerateColourMod(sf::Uint8& colour_byte_p);
    void GenerateSizeMod(float& size_p);
    void GenerateSpeedMod(float& speed);


};







class Weather
{
public:

    // Constructor and pointer setting
    Weather();
    void SetEngine(Engine* engine_p);


    // Weather control methods
    void StartWeather(WEATHER_TYPE type_p); // Starts the drawing and simulation of a specific type of weather system
    void StopWeather(); // Stops the current weather system being simulated (if any)

    // Returns the type of weather system being simulated (W_NONE if no weather is being simulated)
    WEATHER_TYPE IsPlaying()
    {
        if(running_m)
            return current_weather_type_m;
        else
            return W_NONE;
    }


    // Loop methods
    void Draw();
    void Update();


protected:

    // The pointer to the engine (should be checked at the top of every method that uses this)
    Engine* engine_m;

    // The current weather system being simulated (W_NONE if no weather is being simulated)
    WEATHER_TYPE current_weather_type_m;

    // If the simulation is running
    bool running_m;

    // The vector of particles
    //Particle particles_m[PARTICLE_COUNT];
    std::vector<Particle> particles_m;

    // Particle spawn and update variables
    sf::Clock particle_spawn_timer_m;
    unsigned int particle_count_m;

private:
};