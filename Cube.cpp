#include "stdafx.h"
#include "Cube.h"


Cube::Cube(vec3 pos, vec3 color, float size, std::string textureName)
{
	this->pos = pos;
	this->diffuse = color;
	this->size = size;
	this->textureName = textureName;
	this->weight = 100;
	this->radius = size / 2;
	this->objectType = "cube";
	health = -1000;
}


Cube::~Cube()
{
}

void Cube::Render()
{
	if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture(textureName);
	}
	

	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient.x);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse.x);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular.x);

	glPushMatrix();

		glTranslatef(pos.x, pos.y, pos.z);

		glBegin(GL_QUADS);

			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f( size / 2, -size / 2, -size / 2);
			glTexCoord2f(0, 0);
			glVertex3f( size / 2, -size / 2,  size / 2);
			glTexCoord2f(1, 0);
			glVertex3f(-size / 2, -size / 2,  size / 2);
			glTexCoord2f(1, 1);
			glVertex3f(-size / 2, -size / 2, -size / 2);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-size / 2,  size / 2, -size / 2);
			glTexCoord2f(0, 0);
			glVertex3f(-size / 2,  size / 2,  size / 2);
			glTexCoord2f(1, 0);
			glVertex3f( size / 2,  size / 2,  size / 2);
			glTexCoord2f(1, 1);
			glVertex3f( size / 2,  size / 2, -size / 2);

			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-size / 2, -size / 2, -size / 2);
			glTexCoord2f(1, 0);
			glVertex3f(-size / 2, -size / 2,  size / 2);
			glTexCoord2f(1, 1);
			glVertex3f(-size / 2,  size / 2,  size / 2);
			glTexCoord2f(0, 1);
			glVertex3f(-size / 2,  size / 2, -size / 2);

			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f( size / 2,  size / 2, -size / 2);
			glTexCoord2f(0, 1);
			glVertex3f( size / 2,  size / 2,  size / 2);
			glTexCoord2f(0, 0);
			glVertex3f( size / 2, -size / 2,  size / 2);
			glTexCoord2f(1, 0);
			glVertex3f( size / 2, -size / 2, -size / 2);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-size / 2,  size / 2, -size / 2);
			glTexCoord2f(0, 1);
			glVertex3f( size / 2,  size / 2, -size / 2);
			glTexCoord2f(0, 0);
			glVertex3f( size / 2, -size / 2, -size / 2);
			glTexCoord2f(1, 0);
			glVertex3f(-size / 2, -size / 2, -size / 2);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1, 1);
			glVertex3f( size / 2,  size / 2,  size / 2);
			glTexCoord2f(0, 1);
			glVertex3f(-size / 2,  size / 2,  size / 2);
			glTexCoord2f(0, 0);
			glVertex3f(-size / 2, -size / 2,  size / 2);
			glTexCoord2f(1, 0);
			glVertex3f( size / 2, -size / 2,  size / 2);

		glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Cube::Update()
{
	pos.x += force.x / weight;
	pos.z += force.z / weight;

	force.x /= 1.03;
	force.y /= 1.03;
	force.z /= 1.03;
}