// implements the Particle class in weather.h

#include "weather.h"
#include <cstdlib>



Particle::Particle()
{
    colour_m = sf::Color::Red;

    size_m = 1.0f;

    x_m = 0.0f;
    y_m = 0.0f;
    x_start_m = 0.0f;
    y_start_m = 0.0f;
    x_speed_m = 0.0f;
    y_speed_m = 0.0f;
}

Particle::Particle(sf::Color colour_p, float x_p, float y_p, float x_speed_p, float y_speed_p)
{
    Create(colour_p, x_p, y_p, x_speed_p, y_speed_p);
}

void Particle::Create(sf::Color colour_p, float x_p, float y_p, float x_speed_p, float y_speed_p)
{
    // Set all values
    colour_m = colour_p;
    size_m = 2.0f;
    x_m = x_p;
    y_m = y_p;
    x_start_m = x_p;
    y_start_m = y_p;
    x_speed_m = x_speed_p;
    y_speed_m = y_speed_p;


    // Mutate the colour slightly
    GenerateColourMod(colour_m.r);
    GenerateColourMod(colour_m.g);
    GenerateColourMod(colour_m.b);
    GenerateColourMod(colour_m.a);

    // Generate a random size
    GenerateSizeMod(size_m);

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
    // Convert the 8 bit value to 16 bit 
    // (This is to handle cases where the value becomes bigger than 255)
    sf::Uint16 colour_byte_16 = (sf::Uint16)colour_byte_p;

    // Add +/- PARTICLE_COLOUR_VARIATION to the value
    colour_byte_16 = rand() % (PARTICLE_COLOUR_VARIATION*2);
    colour_byte_16 -= PARTICLE_COLOUR_VARIATION;

    // Restrict the value to unsigned 8 bit limits
    if(colour_byte_16 < 0)
        colour_byte_16 = 0;
    if(colour_byte_16 > 255)
        colour_byte_16 = 255;

    // Convert back to 8 bit and set the original reference
    colour_byte_p = (sf::Uint8)colour_byte_16;
}



void Particle::GenerateSizeMod(float& size_p)
{
    size_p *= rand() % PARTICLE_MAX_SIZE;
}


float Particle::GenerateSpeedMod()
{
    // TODO: Finish this
    return 1.0f;
}