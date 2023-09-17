#pragma once
#include "raylib.h"
#include <list>
#include <vector>
#include <unordered_map>

enum wolfState
{
	wander,
	pursuing,
	eat,
	breed,
};

class Wolf
{
private:
	Vector2 position = {};
	bool dead = false;
	bool hungry = false;
	bool sheepFound = false;
	bool reachedTarget = false;

	float breedCooldown = 0.0f;
	float health = 70.0f;
	unsigned int updateVector = 0;

	std::string state;

	Rectangle collisionBox_entity;
	Rectangle senseBox;

	wolfState currentState = wolfState::wander;

	Vector2 direction{ 1 , 1 };
	Vector2 targetDirection{ 0, 0 };
	Vector2 sheepPosition{ 0, 0 };

	Texture2D wolfTexture;
private:
	bool BorderCollision();
	void senseCollision();
	void collisionBox();

	void findSheep(std::list<Rectangle> collider);
	void Wander();
	void collideCheckSheep(std::list<Rectangle> collider);
	void Eat();
	void Breed();
	void goToSheep();

public:
	void sense(std::list<Rectangle> collider);
	void decide();
	void act(std::list<Rectangle> collider);

	void update();
	void draw();

	Wolf() = default;
	Wolf(float posX, float posY, Texture2D wolf_Texture);
	Wolf(float posX, float posY, Texture2D wolf_Texture, float health, float coolDown);
	~Wolf() = default;

	void setBreedCooldown(float coolDown);

	Rectangle getSenseBox();
	Rectangle getCollisionBox();
	bool getDead();
	float getBreedCooldown();
	Vector2 getPosition();
	wolfState getState();
};