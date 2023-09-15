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

	DectectWindowCollision();
	DectectRigidBodyCollision();

}
void CollisionDetection::DectectRigidBodyCollision()
{
	for (int i = 0; i < particles.size(); i++)
	{
		for (int j = i + 1; j < particles.size(); j++)
		{
			
			if (IsColliding(particles[i], particles[j]))
			{
				
				vec2 dir1 = particles[i]->rigidBody->getDirection();
				particles[i]->rigidBody->setDirection(vec2(dir1.x * -1, dir1.y * -1));
				vec2 dir2 = particles[j]->rigidBody->getDirection();
				particles[j]->rigidBody->setDirection(vec2(dir2.x * -1, dir2.y * -1));
				//std::cout << "IsColliding" << particles[i]->rigidBody->getDirection().x << std::endl;
			}
		}
	}
}
bool CollisionDetection::IsColliding(Particle* p1, Particle* p2)
{
	vec3 pivot1 = p1->transform.getPosition();
	vec3 pivot2 = p2->transform.getPosition();
	

	float radious1XSize = 20.0f * p1->transform.getScale().x;
	float radious2XSize = 20.0f * p2->transform.getScale().x;

	float radious1YSize = 20.0f * p1->transform.getScale().x;
	float radious2YSize = 20.0f * p2->transform.getScale().y;

	return IsIntersectingXAxis(pivot1, pivot2, radious1XSize, radious2XSize) && IsIntersectingYAxis(pivot1, pivot2, radious1YSize, radious2YSize);
	
}
bool CollisionDetection::IsIntersectingXAxis(vec3 pivot1, vec3 pivot2, float radiousSize1, float radiousSize2)
{
	float pivotXDist = 0;
	if (pivot1.x < 0 && pivot2.x >= 0)
	{
		pivotXDist = abs(pivot1.x) + pivot2.x;
	}
	else if (pivot2.x < 0 && pivot1.x >= 0)
	{
		pivotXDist = abs(pivot2.x) + pivot1.x;
	}
	else
	{
		pivotXDist = abs(pivot1.x - pivot2.x);
	}
	//std::cout << " 1) " << pivotXDist << " < " << radiousSize1 + radiousSize2 << std::endl;
	return pivotXDist < radiousSize1 + radiousSize2;
}
bool CollisionDetection::IsIntersectingYAxis(vec3 pivot1, vec3 pivot2, float radiousSize1, float radiousSize2)
{
	float pivotYDist = 0;
	if (pivot1.y < 0 && pivot2.y >= 0)
	{
		pivotYDist = abs(pivot1.y) + pivot2.y;
	}
	else if (pivot2.y < 0 && pivot1.y >= 0)
	{
		pivotYDist = abs(pivot2.y) + pivot1.y;
	}
	else
	{
		pivotYDist = abs(pivot1.y - pivot2.y);
	}
	//std::cout << " 2) " << pivotYDist << " < " << radiousSize1 + radiousSize2 << std::endl;

	return pivotYDist < radiousSize1 + radiousSize2;
}
void CollisionDetection::DectectWindowCollision()
{
	for (int i = 0; i < particles.size(); i++)
	{
		Particle* particle = particles[i];
		vec3 pos = particle->transform.getPosition();
		vec2 dir = particle->rigidBody->getDirection();
		if (pos.x >= halfWindowSize.x || pos.x <= -halfWindowSize.x)
		{
			particle->rigidBody->setDirection(vec2(dir.x * -1, dir.y));
		}
		if (pos.y >= halfWindowSize.y || pos.y <= -halfWindowSize.y)
		{
			particle->rigidBody->setDirection(vec2(dir.x, dir.y * -1));
		}
	}
}
