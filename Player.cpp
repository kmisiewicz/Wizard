#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	pos.x = 0.0f;
	pos.y = 1.5f;
	pos.z = 10.0f;

	dir.x = 0.0f;
	dir.y = 0.0f;
	dir.z = -1.0f;

	speed = 0.1f;
	radius = 2.0f;

	velocity_horizontal = 0;
	velocity_vertical = 0;
	velocity_up = 0;
	jumpboost = 1;

	flyingMode = false;
	jump = false;

	weight = 1;
	spellSetting = 1;
	objectType = "player";
	points = 0;
	health = 100;
	maxHealth = 100;
	energy = 100;
	maxEnergy = 100;
}


Player::~Player()
{
}

void Player::Render()
{

}

void Player::Update()
{
	vec3 movdir = dir;
	movdir.y = 0;
	movdir = movdir.normalized();
	pos.x += movdir.x * speed * velocity_vertical * jumpboost;
	pos.z += movdir.z * speed * velocity_vertical * jumpboost;

	pos.x += movdir.z * speed * velocity_horizontal;
	pos.z -= movdir.x * speed * velocity_horizontal;

	pos.y += speed * velocity_up;

	velocity_vertical /= 1.2;
	velocity_horizontal /= 1.2;
	velocity_up /= 1.2;
	jumpboost /= 1.2;
	if (jumpboost < 1) jumpboost = 1;

	pos.x += force.x / weight;
	pos.y += force.y / weight;
	pos.z += force.z / weight;

	force.x /= 1.2;
	force.y /= 1.2;
	force.z /= 1.2;

	energy += 0.15f;
	if (health > maxHealth) health = maxHealth;
	if (energy > maxEnergy) energy = maxEnergy;
	if (energy < 0) energy = 0;
}