// implements the Weather class in weather.h

#include "weather.h"
#include <cstdlib>

#include <SFML/System.hpp>


Weather::Weather()
{
    engine_m = NIL;

    current_weather_type_m = W_NONE;
}


void Weather::SetEngine(Engine* engine_p)
{
    IsPointerNull((void*)engine_p,"Weather::SetEngine()");

    engine_m = engine_p;
}






void Weather::StartWeather(WEATHER_TYPE type_p)
{
    running_m = true;
    current_weather_type_m = type_p;


    sf::Color col;

    /*
    switch(current_weather_type_m)
    {
        case W_RAIN:
            col.r = 27;
            col.g = 126;
            col.b - 224;
        break;

        case W_SNOW:
            col.r = 227;
            col.g = 227;
            col.b - 227;
        break;

        case W_SAND:
            col.r = 214;
            col.g = 203;
            col.b - 118;
        break;
    }
    */
    col = sf::Color::Blue;


    int counter = 0;
    for(unsigned int c=0; c<PARTICLE_COUNT; c++)
    {
        float x_spawn, y_spawn;
        if(counter == 0)
        {
            x_spawn = (rand() % 768) - 64;
            y_spawn = -64;
        }
        else
        {
            x_spawn = -64;
            y_spawn = (rand() % 608) - 64;
        }

        Particle np(col,x_spawn,y_spawn,4,4);
        particles_m.push_back(np);

        ++ counter;
        if(counter >= 2)
            counter = 0;
    }

    
    // Restart spawn timer
    particle_spawn_timer_m.restart();
    particle_count_m = 0;


}


void Weather::StopWeather()
{
    running_m = false;
    particle_count_m = 0;
    particles_m.clear();
}





void Weather::Update()
{
    if(IsPointerNull((void*)engine_m,"Weather::Update()"))
        return;

    if(!running_m)
        return;


    if(particle_count_m < PARTICLE_COUNT)
    {
        sf::Time el = particle_spawn_timer_m.getElapsedTime();
        if(el.asMilliseconds() >= SPAWN_TIMER_LIMIT)
        {
            particle_count_m ++;
            //if(particle_count == PARTICLE_COUNT)
            //{
                //std::cout << "ERROR PARTICLE COUNT";
                //particle_count_m = 
            //}
            particle_spawn_timer_m.restart();
        }
    }



    for(unsigned int p=0; p<particle_count_m; p++)
    {
        particles_m[p].Update();
    }
}




void Weather::Draw()
{
    if(IsPointerNull((void*)engine_m,"Weather::Draw()"))
        return;

    if(!running_m)
        return;

    
    for(unsigned int p=0; p<particle_count_m; p++)
    {
        particles_m[p].Draw(engine_m);
    }
}