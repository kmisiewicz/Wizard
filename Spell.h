#pragma once

#include "stdafx.h"
class Spell : public SceneObject
{
public:
	Spell(vec3 pos, vec3 castDir, float radius, float weight, vec3 castPosition, int spellType);
	~Spell(void);

	void Render();
	void Update();

	float radiusChangePerUpdate;
	vec3 castPosition;
	vec3 castDir;
	unsigned int counter;
	unsigned int spellType; //1 - czerwony - atak, 2 - zielony - przesuwanie obiektow, 3 - niebieski - otwieranie skrzynek/drzwi

	struct PARTICLES
	{
		double Xpos;
		double Ypos;
		double Zpos;
		double Xmov;
		double Zmov;
		double Red;
		double Green;
		double Blue;
		double Direction;
		double Acceleration;
		double Deceleration;
		double Scalez;
		bool Visible;
	} Particle[200];

	std::string textureName1, textureName2;
};
