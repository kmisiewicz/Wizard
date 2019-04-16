#pragma once
#include "SceneObject.h"

class Potion :	public SceneObject
{
public:
	Potion(vec3 pos, vec3 color);
	~Potion();
	Potion(Potion &potion);

	bool load(std::string filepath);

	void Render();
	void Update();

	vec3 color;
	vec3 lightcolor;
	
	vec3 modelTranslation;
	vec3 modelScale;

	std::string textureName;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;
	bool up;
	float rotate;
	int bonus;
};

