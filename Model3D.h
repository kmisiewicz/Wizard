#pragma once
#include "SceneObject.h"

class Model3D :	public SceneObject
{
public:
	Model3D(vec3 pos, vec3 color);
	~Model3D();
	Model3D(Model3D &model);
	bool load(std::string filepath);

	void Render();
	void Update();

	vec3 color;

	vec3 modelTranslation;
	vec3 modelScale;
	float modelRotate;

	std::string textureName;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;
};

