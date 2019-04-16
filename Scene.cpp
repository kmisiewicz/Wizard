#include "stdafx.h"
#include "Scene.h"


Scene::Scene(void)
{
	skydome = new Skydome(150, "nebula");
	menu = true;
	pause = false;
	gameOver = false;
	counter = 0;
	SoundEngine = createIrrKlangDevice();
	musicplaying = false;
	gameovermusic = false;
}


Scene::~Scene(void)
{
	for(unsigned int i = 0 ; i < sceneObjects.size() ; i++)
		delete sceneObjects[i];

	sceneObjects.clear();
}

void Scene::AddObject(SceneObject* object)
{
	sceneObjects.push_back(object);
}


void renderBitmapString(float x, float y, char* text) {
	char *c; 
	glRasterPos3f(x, y, 0);
	for (c = text; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void Scene::AddTriangleCollider(vec3 v1, vec3 v2, vec3 v3, vec3 uv1, vec3 uv2, vec3 uv3, std::string textureName)
{
	Triangle t;

	t.v1 = v1;
	t.v2 = v2;
	t.v3 = v3;

	t.uv1 = uv1;
	t.uv2 = uv2;
	t.uv3 = uv3;

	t.textureName = textureName;

	t.n = vec3::cross(v1 - v3, v2 - v1);
	t.n = t.n.normalized();

	t.A = t.n.x;
	t.B = t.n.y;
	t.C = t.n.z;
	t.D = -(t.A * v1.x + t.B * v1.y + t.C*v1.z);

	collisionTriangles.push_back(t);
}

void Scene::HeadUpDisplay()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	if (!menu && !pause && !gameOver)
	{
		char text[50];
		glColor3f(1, 1, 1);
		sprintf(text, "%d", (int)hud.health);		
		renderBitmapString(34, 3, text);
		sprintf(text, "%d", (int)hud.energy);
		renderBitmapString(64, 3, text);
		sprintf(text, "SCORE: %d", (int)hud.points);
		renderBitmapString(90, 95, text);

		glBegin(GL_QUADS);
		glColor3f(0, 0, 0.9);
		glVertex2f(98, 5);
		glVertex2f(98, 3);
		glVertex2f(98 - 30 * (hud.energy / hud.maxEnergy), 3);
		glVertex2f(98 - 30 * (hud.energy / hud.maxEnergy), 5);

		glColor3f(0, 0, 0);
		glVertex2f(98 - 30 * (hud.energy / hud.maxEnergy), 5);
		glVertex2f(98 - 30 * (hud.energy / hud.maxEnergy), 3);
		glVertex2f(68, 3);
		glVertex2f(68, 5);

		glColor3f(0, 0, 0.3);
		glVertex2f(67, 6);
		glVertex2f(67, 2);
		glVertex2f(99, 2);
		glVertex2f(99, 6);
		//
		glColor3f(0.9, 0, 0);
		glVertex2f(2, 5);
		glVertex2f(2, 3);
		glVertex2f(2 + 30 * (hud.health / hud.maxHealth), 3);
		glVertex2f(2 + 30 * (hud.health / hud.maxHealth), 5);

		glColor3f(0, 0, 0);
		glVertex2f(2 + 30 * (hud.health / hud.maxHealth), 5);
		glVertex2f(2 + 30 * (hud.health / hud.maxHealth), 3);
		glVertex2f(32, 3);
		glVertex2f(32, 5);

		glColor3f(0.3, 0, 0);
		glVertex2f(1, 6);
		glVertex2f(1, 2);
		glVertex2f(33, 2);
		glVertex2f(33, 6);
		glEnd();

		
	}
	if (menu)
	{
		char text[50];
		glColor3f(1, 1, 1);
		sprintf(text, "PLAY");
		renderBitmapString(48, 49, text);
		sprintf(text, "QUIT");
		renderBitmapString(48, 41, text);
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture("title");
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex2f(32, 60);
		glTexCoord2d(1, 0);
		glVertex2f(68, 60);
		glTexCoord2d(1, 1);
		glVertex2f(68, 80);
		glTexCoord2d(0, 1);
		glVertex2f(32, 80);
		glEnd();
		TextureManager::getInstance()->BindTexture("button");
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex2f(45, 47);
		glTexCoord2d(1, 0);
		glVertex2f(55, 47);
		glTexCoord2d(1, 1);
		glVertex2f(55, 53);
		glTexCoord2d(0, 1);
		glVertex2f(45, 53);

		glTexCoord2d(0, 0);
		glVertex2f(45, 39);
		glTexCoord2d(1, 0);
		glVertex2f(55, 39);
		glTexCoord2d(1, 1);
		glVertex2f(55, 45);
		glTexCoord2d(0, 1);
		glVertex2f(45, 45);
		glEnd();
		TextureManager::getInstance()->BindTexture("menu");
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex2f(0, 0);
		glTexCoord2d(1, 0);
		glVertex2f(100, 0);
		glTexCoord2d(1, 1);
		glVertex2f(100, 100);
		glTexCoord2d(0, 1);
		glVertex2f(0, 100);
		glEnd();
		glDisable(GL_TEXTURE_2D);		
	}
	else if (pause)
	{
		char text[100];
		glColor3f(1, 1, 1);
		sprintf(text, "CONTINUE");
		renderBitmapString(47, 30, text);
		sprintf(text, "QUIT");
		renderBitmapString(48, 22, text);
		glColor3f(0, 0, 0);
		sprintf(text, "You're a wizard...");
		renderBitmapString(32, 91, text);
		sprintf(text, "And you will have to survive in this room full of dangerous foes.");
		renderBitmapString(32, 87, text);
		sprintf(text, "Here's some basic knowledge:");
		renderBitmapString(32, 83, text);
		sprintf(text, "You know 3 spells:           kills monsters,               moves");
		renderBitmapString(32, 79, text);
		glColor3f(0.9, 0, 0);
		sprintf(text, "RED");
		renderBitmapString(43, 79, text);
		glColor3f(0, 0.9, 0);
		sprintf(text, "GREEN");
		renderBitmapString(54, 79, text);
		glColor3f(0, 0, 0.9);
		sprintf(text, "BLUE");
		renderBitmapString(42, 75, text);
		glColor3f(0, 0, 0);
		sprintf(text, "objects and the                opens chests. Search for them to get");
		renderBitmapString(32, 75, text);
		sprintf(text, "potions which will boost your health or energy. You can't");
		renderBitmapString(32, 71, text);
		sprintf(text, "spam spells because your energy is limited but recovers over time");
		renderBitmapString(32, 67, text);
		sprintf(text, "I hope I didn't forget anything important. Have fun!");
		renderBitmapString(32, 63, text);
		sprintf(text, "W, S, A, D - movement");
		renderBitmapString(32, 59, text);
		sprintf(text, "Space - jump");
		renderBitmapString(32, 55, text);
		sprintf(text, "LPM - cast a spell");
		renderBitmapString(32, 51, text);
		sprintf(text, "1, 2, 3 - switch spell type");
		renderBitmapString(32, 47, text);
		sprintf(text, "ESC - pause (this screen)");
		renderBitmapString(32, 43, text);
		sprintf(text, "M - turn off music (only during game)");
		renderBitmapString(32, 39, text);

		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture("button");
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex2f(45, 28);
		glTexCoord2d(1, 0);
		glVertex2f(55, 28);
		glTexCoord2d(1, 1);
		glVertex2f(55, 34);
		glTexCoord2d(0, 1);
		glVertex2f(45, 34);
		
		glTexCoord2d(0, 0);
		glVertex2f(45, 20);
		glTexCoord2d(1, 0);
		glVertex2f(55, 20);
		glTexCoord2d(1, 1);
		glVertex2f(55, 26);
		glTexCoord2d(0, 1);
		glVertex2f(45, 26);
		glEnd();

		TextureManager::getInstance()->BindTexture("paper");
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex2f(30, 35);
		glTexCoord2d(1, 0);
		glVertex2f(70, 35);
		glTexCoord2d(1, 1);
		glVertex2f(70, 96);
		glTexCoord2d(0, 1);
		glVertex2f(30, 96);
		glEnd();

		TextureManager::getInstance()->BindTexture("menu");
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex2f(0, 0);
		glTexCoord2d(1, 0);
		glVertex2f(100, 0);
		glTexCoord2d(1, 1);
		glVertex2f(100, 100);
		glTexCoord2d(0, 1);
		glVertex2f(0, 100);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else if (gameOver)
	{
		char text[50];
		glColor3f(1, 1, 1);
		sprintf(text, "QUIT");
		renderBitmapString(48, 37, text);
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture("gameover");
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex2f(30, 50);
		glTexCoord2d(1, 0);
		glVertex2f(70, 50);
		glTexCoord2d(1, 1);
		glVertex2f(70, 70);
		glTexCoord2d(0, 1);
		glVertex2f(30, 70);
		glEnd();
		TextureManager::getInstance()->BindTexture("button");
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex2f(45, 35);
		glTexCoord2d(1, 0);
		glVertex2f(55, 35);
		glTexCoord2d(1, 1);
		glVertex2f(55, 41);
		glTexCoord2d(0, 1);
		glVertex2f(45, 41);
		glEnd();
		TextureManager::getInstance()->BindTexture("menu");
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex2f(0, 0);
		glTexCoord2d(1, 0);
		glVertex2f(100, 0);
		glTexCoord2d(1, 1);
		glVertex2f(100, 100);
		glTexCoord2d(0, 1);
		glVertex2f(0, 100);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Scene::Render()
{
	if (!menu && !pause)
	{
		for (unsigned int i = 0; i < sceneObjects.size(); i++)
			sceneObjects[i]->Render();

		for (unsigned int i = 0; i < collisionTriangles.size(); i++)
		{
			if (!collisionTriangles[i].textureName.empty())
			{
				glEnable(GL_TEXTURE_2D);
				TextureManager::getInstance()->BindTexture(collisionTriangles[i].textureName);
			}

			float ambient[] = { 0.5f, 0.5f, 0.5f };
			float diffuse[] = { 1.0f, 1.0f, 1.0f };
			float specular[] = { 0.0f, 0.0f, 0.0f };

			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glBegin(GL_TRIANGLES);
			glNormal3f(collisionTriangles[i].n.x, collisionTriangles[i].n.y, collisionTriangles[i].n.z);
			glTexCoord2f(collisionTriangles[i].uv1.x, collisionTriangles[i].uv1.y);
			glVertex3f(collisionTriangles[i].v1.x, collisionTriangles[i].v1.y, collisionTriangles[i].v1.z);
			glTexCoord2f(collisionTriangles[i].uv2.x, collisionTriangles[i].uv2.y);
			glVertex3f(collisionTriangles[i].v2.x, collisionTriangles[i].v2.y, collisionTriangles[i].v2.z);
			glTexCoord2f(collisionTriangles[i].uv3.x, collisionTriangles[i].uv3.y);
			glVertex3f(collisionTriangles[i].v3.x, collisionTriangles[i].v3.y, collisionTriangles[i].v3.z);
			glEnd();

			glDisable(GL_TEXTURE_2D);
		}

		skydome->Render();
	}
}

void Scene::Update()
{
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		SceneObject* obj = sceneObjects[i];

		obj->prevPos = obj->pos;

		obj->pos.y -= 0.3f;

		if ((obj->pos.x + obj->radius) > boundaryMax.x)
			obj->pos.x = boundaryMax.x - obj->radius;

		if ((obj->pos.y + obj->radius) > boundaryMax.y)
			obj->pos.y = boundaryMax.y - obj->radius;

		if ((obj->pos.z + obj->radius) > boundaryMax.z)
			obj->pos.z = boundaryMax.z - obj->radius;

		if ((obj->pos.x - obj->radius) < boundaryMin.x)
			obj->pos.x = boundaryMin.x + obj->radius;

		if ((obj->pos.y - obj->radius) < boundaryMin.y)
			obj->pos.y = boundaryMin.y + obj->radius;

		if ((obj->pos.z - obj->radius) < boundaryMin.z)
			obj->pos.z = boundaryMin.z + obj->radius;
	}

	for (int i = 0; i < sceneObjects.size(); i++)
	{
		for (int j = i + 1; j < sceneObjects.size(); j++)
		{
			SceneObject* obj1 = sceneObjects[i];
			SceneObject* obj2 = sceneObjects[j];

			if (obj1->objectType == "staff" || obj2->objectType == "staff") continue;
			if (obj1->objectType == "player" && obj2->objectType == "spell") continue;

			float r = vec3::distance(obj1->pos, obj2->pos);

			float d = (obj1->radius + obj2->radius) - r;

			if (d > 0)
			{
				vec3 v1 = obj1->pos - obj2->pos;
				vec3 v2 = obj2->pos - obj1->pos;

				v1 = v1.normalized();
				v2 = v2.normalized();

				if (obj1->objectType == "player" && (obj2->objectType == "cube" || obj2->objectType == "chest" || obj2->objectType == "object"))
				{
					obj1->pos = obj1->pos + v1 * d * 1.2f;
					continue;
				}
				else if ((obj1->objectType == "cube" || obj2->objectType == "chest" || obj2->objectType == "object") && obj2->objectType == "player")
				{
					obj2->pos = obj1->pos + v1 * d * 1.2f;
					continue;
				}
				else if(obj1->objectType == "player" && obj2->objectType == "dino")
				{
					if (obj2->objectType == "dino")
					{
						Player *player = dynamic_cast<Player*>(obj1);
						SoundEngine->play2D("../Resources/Sounds/heal.mp3");
						player->health = 100;
						player->energy = 100;
						obj2->isAlive = false;
					}
				}
				else if (obj1->objectType == "player" && (obj2->objectType == "potionhp" || obj2->objectType == "potionmana"))
				{
					Potion * potion = dynamic_cast<Potion*>(obj2);
					Player * player = dynamic_cast<Player*>(obj1);
					SoundEngine->play2D("../Resources/Sounds/heal.mp3");
					if (potion->objectType == "potionhp") player->health += potion->bonus;
					else player->energy += potion->bonus;
					potion->isAlive = false;
					glDisable(GL_LIGHT3);
					continue;
				}
				obj1->pos = obj1->pos + v1 * (d / 2) * 1.2f;
				obj2->pos = obj2->pos + v2 * (d / 2) * 1.2f;
				
				float total_force = obj1->force.length() + obj2->force.length();

				obj1->force = v1 * total_force * 0.5f;
				obj2->force = v2 * total_force * 0.5f;

				if (obj1->objectType == "spell")
				{
					obj1->isAlive = false;
					glDisable(GL_LIGHT2);
					Spell * spell = dynamic_cast<Spell*>(obj1);
					if (spell->spellType == 2) 
					{
						obj2->force = obj2->force * 80;
					}
					
					if (spell->spellType == 1 && obj2->objectType == "enemy")
					{
						Enemy * enemy = dynamic_cast<Enemy*>(obj2);
						enemy->health -= 10;
						if (enemy->enemyType == "spider") SoundEngine->play2D("../Resources/Sounds/hit1.mp3");
						else if (enemy->enemyType == "giant") SoundEngine->play2D("../Resources/Sounds/gianthit.mp3");
						else if (enemy->enemyType == "ghost") SoundEngine->play2D("../Resources/Sounds/animal.mp3");
					}
					if (spell->spellType == 3 && obj2->objectType == "chest")
					{
						Chest * chest = dynamic_cast<Chest*>(obj2);
						if (chest->closed && !chest->open)
						{
							chest->open = true;
							chest->closed = false;
							Potion *potion2 = new Potion(*potion);
							potion2->pos = chest->pos;
							potion->pos.y += 3;
							AddObject(potion2);
						}
						if (chest->closed && chest->open)
						{
							chest->open = false;
							chest->closed = false;
							chest->close = true;
						}
					}
				}
				else if (obj2->objectType == "spell")
				{
					obj2->isAlive = false;
					glDisable(GL_LIGHT2);
					Spell * spell = dynamic_cast<Spell*>(obj2);
					if (spell->spellType == 2)
					{
						obj1->force = obj1->force * 80;
					}
					if (spell->spellType == 1 && obj1->objectType == "enemy")
					{
						Enemy * enemy = dynamic_cast<Enemy*>(obj1);
						enemy->health -= 10;
						if (enemy->enemyType == "spider") SoundEngine->play2D("../Resources/Sounds/hit1.mp3");
						else if(enemy->enemyType == "giant") SoundEngine->play2D("../Resources/Sounds/gianthit.mp3");
						else if(enemy->enemyType == "ghost") SoundEngine->play2D("../Resources/Sounds/animal.mp3");
					}
					if (spell->spellType == 3 && obj1->objectType == "chest")
					{
						Chest * chest = dynamic_cast<Chest*>(obj1);
						if (chest->closed && !chest->open)
						{
							chest->open = true;
							chest->closed = false;
							Potion *potion2 = new Potion(*potion);
							potion2->pos = chest->pos;
							potion->pos.y += 3;
							AddObject(potion2);
						}
						if (chest->closed && chest->open)
						{
							chest->open = false;
							chest->closed = false;
							chest->close = true;
						}
					}
				}
				if (obj1->objectType == "player")
				{
					obj1->force.x = 0;
					obj1->force.y = 0;
					obj1->force.z = 0;
					if (obj2->objectType == "enemy")
					{
						Enemy * enemy = dynamic_cast<Enemy*>(obj2);
						enemy->player->health -= enemy->strength;
					}
				}
				if (obj2->objectType == "player")
				{
					obj2->force.x = 0;
					obj2->force.y = 0;
					obj2->force.z = 0;
					if (obj1->objectType == "enemy")
					{
						Enemy * enemy = dynamic_cast<Enemy*>(obj1);
						enemy->player->health -= enemy->strength;
					}
				}
			}
		}
	}

	for(unsigned int i = 0 ; i < sceneObjects.size() ; i++)
		sceneObjects[i]->Update();

	for (unsigned int i = 0; i < sceneObjects.size(); i++)
	{
		SceneObject* obj = sceneObjects[i];

		for (int j = 0; j < collisionTriangles.size(); j++)
		{
			Triangle tr = collisionTriangles[j];

			float currDist = tr.A * obj->pos.x + tr.B * obj->pos.y + tr.C * obj->pos.z + tr.D;
			float prevDist = tr.A * obj->prevPos.x + tr.B * obj->prevPos.y + tr.C * obj->prevPos.z + tr.D;

			if ((currDist * prevDist < 0) || abs(currDist) < obj->radius)
			{
				// Rzut pozycji obiektu na plaszczyzne
				vec3 p = obj->pos - tr.n * currDist;

				// Przesuniecie punktu do srodka trojkata o dlugosc promienia kolidera
				vec3 r = (tr.v1 + tr.v2 + tr.v3) * (1.0f / 3.0f) - p;
				r = r.normalized();
				p = p + r * obj->radius;

				// Obliczenie v, w, u - wspolrzednych barycentrycznych
				vec3 v0 = tr.v2 - tr.v1, v1 = tr.v3 - tr.v1, v2 = p - tr.v1;
				float d00 = vec3::dot(v0, v0);
				float d01 = vec3::dot(v0, v1);
				float d11 = vec3::dot(v1, v1);
				float d20 = vec3::dot(v2, v0);
				float d21 = vec3::dot(v2, v1);
				float denom = d00 * d11 - d01 * d01;

				float v = (d11 * d20 - d01 * d21) / denom;
				float w = (d00 * d21 - d01 * d20) / denom;
				float u = 1.0f - v - w;

				// Sprawdzenie czy punkt jest w srodku trojkata
				if (v >= 0 && w >= 0 && (v + w) <= 1)
				{
					float d = obj->radius - currDist;

					obj->pos = obj->pos + tr.n * d;

					obj->force = obj->force - tr.n * vec3::dot(tr.n, obj->force) * 2;
				}
			}
		}
	}

	for (std::vector<SceneObject*>::iterator it = sceneObjects.begin(); it != sceneObjects.end();)
	{
		if ((*it)->isAlive)
		{
			it++;
		}
		else
		{
			it = sceneObjects.erase(it);
		}
	}
	if (++counter % 200 == 0)
	{
		Enemy* spider2 = new Enemy(*spider);
		AddObject(spider2);
		if(counter == 600 || counter == 1200)
		{
			spider2 = new Enemy(*ghost);
			AddObject(spider2);
		}
		if (counter == 1800 || counter == 600)
		{
			Chest *chest = new Chest((std::rand() * std::rand()) % 96 - 48, 0, (std::rand() * std::rand()) % 92 - 44, vec3(0, 0, 0), vec3(3, 3, 3));
			AddObject(chest);
		}
		if (counter == 2400)
		{
			spider2 = new Enemy(*giant);
			AddObject(spider2);
			counter = 0;
		}
	}
	skydome->Update();
	if (gameOver)
	{
		
		if (!gameovermusic)
		{
			SoundEngine->stopAllSounds();
			SoundEngine->play2D("../Resources/Sounds/wizardover.mp3");
			gameovermusic = true;
		}
	}
	spider->speed += 0.00001;
}