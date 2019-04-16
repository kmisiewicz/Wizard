#pragma once
#include "SceneObject.h"
#include "stdafx.h"

class Staff : public SceneObject
{
public:
	Staff(vec3 pos, vec3 color, std::string StaffType, Player * player, float baserotate);
	~Staff();

	bool load(std::string filepath);

	void Render();
	void Update();

	vec3 color;
	vec3 dir;
	vec3 modelTranslation;
	vec3 modelScale;

	std::string textureName;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;

	float baserotate;
	float rotate, rotate2;
	bool attack, attackback;
	float attackrotate;
	std::string StaffType;
	Player * player;
};

