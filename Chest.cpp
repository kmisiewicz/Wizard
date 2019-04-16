#include "stdafx.h"
#include "Chest.h"


Chest::Chest(float x, float y, float z, vec3 rot, vec3 scale)
{
	pos.x = x;
	pos.y = y;
	Y = y-0.6;
	pos.z = z;
	openAngle = 0.0f;
	objectType = "chest";
	health = -1000;
	open = false;
	close = false;
	closed = true;
	this->rot = rot;
	this->scale = scale;
	textureName = "wood2";
	radius = 0.6;
	modelRotate = std::rand() % 360;
}

Chest::~Chest()
{
}

void Chest::Render()
{
	if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture(textureName);
	}
	
	glPushMatrix();
		float mat_ambient[] = { 0.2125f, 0.1275f, 0.054f, 1.0f };
		float mat_diffuse[] = { 0.714f, 0.4284f, 0.18144f, 1.0f };
		float mat_specular[] = { 0.393548f, 0.271906f, 0.166721f, 1.0f };
		float shine[] = { 25.6f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shine);
		glTranslatef(pos.x, -0.2, pos.z);
		glRotatef(modelRotate, 0, 1, 0);
		glScalef(scale.x, scale.y, scale.z);
		glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			//front
			glTexCoord2f(0, 0);
			glVertex3f(-0.4f, 0.0f, 0.2f);
			glTexCoord2f(0, 2);
			glVertex3f(0.4f, 0.0f, 0.2f);
			glTexCoord2f(1, 2);
			glVertex3f(0.4f, 0.35f, 0.2f);
			glTexCoord2f(1, 0);
			glVertex3f(-0.4f, 0.35f, 0.2f);
			glNormal3f(-1, 0, 0);
			//lewa œciana
			glTexCoord2f(1, 1);
			glVertex3f(-0.4f, 0.35f, 0.2f);
			glTexCoord2f(1, 0);
			glVertex3f(-0.4f, 0.35f, -0.2f);
			glTexCoord2f(0, 0);
			glVertex3f(-0.4f, 0.0f, -0.2f);
			glTexCoord2f(0, 1);
			glVertex3f(-0.4f, 0.0f, 0.2f);
			//dó³
			glNormal3f(0, -1, 0);
			glTexCoord2f(2, 1);
			glVertex3f(-0.4f, 0.0f, 0.2f);
			glTexCoord2f(0, 1);
			glVertex3f(-0.4f, 0.0f, -0.2f);
			glTexCoord2f(0, 0);
			glVertex3f(0.4f, 0.0f, -0.2f);
			glTexCoord2f(2, 0);
			glVertex3f(0.4f, 0.0f, 0.2f);
			//ty³
			glNormal3f(0, 0, -1);
			glTexCoord2f(0, 2);
			glVertex3f(-0.4f, 0.0f, -0.2f);
			glTexCoord2f(1, 2);
			glVertex3f(-0.4f, 0.35f, -0.2f);
			glTexCoord2f(1, 0);
			glVertex3f(0.4f, 0.35f, -0.2f);
			glTexCoord2f(0, 0);
			glVertex3f(0.4f, 0.0f, -0.2f);
			//prawa œciana
			glNormal3f(1, 0, 0);
			glTexCoord2f(0, 1);
			glVertex3f(0.4f, 0.0f, -0.2f);
			glTexCoord2f(1, 1);
			glVertex3f(0.4f, 0.35f, -0.2f);
			glTexCoord2f(1, 0);
			glVertex3f(0.4f, 0.35f, 0.2f);
			glTexCoord2f(0, 0);
			glVertex3f(0.4f, 0.0f, 0.2f);
			//ramka prawa
			glNormal3f(0, 1, 0);
			glTexCoord2f(0, 0);
			glVertex3f(0.4f, 0.35f, 0.2f);
			glTexCoord2f(1, 0);
			glVertex3f(0.4f, 0.35f, -0.2f);
			glTexCoord2f(1, 0.3);
			glVertex3f(0.35f, 0.35f, -0.2f);
			glTexCoord2f(0, 0.3);
			glVertex3f(0.35f, 0.35f, 0.2f);
			//ramka przednia
			glTexCoord2f(1, 2);
			glVertex3f(0.35f, 0.35f, 0.2f);
			glTexCoord2f(0.9, 2);
			glVertex3f(0.35f, 0.35f, 0.15f);
			glTexCoord2f(0.9, 0);
			glVertex3f(-0.35f, 0.35f, 0.15f);
			glTexCoord2f(1, 0);
			glVertex3f(-0.35f, 0.35f, 0.2f);
			//ramka lewa
			glTexCoord2f(0, 0);
			glVertex3f(-0.35f, 0.35f, 0.2f);
			glTexCoord2f(1, 0);
			glVertex3f(-0.35f, 0.35f, -0.2f);
			glTexCoord2f(1, 0.3);
			glVertex3f(-0.4f, 0.35f, -0.2f);
			glTexCoord2f(0, 0.3);
			glVertex3f(-0.4f, 0.35f, 0.2f);
			//ramka tylnia
			glTexCoord2f(0.9, 0);
			glVertex3f(-0.35f, 0.35f, -0.2f);
			glTexCoord2f(1, 0);
			glVertex3f(-0.35f, 0.35f, -0.15f);
			glTexCoord2f(1, 2);
			glVertex3f(0.35f, 0.35f, -0.15f);
			glTexCoord2f(0.9, 2);
			glVertex3f(0.35f, 0.35f, -0.2f);
			
			//glColor3f(0.92, 0.78, 0.62);
			mat_ambient[0] = 0.05f;
			mat_ambient[1] = 0.0f;
			mat_ambient[2] = 0.0f;
			mat_diffuse[0] = 0.5f;
			mat_diffuse[1] = 0.4f;
			mat_diffuse[2] = 0.4f;
			mat_specular[0] = 0.7f;
			mat_specular[1] = 0.04f;
			mat_specular[2] = 0.04f;
			shine[0] = 10.0f;
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, shine);
			//œrodek ty³
			glNormal3f(0, 0, -1);
			glVertex3f(0.35f, 0.35f, -0.15f);
			glVertex3f(-0.35f, 0.35f, -0.15f);
			glVertex3f(-0.35f, 0.05f, -0.15f);
			glVertex3f(0.35f, 0.05f, -0.15f);
			//œrodek prawa œciana
			glNormal3f(-1, 0, 0);
			glVertex3f(0.35f, 0.05f, -0.15f);
			glVertex3f(0.35f, 0.05f, 0.15f);
			glVertex3f(0.35f, 0.35f, 0.15f);
			glVertex3f(0.35f, 0.35f, -0.15f);
			//œrodek przód
			glNormal3f(0, 0, 1);
			glVertex3f(0.35f, 0.35f, 0.15f);
			glVertex3f(0.35f, 0.05f, 0.15f);
			glVertex3f(-0.35f, 0.05f, 0.15f);
			glVertex3f(-0.35f, 0.35f, 0.15f);
			//œrodek lewa œciana
			glNormal3f(1, 0, 0);
			glVertex3f(-0.35f, 0.35f, 0.15f);
			glVertex3f(-0.35f, 0.05f, 0.15f);
			glVertex3f(-0.35f, 0.05f, -0.15f);
			glVertex3f(-0.35f, 0.35f, -0.15f);
			// œrodek dó³
			glNormal3f(0, 1, 0);
			glVertex3f(-0.35f, 0.05f, -0.15f);
			glVertex3f(-0.35f, 0.05f, 0.15f);
			glVertex3f(0.35f, 0.05f, 0.15f);
			glVertex3f(0.35f, 0.05f, -0.15f);
		glEnd();
		
		glPushMatrix();
		glTranslatef(0.0f, 0.35f, -0.2f);
		glRotatef(openAngle, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.35f, 0.2f);
		mat_ambient[0] = 0.2125f;
		mat_ambient[1] = 0.1275f;
		mat_ambient[2] = 0.054f;
		mat_diffuse[0] = 0.714f;
		mat_diffuse[1] = 0.4284f;
		mat_diffuse[2] = 0.18144f;
		mat_specular[0] = 0.393548f;
		mat_specular[1] = 0.271906f;
		mat_specular[2] = 0.166721f;
		shine[0] = 25.6f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shine);
		glBegin(GL_QUADS);
			glColor3f(0.23, 0.15, 0.1);
			glNormal3f(0, -1, 0);
			//wieko dó³
			glTexCoord2f(1, 0);
			glVertex3f(-0.4f, 0.35f, 0.2f);
			glTexCoord2f(0, 0);
			glVertex3f(-0.4f, 0.35f, -0.2f);
			glTexCoord2f(0, 1);
			glVertex3f(0.4f, 0.35f, -0.2f);
			glTexCoord2f(1, 1);
			glVertex3f(0.4f, 0.35f, 0.2f);
		glEnd();
		
		//wieko
		
		glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(-1, 0, 0);
			//lewa œciana
			for (int i = 0; i < 12; i++)
			{
				glTexCoord2f(0, 0);
				glVertex3f(-0.4f, 0.35f, 0.0f);
				glTexCoord2f(i % 2 * 0.2, 1);
				glVertex3f(-0.4f, 0.35f + 0.2 * sin(i * 2 * 3.142 / 24), 0.2 * cos(i * 2* 3.142 / 24));
			}
			glVertex3f(-0.4f, 0.35f, -0.2f);
			glVertex3f(-0.4f, 0.35f, -0.2f);
			glVertex3f(0.4f, 0.35f, -0.2f);
			glTexCoord2f(0, 0);
			glVertex3f(0.4f, 0.35f, -0.2f);
			glNormal3f(1, 0, 0);
			//prawa œciana
			for (int i = 0; i <= 12; i++)
			{
				glTexCoord2f(i % 2 * 0.2, 1);
				glVertex3f(0.4f, 0.35f + 0.2 * sin(i * 2 * 3.142 / 24), 0.2 * cos(i * 2 * 3.142 / 24));
				glTexCoord2f(0, 0);
				glVertex3f(0.4f, 0.35f, 0.0f);
			}
			glVertex3f(0.4f, 0.35f, 0.2f);
			glVertex3f(0.4f, 0.35f, 0.2f);
			glVertex3f(0.4f, 0.35f, 0.2f);
			//to okr¹g³e
			for (int i = 0; i <= 12; i++)
			{
				glNormal3f(0, sin(float(i) * 2 * 3.142 / float(24)), cos(float(i) * 2 * 3.142 / float(24)));
				glTexCoord2f((i + 1) % 2 * 0.1, 2);
				glVertex3f(0.4, 0.35 + 0.2 * sin(float(i) * 2 * 3.142 / float(24)), 0.2 * cos(float(i) * 2 * 3.142 / float(24)));
				glTexCoord2f((i + 1) % 2 * 0.1, 0);
				glVertex3f(-0.4, 0.35+ 0.2 * sin(float(i) * 2 * 3.142 / float(24)), 0.2 * cos(float(i) * 2 * 3.142 / float(24)));
			}
			
		glEnd();
		glPopMatrix();
	glPopMatrix();
}

void Chest::Update()
{
	if (!closed)
	{
		if (open)
		{
			openAngle -= 2;
			if (openAngle == -130)
			{
				close = true;
				open = false;
			}
		}
		if (close)
		{
			openAngle += 2;
			if (openAngle == 0)
			{
				close = false;
				closed = true;
				isAlive = false;
			}
		}
	}
}

void Chest::openClose()
{

}
