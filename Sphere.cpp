#include "stdafx.h"
#include "Sphere.h"


Sphere::Sphere(vec3 pos, vec3 color, float radius, float weight)
{
	this->pos = pos;
	this->diffuse = color;
	this->radius = radius;
	this->weight = weight;
	objectType = "sphere";
	health = -1000;
	radiusChangePerUpdate = 0;
}


Sphere::~Sphere(void)
{
}

void Sphere::Render()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient.x);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse.x);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular.x);

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glutSolidSphere(radius, 24, 24);
	glPopMatrix();
}

void Sphere::Update()
{
	pos.x += force.x / weight;
	pos.y += force.y / weight;
	pos.z += force.z / weight;

	force.x /= 1.2;
	force.y /= 1.2;
	force.z /= 1.2;

	radius += radiusChangePerUpdate;

	if (radius <= 0)
	{
		isAlive = false;
	}
}