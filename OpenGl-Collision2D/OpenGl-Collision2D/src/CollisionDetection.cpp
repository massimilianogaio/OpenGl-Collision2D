#include "CollisionDetection.h"
#include <iostream>

CollisionDetection::CollisionDetection(vec2 windowSize, std::vector<Particle*>& particles)
	: halfWindowSize(windowSize), particles(particles)
{
	this->halfWindowSize = halfWindowSize;
	this->particles = std::vector<Particle*>(particles);
}

void CollisionDetection::DetectCollision()
{
	for (int i = 0; i < particles.size(); i++)
	{
		DectectWindowCollision(particles[i]);
	}
}
void CollisionDetection::DectectWindowCollision(Particle* particle)
{
	
	vec3 pos = particle->transform.getPosition();
	vec2 dir = particle->rigidBody.getDirection();
	if (pos.x >= halfWindowSize.x || pos.x <= -halfWindowSize.x)
	{
		particle->rigidBody.setDirection(vec2(dir.x * -1, dir.y));
	}
	if (pos.y >= halfWindowSize.y || pos.y <= -halfWindowSize.y)
	{
		particle->rigidBody.setDirection(vec2(dir.x, dir.y * -1));
	}
}
