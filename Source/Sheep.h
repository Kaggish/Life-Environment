#pragma once
#include "raylib.h"
#include <list>
#include <vector>
#include <unordered_map>

enum sheepState
{
	wandering,
	lockedOnTarget,
	eating,
	breeding,
	evading,
};

class Sheep
{
private:
	Vector2 position = {};

	bool dead = false;
	bool hungry = false;
	bool grassFound = false;
	bool wolfFound = false;
	bool reachedTarget = false;

	float breedCooldown = 0.0f;
	float health = 70.0f;

	unsigned int updateVector = 0;

	sheepState currentState = sheepState::wandering;

	Rectangle collisionBox_entity;
	Rectangle senseBox;


	Vector2 direction{ 1, 1 };
	Vector2 grassDirection{ 0, 0 };
	Vector2 wolfDirection {0, 0};
	Vector2 grassPosition{ 0, 0 };
	Vector2 evadePosition{ 0, 0 };

	Texture2D sheepTexture;
private:

	bool BorderCollision();
	void senseCollision();
	void collisionBox();

	void findGrass(std::list<Rectangle> grassCollider);
	void Evade(std::list<Rectangle> wolfCollider);
	void takeDamage(std::list<Rectangle> wolfCollider);
	void Wander();
	void goToGrass();
	void runFromWolf();
	void Eat();
	void Breed();

public:
	Sheep() = default;
	Sheep(float posX, float posY, Texture2D sheep_Texture);
	Sheep(float posX, float posY, Texture2D sheep_Texture, float health, float _breedCooldown);
	~Sheep() = default;

	void sense(std::list<Rectangle> grassCollider, std::list<Rectangle> wolfCollider);
	void decide();
	void act(std::list<Rectangle> wolfcollider);

	void update();
	void draw();

	void setBreedCooldown(float cooldown);

	Rectangle getSenseBox();
	Rectangle getCollisionBox();
	Vector2 getPosition();
	bool getDead();
	bool getBreading();
	sheepState getState();
	float getBreedCooldown();

};