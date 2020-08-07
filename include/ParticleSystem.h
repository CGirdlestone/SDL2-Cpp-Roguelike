
#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <map>
#include <vector>
#include "System.h"
#include "Events.h"
#include "Particle.h"

class EventManager;

class ParticleSystem : public System
{
public:
  ParticleSystem(EventManager* eventManager, std::map<int, GameObject*> *entities);
  virtual ~ParticleSystem();
	void addParticle(int _x, int _y, int _size, int _red, int _green, int _blue);
	void ageParticles(uint32_t dt);
	void update(uint32_t dt);
	void purgeParticles(){ particles.clear(); }

  virtual void notify(OnHitEvent event);

	std::vector<Particle> particles;
private:
  EventManager* m_eventManager;
  std::map<int, GameObject*> *m_entities;
};


#endif
