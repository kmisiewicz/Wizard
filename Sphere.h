#pragma once

#include "SceneObject.h"

class Sphere : public SceneObject
{
public:
	Sphere(vec3 pos, vec3 color, float radius, float weight);
	~Sphere(void);

	void Render();
	void Update();

	float radiusChangePerUpdate;
};
