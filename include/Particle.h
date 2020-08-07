#ifndef PARTICLE_H
#define PARTICLE_H

struct Particle
{
	Particle(int _x, int _y, int _size, int _red, int _green, int _blue);
	~Particle();
	int x, y; 
	int size;
	int red, green, blue;
	int steps;
	int lifetime;
	int currentLife;
};

#endif
