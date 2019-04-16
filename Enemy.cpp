#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(vec3 pos, vec3 color, std::string enemyType, float speed, Player * player, float baserotate, int health, float strength)
{
	this->pos = pos;
	this->color = color;
	objectType = "enemy";
	this->enemyType = enemyType;
	this->speed = speed;
	this->player = player;
	this->baserotate = baserotate;
	this->health = health;
	this->strength = strength;
	modelScale = vec3(1, 1, 1);
	rotate = 0;
}


Enemy::~Enemy()
{
}

Enemy::Enemy(Enemy & enemy)
{
	pos = vec3(std::rand() % 91 - 45, 3, std::rand() % 91 - 35);

	weight = enemy.weight;
	radius = enemy.radius;

	ambient = enemy.ambient;
	diffuse = enemy.diffuse;
	specular = enemy.specular;

	isAlive = true;
	objectType = enemy.objectType;
	health = enemy.health;
	color = enemy.color;
	modelTranslation = enemy.modelTranslation;
	modelScale = enemy.modelScale;

	textureName = enemy.textureName;

	vertices = enemy.vertices;
	normals = enemy.normals;
	uvs = enemy.uvs;
	player = enemy.player;
	speed = enemy.speed;
	baserotate = enemy.baserotate;
	strength = enemy.strength;
	enemyType = enemy.enemyType;
	
}

bool Enemy::load(std::string filename)
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

void Enemy::Render()
{
	if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName);
	}

	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	float mat_diffuse[] = { color.x, color.y, color.z };
	float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	glPushMatrix();
		
		glTranslatef(pos.x, pos.y, pos.z);
		glTranslatef(modelTranslation.x, modelTranslation.y, modelTranslation.z);
		glRotatef(rotate + baserotate, 0, 1, 0);
		
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

void Enemy::Update()
{
	pos.x += force.x / weight;
	pos.y += force.y / weight;
	pos.z += force.z / weight;

	dir = player->pos - pos;
	dir = dir.normalized();

	pos.x += dir.x * speed;
	pos.z += dir.z * speed;

	rotate = -atan2(dir.z, dir.x) * 180 / PI;

	if (pos.y < 0) pos.y = 0;

	force.x /= 1.1;
	force.y /= 1.1;
	force.z /= 1.1;
	if (health <= 0)
	{
		isAlive = false;
		player->points += 10;
	}
}