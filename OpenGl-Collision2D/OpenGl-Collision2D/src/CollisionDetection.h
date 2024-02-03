#pragma once
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Particle.h"
#include <vector>
using namespace glm;

class CollisionDetection {
public:
	CollisionDetection(vec2 windowSize, std::vector<Shape*>& particles);
	void DetectCollision();
	
private:
	
	vec2 halfWindowSize;
	std::vector<Shape*>& shapes;

	void DectectRigidBodyCollision();
	bool IsColliding(Shape* p1, Shape* p2);
	bool IsIntersectingXAxis(vec3 pivot1, vec3 pivot2, float radiousSize1, float radiousSize2);
	bool IsIntersectingYAxis(vec3 pivot1, vec3 pivot2, float radiousSize1, float radiousSize2);
	void DectectWindowCollision();
	bool IsOutsideWindowBounds(float position, float size, float windowBound);
};