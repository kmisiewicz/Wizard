#pragma once
#include "SceneObject.h"
class Cube :
	public SceneObject
{
public:
	Cube(vec3 pos, vec3 color, float size, std::string textureName = "");
	~Cube();

	void Render();
	void Update();

	float size;

	std::string textureName;
};

