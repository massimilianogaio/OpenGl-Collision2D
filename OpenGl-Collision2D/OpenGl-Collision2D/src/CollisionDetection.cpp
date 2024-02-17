#include "CollisionDetection.h"
#include <iostream>
#include <unordered_set>

std::unordered_set<int> CollidingObjects;

CollisionDetection::CollisionDetection(vec2 windowSize, std::vector<Shape*>& particles)
	: halfWindowSize(windowSize), shapes(particles)
{
	this->halfWindowSize = halfWindowSize;
	this->shapes = std::vector<Shape*>(particles);
}

void CollisionDetection::DetectCollision()
{
	DectectWindowCollision();
	DectectRigidBodyCollision();
}
glm::vec2 ComputeVelocity(glm::vec2 v1, glm::vec2 v2, float m1, float m2, glm::vec2 x1, glm::vec2 x2) {
	glm::vec2 relativeVelocity = v1 - v2;
	glm::vec2 relativePosition = x1 - x2;
	float distanceSquared = glm::dot(relativePosition, relativePosition);
	float dotProduct = glm::dot(relativeVelocity, relativePosition);

	return v1 - ((2.0f * m2) / (m1 + m2)) * (dotProduct / distanceSquared) * relativePosition;
}

void CollisionDetection::DectectRigidBodyCollision()
{
	for (int i = 0; i < shapes.size(); i++)
	{
		for (int j = i + 1; j < shapes.size(); j++)
		{
			int hash = (int)(shapes[i])+(int)(shapes[j]);
			bool alreadyColliding = CollidingObjects.find(hash) != CollidingObjects.end();
			bool isColliding = IsColliding(shapes[i], shapes[j]);
			if (!alreadyColliding && isColliding)
			{
				CollidingObjects.insert(hash);

				float m1 = shapes[i]->rigidBody->getMass();
				float m2 = shapes[j]->rigidBody->getMass();
				vec2 v1 = shapes[i]->rigidBody->getDirection() * shapes[i]->rigidBody->getAcceleration();
				vec2 v2 = shapes[j]->rigidBody->getDirection() * shapes[j]->rigidBody->getAcceleration();

				vec3 x1 = shapes[i]->transform.getPosition();
				vec3 x2 = shapes[j]->transform.getPosition();

				vec2 dir1 = ComputeVelocity(v1, v2, m1, m2, x1, x2) / shapes[i]->rigidBody->getAcceleration();
				vec2 dir2 = ComputeVelocity(v2, v1, m2, m1, x2, x1) / shapes[j]->rigidBody->getAcceleration();

				shapes[i]->rigidBody->setDirection(dir1);
				shapes[j]->rigidBody->setDirection(dir2);
			}
			else if(alreadyColliding && !isColliding)
			{
				CollidingObjects.erase(hash);
			}
		}
	}
}
bool CollisionDetection::IsColliding(Shape* p1, Shape* p2)
{
	vec3 pivot1 = p1->transform.getPosition();
	vec3 pivot2 = p2->transform.getPosition();

	float radious1Size = p1->getScaledSize();
	float radious2Size = p2->getScaledSize();

	return IsIntersectingXAxis(pivot1, pivot2, radious1Size, radious2Size) && IsIntersectingYAxis(pivot1, pivot2, radious1Size, radious2Size);
	
}
bool CollisionDetection::IsIntersectingXAxis(vec3 pivot1, vec3 pivot2, float radiousSize1, float radiousSize2)
{
	float pivotDist = 0;
	if (pivot1.x < 0 && pivot2.x >= 0)
	{
		pivotDist = abs(pivot1.x) + pivot2.x;
	}
	else if (pivot2.x < 0 && pivot1.x >= 0)
	{
		pivotDist = abs(pivot2.x) + pivot1.x;
	}
	else
	{
		pivotDist = abs(pivot1.x - pivot2.x);
	}
	return pivotDist <= radiousSize1 + radiousSize2;
}
bool CollisionDetection::IsIntersectingYAxis(vec3 pivot1, vec3 pivot2, float radiousSize1, float radiousSize2)
{
	float pivotDist = 0;
	if (pivot1.y < 0 && pivot2.y >= 0)
	{
		pivotDist = abs(pivot1.y) + pivot2.y;
	}
	else if (pivot2.y < 0 && pivot1.y >= 0)
	{
		pivotDist = abs(pivot2.y) + pivot1.y;
	}
	else
	{
		pivotDist = abs(pivot1.y - pivot2.y);
	}
	return pivotDist < radiousSize1 + radiousSize2;
}
void CollisionDetection::DectectWindowCollision()
{
	for (int i = 0; i < shapes.size(); i++)
	{
		vec3 pos = shapes[i]->transform.getPosition();
		vec2 dir = shapes[i]->rigidBody->getDirection();
		float shapeSize = shapes[i]->getScaledSize();
		if (IsOutsideWindowBounds(pos.x, shapeSize, halfWindowSize.x))
		{
			shapes[i]->rigidBody->setDirection(vec2(dir.x * -1, dir.y));
		}
		if (IsOutsideWindowBounds(pos.y, shapeSize, halfWindowSize.y))
		{
			shapes[i]->rigidBody->setDirection(vec2(dir.x, dir.y * -1));
		}
	}
}
bool CollisionDetection::IsOutsideWindowBounds(float position, float size, float windowBound)
{
	return (position + size >= windowBound) || (position - size <= -windowBound);
}