#include "stdafx.h"
#include "Potion.h"


Potion::Potion(vec3 pos, vec3 color)
{
	this->pos = pos;
	this->color = color;
	modelScale = vec3(0.02, 0.02, 0.02);
	modelTranslation = vec3(0, 0, 0);
	health = -1000;
	up = true;
	rotate = 0;
	bonus = std::rand() % 21 + 10;
	lightcolor = vec3(0, 0, 0);
	if (std::rand() % 2)
	{
		objectType = "potionhp";
		lightcolor.x = 1;
	}
	else
	{
		objectType = "potionmana";
		lightcolor.z = 1;		
	}
	textureName = objectType;
}

Potion::Potion(Potion &potion)
{
	color = potion.color;
	modelScale = potion.modelScale;
	modelTranslation = potion.modelTranslation;
	health = potion.health;
	radius = potion.radius;
	vertices = potion.vertices;
	normals = potion.normals;
	uvs = potion.uvs;
	up = true;
	rotate = 0;
	bonus = std::rand() % 21 + 20;
	lightcolor = vec3(0, 0, 0);
	if (std::rand() % 2)
	{
		objectType = "potionhp";
		lightcolor.x = 1;
	}
	else
	{
		objectType = "potionmana";
		lightcolor.z = 1;
	}
	textureName = objectType;
}

Potion::~Potion()
{
}

bool Potion::load(std::string filename)
{
	struct SFace {
		int v[3];
		int n[3];
		int uv[3];
	};

	FILE * fp = fopen(filename.c_str(), "r");

	if (fp == NULL) {
		printf("Nie wczytano pliku %s\n", filename.c_str());
		return false;
	}

	vertices.clear();

	std::vector<vec3> loaded_vertices;
	std::vector<vec3> loaded_normals;
	std::vector<vec3> loaded_uvs;
	std::vector<SFace> loaded_faces;

	char buf[256];

	while (fgets(buf, 256, fp)) {
		if (buf[0] == 'v' && buf[1] == ' ') {
			vec3 vertex;
			sscanf(buf, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			loaded_vertices.push_back(vertex);
		}
		if (buf[0] == 'v' && buf[1] == 'n') {
			vec3 normal;
			sscanf(buf, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
			loaded_normals.push_back(normal);
		}
		if (buf[0] == 'v' && buf[1] == 't') {
			vec3 vertex;
			sscanf(buf, "vt %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			loaded_uvs.push_back(vertex);
		}
		if (buf[0] == 'f' && buf[1] == ' ') {
			SFace face;
			sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d", 
				&face.v[0], &face.uv[0], &face.n[0],
				&face.v[1], &face.uv[1], &face.n[1], 
				&face.v[2], &face.uv[2], &face.n[2]);
			loaded_faces.push_back(face);
		}
	}

	fclose(fp);

	vec3 minVertex = loaded_vertices[0];
	vec3 maxVertex = loaded_vertices[1];

	for (int i = 0; i < loaded_faces.size(); ++i) {
		for (int j = 0; j < 3; ++j) {

			int idxV = loaded_faces[i].v[j] - 1;
			int idxN = loaded_faces[i].n[j] - 1;
			int idxUV = loaded_faces[i].uv[j] - 1;

			vertices.push_back(loaded_vertices[idxV]);
			normals.push_back(loaded_normals[idxN]);
			uvs.push_back(loaded_uvs[idxUV]);

			if (loaded_vertices[idxV].x < minVertex.x)
				minVertex.x = loaded_vertices[idxV].x;

			if (loaded_vertices[idxV].x > maxVertex.x)
				maxVertex.x = loaded_vertices[idxV].x;


			if (loaded_vertices[idxV].y < minVertex.y)
				minVertex.y = loaded_vertices[idxV].y;

			if (loaded_vertices[idxV].y > maxVertex.y)
				maxVertex.y = loaded_vertices[idxV].y;


			if (loaded_vertices[idxV].z < minVertex.z)
				minVertex.z = loaded_vertices[idxV].z;

			if (loaded_vertices[idxV].z > maxVertex.z)
				maxVertex.z = loaded_vertices[idxV].z;
			
		}
	}

	float diffX = maxVertex.x - minVertex.x;
	float diffY = maxVertex.y - minVertex.y;
	float diffZ = maxVertex.z - minVertex.z;

	if (diffX < diffY)
	{
		if (diffY < diffZ)
		{
			radius = diffZ;
		}
		else
		{
			radius = diffY;
		}
	}
	else
	{
		if (diffX < diffZ)
		{
			radius = diffZ;
		}
		else
		{
			radius = diffX;
		}
	}

	radius /= 2;
	weight = radius;

	return true;
}

void Potion::Render()
{
	if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName);
	}

	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	float mat_diffuse[] = { lightcolor.x, lightcolor.y, lightcolor.z };
	float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	glEnable(GL_LIGHT3);
	GLfloat l3_ambient[] = { ambient.x, ambient.y, ambient.z };
	GLfloat l3_diffuse[] = { diffuse.x,diffuse.y,diffuse.z };
	GLfloat l3_specular[] = { specular.x, specular.y, specular.z };
	GLfloat l3_position[] = { pos.x, pos.y, pos.z, 0.0f };
	glLightfv(GL_LIGHT3, GL_AMBIENT, l3_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, l3_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, l3_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, l3_position);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.8);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.8);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.8);

	glPushMatrix();
		
		glTranslatef(pos.x, pos.y, pos.z);
		glTranslatef(modelTranslation.x, modelTranslation.y, modelTranslation.z);
		glRotatef(rotate, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		glScalef(modelScale.x, modelScale.y, modelScale.z);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < vertices.size(); i++)
		{
			glNormal3f(normals[i].x, normals[i].y, normals[i].z);
			glTexCoord2f(uvs[i].x, uvs[i].y);
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}
		glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Potion::Update()
{
	pos.x += force.x / weight;
	pos.y += force.y / weight;
	pos.z += force.z / weight;

	force.x /= 1.2;
	force.y /= 1.2;
	force.z /= 1.2;
	if (up)
	{
		modelTranslation.y += 0.01;
		if (modelTranslation.y >= 0.5) up = false;
	}
	else
	{
		modelTranslation.y -= 0.01;
		if (modelTranslation.y <= 0) up = true;
	}
	rotate += 0.5;
	if (rotate >= 360) rotate = 0;
}