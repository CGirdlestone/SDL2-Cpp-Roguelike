#include "Particle.h"

Particle::Particle(int _x, int _y, int _size, int _red, int _green, int _blue):
x(_x), y(_y), size(_size), red(_red), green(_green), blue(_blue)
{
	steps = 0;
	lifetime = 300;
	currentLife = 300;
}

Particle::~Particle()
{

}
