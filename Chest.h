#pragma once
#include "stdafx.h"
class Chest : public SceneObject
{
private:
	float Y, openAngle;
	vec3 rot, scale;
	std::string textureName;
public:
	Chest(float, float, float, vec3, vec3);
	~Chest();
	void Render();
	void Update();
	void openClose();
	bool open, close, closed;
	float modelRotate;
};

