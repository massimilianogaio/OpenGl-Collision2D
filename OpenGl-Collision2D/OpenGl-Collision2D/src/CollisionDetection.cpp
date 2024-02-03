#include "CollisionDetection.h"
#include <iostream>

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
void CollisionDetection::DectectRigidBodyCollision()
{
	for (int i = 0; i < shapes.size(); i++)
	{
		for (int j = i + 1; j < shapes.size(); j++)
		{
			
			if (IsColliding(shapes[i], shapes[j]))
			{

				float m1 = shapes[i]->rigidBody->getMass();
				float m2 = shapes[j]->rigidBody->getMass();
				vec2 u1 = shapes[i]->rigidBody->getDirection();
				vec2 u2 = shapes[j]->rigidBody->getDirection();

				vec2 v1, v2;

				// lost of energy
				//vec2 v1 = (((m1 - m2)/(m1 + m2)) * u1) + (((2 * m2)/(m1 + m2)) * u2);
				//vec2 v2 = (((2 * m2) / (m1 + m2)) * u1) + (((m2 - m1) / (m1 + m2)) * u2);


				// not lost of energy
				v1.x = ((u1.x * (m1 - m2) + 2.0f * m2 * u2.x) / (m1 + m2));
				v1.y = ((u1.y * (m1 - m2) + 2.0f * m2 * u2.y) / (m1 + m2));

				v2.x = ((u2.x * (m2 - m1) + 2.0f * m1 * u1.x) / (m1 + m2));
				v2.y = ((u2.y * (m2 - m1) + 2.0f * m1 * u1.y) / (m1 + m2));

				shapes[i]->rigidBody->setDirection(v1);
				shapes[j]->rigidBody->setDirection(v2);



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