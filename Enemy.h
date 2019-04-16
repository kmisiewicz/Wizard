#pragma once
#include "SceneObject.h"
#include "stdafx.h"

class Enemy : public SceneObject
{
public:
	Enemy(vec3 pos, vec3 color, std::string enemyType, float speed, Player * player, float baserotate, int health, float strength);
	~Enemy();
	Enemy(Enemy &enemy);
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

	float speed;
	float baserotate;
	float rotate;
	float strength;
	std::string enemyType;
	Player * player;
};

