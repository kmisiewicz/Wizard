#include "stdafx.h"
#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;
void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnTimer(int);
void OnMouseMove(int, int);
void OnMouseClick(int, int, int, int);

Player* player;
Sphere* movableSphere;
Staff* staff;
Scene scene;

int window_width, window_height;
vec3 mousePosition;

bool captureMouse;
bool gameClose = false;
ISoundEngine *SoundEngineMenu;

float T = 0;

int main(int argc, char* argv[])
{
	FreeConsole();
	srand(time(NULL));
	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280, 720);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Wizard");
	glutFullScreen();

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutTimerFunc(17, OnTimer, 0);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutMouseFunc(OnMouseClick);

	glClearColor(0.1f, 0.2f, 0.3f, 0.0);

	glEnable(GL_DEPTH_TEST);

	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	captureMouse = false;
	glutWarpPointer(window_width / 2, window_height / 2);
	
	SoundEngineMenu = createIrrKlangDevice();
	if (!SoundEngineMenu) return 0;
	SoundEngineMenu->play2D("../Resources/Sounds/wizardmenu.mp3", true);
	player = new Player();
	scene.AddObject(player);
	scene.hud.maxEnergy = player->maxEnergy;
	scene.hud.maxHealth = player->maxHealth;
	
	scene.AddObject(new Cube(vec3(-30, 0, 5), vec3(1, 1, 1), 5, "movebox"));
	scene.AddObject(new Cube(vec3(-30, 0, -5), vec3(1, 1, 1), 5, "movebox"));
	scene.AddObject(new Cube(vec3(-30, 0, -15), vec3(1, 1, 1), 5, "movebox"));
	scene.AddObject(new Cube(vec3(-30, 0, -25), vec3(1, 1, 1), 5, "movebox"));
	scene.AddObject(new Cube(vec3(-10, 0, -25), vec3(1, 1, 1), 5, "movebox"));
	scene.AddObject(new Cube(vec3(0, 0, -25), vec3(1, 1, 1), 5, "movebox"));
	scene.AddObject(new Cube(vec3(10, 0, -25), vec3(1, 1, 1), 5, "movebox"));
	scene.AddObject(new Cube(vec3(20, 0, -25), vec3(1, 1, 1), 5, "movebox"));

	scene.AddObject(new Chest(-20, 0, 40, vec3(0, 0, 0), vec3(3, 3, 3)));

	scene.dino = new Model3D(vec3(-50, 1, 3), vec3(0.3, 0.3, 0.3));
	scene.dino->load("../Resources/Models/dino.obj");
	scene.dino->textureName = "dino";
	scene.dino->modelTranslation = vec3(0, 0, 0);
	scene.dino->modelScale = vec3(0.02, 0.02, 0.02);
	scene.dino->modelRotate = 0;
	scene.dino->radius *= 0.02;
	scene.dino->objectType = "dino";
	scene.AddObject(scene.dino);

	scene.shelf = new Model3D(vec3(53, 0, -17), vec3(1, 1, 1));
	scene.shelf->load("../Resources/Models/shelf.obj");
	scene.shelf->textureName = "shelf";
	scene.shelf->modelTranslation = vec3(1, -3, 0);
	scene.shelf->modelScale = vec3(0.7, 0.5, 3);
	scene.shelf->modelRotate = -90;
	scene.shelf->radius = 3;
	scene.shelf->weight = 100;
	scene.shelf->objectType = "object";
	scene.AddObject(scene.shelf);
	Model3D *shelf2 = new Model3D(*scene.shelf);
	shelf2->pos = vec3(53, 0, 17);
	scene.AddObject(shelf2);
	shelf2 = new Model3D(*scene.shelf);
	shelf2->pos = vec3(-54, 0, -17);
	shelf2->modelTranslation.x = -1;
	shelf2->modelRotate = 90;
	scene.AddObject(shelf2);

	scene.cupboard = new Model3D(vec3(53, 0, 0), vec3(1, 1, 1));
	scene.cupboard->load("../Resources/Models/shelf2.obj");
	scene.cupboard->textureName = "shelf2";
	scene.cupboard->modelTranslation = vec3(0, -2, 0);
	scene.cupboard->modelScale = vec3(0.3, 0.3, 0.5);
	scene.cupboard->modelRotate = 90;
	scene.cupboard->radius = 2;
	scene.cupboard->weight = 50;
	scene.cupboard->objectType = "object";
	scene.AddObject(scene.cupboard);
	Model3D *cupboard2 = new Model3D(*scene.cupboard);
	cupboard2->modelRotate = -90;
	cupboard2->pos = vec3(-53, 0, 0);
	scene.AddObject(cupboard2);

	scene.armchair = new Model3D(vec3(-30, 0, 20), vec3(1, 1, 1));
	scene.armchair->load("../Resources/Models/armchair.obj");
	scene.armchair->textureName = "armchair";
	scene.armchair->modelTranslation = vec3(0, -1, 0);
	scene.armchair->modelScale = vec3(1.7, 1.7, 1.7);
	scene.armchair->modelRotate = -120;
	scene.armchair->radius = 1;
	scene.armchair->weight = 30;
	scene.armchair->objectType = "object";
	scene.AddObject(scene.armchair);
	Model3D *armchair2 = new Model3D(*scene.armchair);
	armchair2->modelRotate = -70;
	armchair2->pos = vec3(-32, 0, 25);
	scene.AddObject(armchair2);
	armchair2 = new Model3D(*scene.armchair);
	armchair2->modelRotate = 70;
	armchair2->pos = vec3(15, 0, 17);
	scene.AddObject(armchair2);
	armchair2 = new Model3D(*scene.armchair);
	armchair2->modelRotate = 120;
	armchair2->pos = vec3(17, 0, 15);
	scene.AddObject(armchair2);

	scene.table = new Model3D(vec3(-29, 0, 23), vec3(1, 1, 1));
	scene.table->load("../Resources/Models/table.obj");
	scene.table->textureName = "table";
	scene.table->modelTranslation = vec3(0, -2, 0);
	scene.table->modelScale = vec3(2.5, 2.5, 2.5);
	scene.table->modelRotate = 0;
	scene.table->radius = 2;
	scene.table->weight = 50;
	scene.table->objectType = "object";
	scene.AddObject(scene.table);
	Model3D *table2 = new Model3D(*scene.table);
	table2->pos = vec3(15, 0, 15);
	scene.AddObject(table2);

	scene.potion = new Potion(vec3(0, 0, 0), vec3(1, 1, 1));
	scene.potion->load("../Resources/Models/potion2.obj");
	scene.potion->radius = 0.7f;

	scene.ghost = new Enemy(vec3(30, 10, 0), vec3(1, 1, 1), "ghost", 0.16f, player, -90, 20, 0.15);
	scene.ghost->load("../Resources/Models/ghost.obj");
	scene.ghost->textureName = "ghost";
	scene.ghost->modelTranslation = vec3(0, -7, 0);
	scene.ghost->modelScale = vec3(0.2, 0.2, 0.2);
	scene.ghost->radius = 2;

	scene.spider = new Enemy(vec3(0, 0, 0), vec3(1, 1, 1), "spider", 0.1f, player, -90, 10, 1);
	scene.spider->load("../Resources/Models/spider.obj");
	scene.spider->textureName = "spider";
	scene.spider->modelTranslation = vec3(0, -0.8, 0);
	scene.spider->modelScale = vec3(0.015, 0.015, 0.015);
	scene.spider->radius = 1;

	scene.giant = new Enemy(vec3(0, 0, 0), vec3(1, 1, 1), "giant", 0.07f, player, 90, 40, 0.5);
	scene.giant->load("../Resources/Models/giant.obj");
	scene.giant->textureName = "giant";
	scene.giant->modelTranslation = vec3(0, -2.5, 0);
	scene.giant->modelScale = vec3(0.04, 0.04, 0.04);
	scene.giant->radius = 2.5;

	staff = new Staff(player->pos, vec3(1, 1, 1), "staff", player, -90);
	staff->load("../Resources/Models/staff.obj");
	staff->textureName = "staff";
	staff->modelTranslation = vec3(0.4, -1.2, -0.6);
	staff->modelScale = vec3(0.4, 0.4, 0.4);
	staff->radius *= 0.0001f;
	scene.AddObject(staff);

	scene.boundaryMin = vec3(-50, -2, -50);
	scene.boundaryMax = vec3(50, 30, 50);

	scene.AddTriangleCollider(vec3(50, 0, -50), vec3(-50, 0, -50), vec3(50, 0, 50), vec3(20, 20), vec3(0, 20), vec3(20, 0), "star_floor");
	scene.AddTriangleCollider(vec3(-50, 0, -50), vec3(-50, 0, 50), vec3(50, 0, 50), vec3(0, 20), vec3(0, 0), vec3(20, 0), "star_floor");

	scene.AddTriangleCollider(vec3(-50, 0, 50), vec3(-50, 15, 50), vec3(50, 15, 50), vec3(4, 0), vec3(4, 1), vec3(0, 1), "wallred");
	scene.AddTriangleCollider(vec3(50, 15, 50), vec3(50, 0, 50), vec3(-50, 0, 50), vec3(0, 1), vec3(0, 0), vec3(4, 0), "wallred");
	scene.AddTriangleCollider(vec3(50, 15, 50), vec3(50, 15, -50), vec3(50, 0, -50), vec3(4, 1), vec3(0, 1), vec3(0, 0), "wallred");
	scene.AddTriangleCollider(vec3(50, 0, 50), vec3(50, 15, 50), vec3(50, 0, -50), vec3(4, 0), vec3(4, 1), vec3(0, 0), "wallred");
	scene.AddTriangleCollider(vec3(-50, 0, 50), vec3(-50, 15, 50), vec3(-50, 15, 50), vec3(1, 0), vec3(1, 1), vec3(0, 1), "wallred");
	scene.AddTriangleCollider(vec3(-50, 15, 50), vec3(-50, 0, 50), vec3(-50, 15, -50), vec3(0, 1), vec3(0, 0), vec3(4, 1), "wallred");
	scene.AddTriangleCollider(vec3(-50, 0, 50), vec3(-50, 0, -50), vec3(-50, 15, -50), vec3(0, 0), vec3(4, 0), vec3(4, 1), "wallred");
	scene.AddTriangleCollider(vec3(50, 0, -50), vec3(50, 15, -50), vec3(-50, 15, -50), vec3(4, 0), vec3(4, 1), vec3(0, 1), "wallred");
	scene.AddTriangleCollider(vec3(-50, 15, -50), vec3(-50, 0, -50), vec3(50, 0, -50), vec3(0, 1), vec3(0, 0), vec3(4, 0), "wallred");

	scene.AddTriangleCollider(vec3(-50, 0, -40), vec3(50, 0, -40), vec3(-50, 2, -50), vec3(4, 1), vec3(0, 1), vec3(4, 0), "wood");
	scene.AddTriangleCollider(vec3(-50, 2, -50), vec3(50, 0, -40), vec3(50, 2, -50), vec3(0, 1), vec3(4, 0), vec3(4, 1), "wood");

	//WCZYTYWANIE TEKSTUR
	TextureManager::getInstance()->LoadTexture("movebox", "../Resources/textures/movebox.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("dino", "../Resources/textures/dino.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("wood", "../Resources/textures/wood.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("brick", "../Resources/textures/brick.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("grass", "../Resources/textures/grass.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("nebula", "../Resources/textures/nebula2.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("star_floor", "../Resources/textures/star_floor.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("particle", "../Resources/textures/particle.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("particle1", "../Resources/textures/particle_mask.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("wallred", "../Resources/textures/wallred.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("spider", "../Resources/textures/spider.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("ghost", "../Resources/textures/ghost.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("staff", "../Resources/textures/staff.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("wood2", "../Resources/textures/wood2.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("menu", "../Resources/textures/menu.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("button", "../Resources/textures/button2.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("paper", "../Resources/textures/paper.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("gameover", "../Resources/textures/gameover.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("title", "../Resources/textures/title.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("potionhp", "../Resources/textures/potionhp.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("potionmana", "../Resources/textures/potionmana.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("giant", "../Resources/textures/giant.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("shelf", "../Resources/textures/shelf.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("shelf2", "../Resources/textures/shelf2.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("armchair", "../Resources/textures/armchair.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("table", "../Resources/textures/table.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	glutMainLoop();

	return 0;
}

bool keystate[256];

void OnKeyPress(unsigned char key, int x, int y) {
	key = tolower(key);
	if (!keystate[key]) {
		OnKeyDown(key, x, y);
	}
	keystate[key] = true;
}

void OnKeyDown(unsigned char key, int x, int y) {
	if (!scene.menu && !scene.pause && !scene.gameOver)
	{
		if (key == 27) //ESC
		{
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			captureMouse = false;
			scene.pause = true;
			return;
		}
		if (key == 32) //spacja
		{
			if (player->jump == false)
			{
				player->jump = true;
				player->velocity_up = 18;
				player->jumpboost = 2.1;
			}
		}

		if (key == '1') player->spellSetting = 1;
		if (key == '2')	player->spellSetting = 2;
		if (key == '3')	player->spellSetting = 3;
		if (key == 'm') scene.SoundEngine->stopAllSounds();
	}
	else if (scene.pause)
	{
		if (key == 27) //ESC
		{
			scene.pause = false;
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(window_width / 2, window_height / 2);
			captureMouse = true;
			if (!scene.musicplaying || !scene.gameovermusic)
			{
				scene.SoundEngine->play2D("../Resources/Sounds/wizardtheme.mp3", true);
				scene.musicplaying = true;
			}
			return;
		}
	}
}

void OnKeyUp(unsigned char key, int x, int y) {
	keystate[tolower(key)] = false;
}

void OnMouseMove(int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;	
}

void OnMouseClick(int button, int state, int x, int y)
{
	if (!scene.menu && !scene.pause && !scene.gameOver)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (player->energy >= 20)
			{
				vec3 spellstart = player->pos + player->dir * 1.5;
				Spell* newSpell = new Spell(spellstart, player->dir * 1.5, 0.3, 2, player->pos, player->spellSetting);
				newSpell->force = player->dir;
				player->energy -= 20;
				newSpell->radiusChangePerUpdate = -0.00001;
				scene.AddObject(newSpell);
				staff->attack = true;
				staff->attackback = false;
			}
		}
	}
	if (scene.menu)
	{
		int nx = 100 - (x * 1.0 / window_width * 100);
		int ny = 100 - (y * 1.0 / window_height * 100);
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if ((nx >= 45 && nx <= 55) && (ny >= 47 && ny <= 53))
			{
				scene.menu = false;
				scene.pause = true;
				SoundEngineMenu->drop();

			}

			if ((nx >= 45 && nx <= 55) && (ny >= 39 && ny <= 45))
			{
				glutLeaveMainLoop();
			}
		}
	}
	else if (scene.pause)
	{
		int nx = 100 - (x * 1.0 / window_width * 100);
		int ny = 100 - (y * 1.0 / window_height * 100);
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if ((nx >= 45 && nx <= 55) && (ny >= 28 && ny <= 34))
			{
				scene.pause = false;
				captureMouse = true;
				glutSetCursor(GLUT_CURSOR_NONE);
				if (!scene.musicplaying)
				{
					scene.SoundEngine->play2D("../Resources/Sounds/wizardtheme.mp3", true);
					scene.musicplaying = true;
				}
				return;
			}

			if ((nx >= 45 && nx <= 55) && (ny >= 20 && ny <= 26))
			{
				gameClose = true;
			}
		}
	}
	else if (scene.gameOver)
	{
		int nx = 100 - (x * 1.0 / window_width * 100);
		int ny = 100 - (y * 1.0 / window_height * 100);
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if ((nx >= 45 && nx <= 55) && (ny >= 35 && ny <= 41))
			{
				gameClose = true;
			}
		}
	}
}

void OnTimer(int id)
{
	if (!scene.menu && !scene.pause)
	{
		if (keystate['w']) {
			player->velocity_vertical = 2;
		}
		if (keystate['s']) {
			player->velocity_vertical = -1;
		}
		if (keystate['a']) {
			player->velocity_horizontal = 1;
		}
		if (keystate['d']) {
			player->velocity_horizontal = -1;
		}

		if (captureMouse)
		{
			float theta = atan2(player->dir.z, player->dir.x);
			if (mousePosition.x < window_width / 2) {
				theta -= 0.002f * fabs(window_width / 2 - mousePosition.x);
			}
			if (mousePosition.x > window_width / 2) {
				theta += 0.002f * fabs(window_width / 2 - mousePosition.x);
			}
			float phi = acos(player->dir.y);
			if (mousePosition.y > window_height / 2) {
				phi += 0.002f * fabs(window_height / 2 - mousePosition.y);
			}
			if (mousePosition.y < window_height / 2) {
				phi -= 0.002f * fabs(window_height / 2 - mousePosition.y);
			}
			if (phi < PI / 4.1) phi = PI / 4.1;
			if (phi > PI / 1.3) phi = PI / 1.3;
			player->dir.x = sin(phi) * cos(theta);
			player->dir.z = sin(phi) * sin(theta);
			player->dir.y = cos(phi);

			glutWarpPointer(window_width / 2, window_height / 2);
		}

		scene.Update();
		if (player->velocity_up <= 0.02) player->jump = false;
	}
	if (gameClose)
	{
		scene.SoundEngine->drop();
		glutLeaveMainLoop();
	}
	if (player->health <= 0) 
	{
		scene.gameOver = true;
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		captureMouse = false;
	}
	glutTimerFunc(17, OnTimer, 0);
}

void OnRender() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	scene.hud.points = player->points;
	scene.hud.energy = player->energy;
	scene.hud.health = player->health;
	scene.HeadUpDisplay();
	gluLookAt(
		player->pos.x, player->pos.y, player->pos.z,
		player->pos.x + player->dir.x, player->pos.y + player->dir.y, player->pos.z + player->dir.z,
		0.0f, 1.0f, 0.0f
	);
	if (!scene.menu && !scene.pause)
	{

		GLfloat l0_ambient[] = { 0.2f, 0.2f, 0.2f };
		GLfloat l0_diffuse[] = { 1.0f, 1.0f, 1.0 };
		GLfloat l0_specular[] = { 0.5f, 0.5f, 0.5f };
		GLfloat l0_position[] = { player->pos.x, player->pos.y, player->pos.z, 1.0f };

		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_position);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.3);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.001);



		GLfloat l1_ambient[] = { 0.4f, 0.4f, 0.4f };
		GLfloat l1_diffuse[] = { 0.6f, 0.6f, 0.6f };
		GLfloat l1_specular[] = { 0.1f, 0.1f, 0.1f };
		GLfloat l1_position[] = { -player->dir.x, -player->dir.y, -player->dir.z, 0.0f };

		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, l1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, l1_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, l1_position);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);


		scene.Render();
	}
	

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

	
}

void OnReshape(int width, int height) {

	window_width = width;
	window_height = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float) width / height, .01f, 250.0f);
}