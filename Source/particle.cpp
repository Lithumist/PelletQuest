// implements the Particle class in weather.h

#include "weather.h"
#include <cstdlib>

#include <SFML/System.hpp>



Particle::Particle()
{
    colour_m = sf::Color::Red;

    size_m = 2.0f;
    max_size_m = 2.0f;

    x_m = 0.0f;
    y_m = 0.0f;
    x_start_m = 0.0f;
    y_start_m = 0.0f;
    x_speed_m = 0.0f;
    y_speed_m = 0.0f;
}

Particle::Particle(sf::Color colour_p, float x_p, float y_p, float base_speed_p, float max_size_p)
{
    Create(colour_p, x_p, y_p, base_speed_p, max_size_p);
}

void Particle::Create(sf::Color colour_p, float x_p, float y_p, float base_speed_p, float max_size_p)
{
    // Set all values
    colour_m = colour_p;
    size_m = 2.0f;
    max_size_m = max_size_p;
    x_m = x_p;
    y_m = y_p;
    x_start_m = x_p;
    y_start_m = y_p;
    x_speed_m = base_speed_p;
    y_speed_m = base_speed_p;


    // Mutate the colour slightly
    GenerateColourMod(colour_m.r);
    GenerateColourMod(colour_m.g);
    GenerateColourMod(colour_m.b);
    colour_m.a = 210;

    // Generate a random size
    GenerateSizeMod(size_m);

    // Mutate the speed
    GenerateSpeedMod(x_speed_m);
    GenerateSpeedMod(y_speed_m);

}





bool Particle::IsDead()
{
    if(x_m > 640+64 || y_m > 480+64)
        return true;
    else
        return false;
}






void Particle::Update()
{
    // Move particle
    x_m += x_speed_m;
    y_m += y_speed_m;

    // Reset position if dead
    if(IsDead())
    {
        x_m = x_start_m;
        y_m = y_start_m;
    }
}





void Particle::Draw(Engine* engine_p)
{   

    sf::RectangleShape particle(sf::Vector2f(size_m, size_m));  // set size
    particle.setPosition(x_m, y_m); // set position
    particle.setFillColor(colour_m); // set colour

    engine_p->sfml_window_m.draw(particle);

}













////////////////////////
// Randomisation Code //
////////////////////////



void Particle::GenerateColourMod(sf::Uint8& colour_byte_p)
{

    sf::Uint8 mod = rand() % PARTICLE_COLOUR_VARIATION;
    int sign = rand() % 2;

    if(sign == 0)
    {
        // -
        if(colour_byte_p - mod < 0)
            colour_byte_p = 0;
        else
            colour_byte_p -= mod;
    }
    else
    {
        // +
        if(colour_byte_p + mod > 255)
            colour_byte_p = 255;
        else
            colour_byte_p += mod;
    }

}



void Particle::GenerateSizeMod(float& size_p)
{
    size_p *= rand() % (int)max_size_m;
}


void Particle::GenerateSpeedMod(float& speed)
{
    // TODO: Clean up this code and make it readable. (May require rewrite)
    float mod = (float)rand()/(float)RAND_MAX;
    mod -= 0.5;
    mod *= 2;

    speed += mod;
}