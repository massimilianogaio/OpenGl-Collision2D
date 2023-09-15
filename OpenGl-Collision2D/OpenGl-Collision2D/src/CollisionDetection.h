#pragma once
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Particle.h"
#include <vector>
using namespace glm;

class CollisionDetection {
public:
	CollisionDetection(vec2 windowSize, std::vector<Particle*>& particles);
	void DetectCollision();
	
private:
	
	vec2 halfWindowSize;
	std::vector<Particle*>& particles;

	void DectectWindowCollision(Particle* particle);
};