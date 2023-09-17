#pragma once
#include "raylib.h"
#include <list>
#include <vector>
#include <unordered_map>

class Grass
{
	Vector2 position = {};
	bool isTrampled = false;
	bool isSpreading = false;
	bool wantsToSpread = false;
	bool isMature = false;
	bool loseHealth = false;
	bool growing = false;
	bool dead = false;

	float health = 0;
	Texture2D grassTexture;

	Rectangle collisionBox_entity;

public:
	Grass() = default;
	Grass(float posX, float posY, Texture2D grassTexture);
	virtual ~Grass() = default;

	void setTextures(Texture2D _grass);
	void collisionBox();

	Vector2 getPosition();
	float getHealth();
	bool getSpreading();
	Rectangle getCollisionBox();
	bool getStomped();
	bool getDead();

	void sense(std::list<Rectangle> sheepCollider, std::list<Rectangle> wolfCollider);
	void decide();
	void act();

	void update();
	void draw();
};