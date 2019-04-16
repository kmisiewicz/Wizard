#include "stdafx.h"
#include "Spell.h"


Spell::Spell(vec3 pos, vec3 castDir, float radius, float weight, vec3 castPosition, int spellType)
{
	this->pos = pos;
	this->radius = radius;
	this->weight = weight;
	this->castPosition = castPosition;
	this->castDir = castDir;
	radiusChangePerUpdate = 0;
	counter = 0;
	objectType = "spell";
	this->spellType = spellType;
	health = -1000;
	switch (spellType)
	{
	case 1: this->diffuse = vec3(1, 0, 0);
		break;
	case 2: this->diffuse = vec3(0.1, 1, 0.2);
		break;
	case 3: this->diffuse = vec3(0, 0.2, 1);
		break;
	default: this->diffuse = vec3(1, 1, 1);
	}
	int i;
	for (i = 1; i < 200; i++)
	{
		Particle[i].Xpos = 0;
		Particle[i].Ypos = -1;
		Particle[i].Zpos = 0;
		Particle[i].Xmov = (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1) *
			rand() % 11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1
				) * rand() % 11) + 1) * 0.005);
		Particle[i].Zmov = (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1) *
			rand() % 11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1
				) * rand() % 11) + 1) * 0.005);
		Particle[i].Red = 1;
		Particle[i].Green = 1;
		Particle[i].Blue = 1;
		Particle[i].Scalez = 0.05;
		Particle[i].Direction = 0;
		Particle[i].Acceleration = ((((((8 - 5 + 2) * rand() % 11) + 5
			) - 1 + 1) * rand() % 11) + 1) * 0.02;
		Particle[i].Deceleration = 0.0025;
	}
	textureName1 = "particle";
	textureName2 = "particle1";
}


Spell::~Spell(void)
{
}

void Spell::Render()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient.x);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse.x);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular.x);

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glEnable(GL_LIGHT2);
	GLfloat l2_ambient[] = { ambient.x, ambient.y, ambient.z };
	GLfloat l2_diffuse[] = { diffuse.x,diffuse.y,diffuse.z };
	GLfloat l2_specular[] = { specular.x, specular.y, specular.z };
	GLfloat l2_position[] = { pos.x, pos.y, pos.z, 0.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, l2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, l2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, l2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, l2_position);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.8);
	glutSolidSphere(radius, 24, 24);
	
	glDisable(GL_CULL_FACE);
	for (int i = 1; i < 200; i++)
	{
		glPushMatrix();

		glTranslatef(Particle[i].Xpos, Particle[i].Ypos, Particle[i].Zpos);
		glRotatef(Particle[i].Direction - 90, 0, 0, 1);

		glScalef(Particle[i].Scalez, Particle[i].Scalez, Particle[i].Scalez);

		glEnable(GL_BLEND);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		TextureManager::getInstance()->BindTexture(textureName1);

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(-1, -1, 0);
		glTexCoord2d(1, 0);
		glVertex3f(1, -1, 0);
		glTexCoord2d(1, 1);
		glVertex3f(1, 1, 0);
		glTexCoord2d(0, 1);
		glVertex3f(-1, 1, 0);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		TextureManager::getInstance()->BindTexture(textureName2);

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(-1, -1, 0);
		glTexCoord2d(1, 0);
		glVertex3f(1, -1, 0);
		glTexCoord2d(1, 1);
		glVertex3f(1, 1, 0);
		glTexCoord2d(0, 1);
		glVertex3f(-1, 1, 0);
		glEnd();

		glDisable(GL_BLEND);
		glPopMatrix();

	}
	glEnable(GL_CULL_FACE);
	glPopMatrix();
}

void Spell::Update()
{
	pos.x += castDir.x + force.x;
	pos.y += castDir.y + force.y;
	pos.z += castDir.z + force.z;

	force.x /= 1.1;
	force.y /= 1.1;
	force.z /= 1.1;
	castDir.x /= 1.05;
	castDir.y /= 1.05;
	castDir.z /= 1.05;

	radius += radiusChangePerUpdate;
	counter++;
	float d = vec3::distance(castPosition, pos);
	if (d > 30) radiusChangePerUpdate = -0.05;
	if (radius < 0 || counter > 80)
	{
		isAlive = false;
		glDisable(GL_LIGHT2);
	}

	for (int i = 1; i < 200; i++)
	{
		Particle[i].Ypos = Particle[i].Ypos + Particle[i].Acceleration - Particle[i].Deceleration;
		Particle[i].Xpos += Particle[i].Xmov + castDir.x / weight / 4;
		Particle[i].Zpos += Particle[i].Zmov + castDir.z / weight / 4;
		Particle[i].Direction = Particle[i].Direction + ((((((int)(0.5 - 0.1 + 0.1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1);
	}
}