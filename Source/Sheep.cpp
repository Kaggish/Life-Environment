#include "Sheep.h"
#include <iostream>
#include "raymath.h"
#include <string>


bool Sheep::BorderCollision()
{
	if (position.x > 1150)
	{
		direction.x = -1;
		return true;
	}
	else if (position.x < 50)
	{
		direction.x = 1;
		return true;
	}

	else if (position.y > 650)
	{
		direction.y = -1;
		return true;
	}
	else if (position.y < 50)
	{
		direction.y = 1;
		return true;
	}
	return false;
}

void Sheep::senseCollision()
{
	senseBox.x = position.x - sheepTexture.width;
	senseBox.y = position.y - sheepTexture.height;
	senseBox.width = static_cast <float> (sheepTexture.width * 3);
	senseBox.height = static_cast <float> (sheepTexture.height * 3);
}

void Sheep::collisionBox()
{
	collisionBox_entity.x = position.x;
	collisionBox_entity.y = position.y;
	collisionBox_entity.width = static_cast <float> (sheepTexture.width);
	collisionBox_entity.height = static_cast <float> (sheepTexture.height);
}

void Sheep::findGrass(std::list<Rectangle> collider)
{
	float closestDistance = 100000;
	for (auto& grassCollider : collider)
	{
		if (CheckCollisionRecs(senseBox, grassCollider))
		{
			if (abs(Vector2Distance(Vector2{ grassCollider.x, grassCollider.y }, position)) < closestDistance)
			{
				grassFound = true;
				grassDirection.x = grassCollider.x;
				grassDirection.y = grassCollider.y;
			}

			grassPosition = grassDirection;
		}
	}
}

void Sheep::Evade(std::list<Rectangle> wolfCollider)
{
	float closestDistance = 150;
	for (auto& wolfCollider : wolfCollider)
	{
		if (CheckCollisionRecs(senseBox, wolfCollider))
		{
			if (Vector2Distance(Vector2{ wolfCollider.x, wolfCollider.y }, position) < closestDistance) 
			{
				wolfFound = true;
				wolfDirection.x = wolfCollider.x;
				wolfDirection.y = wolfCollider.y;
			}

			wolfDirection = Vector2Subtract(position, wolfDirection);
			evadePosition = Vector2Add(position, Vector2Scale(Vector2Normalize(wolfDirection), 150));
		}
	}
}

void Sheep::takeDamage(std::list<Rectangle> wolfCollider)
{
	for (auto& wolfCollider : wolfCollider)
	{
		if (CheckCollisionRecs(collisionBox_entity, wolfCollider))
		{
			health -= 40 * GetFrameTime();
		}
	}
}

void Sheep::Wander()
{
	if (updateVector % 60 == 0)
	{
		direction.y = static_cast <float> (GetRandomValue(-1, 1));
		direction.x = static_cast <float> (GetRandomValue(-1, 1));
	}

	Vector2Normalize(direction);
	currentState = wandering;
	position = Vector2Add(position, direction);
}

void Sheep::goToGrass()
{
	position = Vector2MoveTowards(position, grassPosition, 3);
}

void Sheep::runFromWolf()
{
	currentState = evading;
	position = Vector2MoveTowards(position, evadePosition, 2);
	if (Vector2Equals(position, evadePosition))
	{
		currentState = wandering;
	}
}

void Sheep::Eat()
{
	health = health + 40.0f;
	currentState = eating;
}

void Sheep::Breed()
{
	currentState = breeding;
	health = 25.0f;
}

void Sheep::sense(std::list<Rectangle> grassCollider, std::list<Rectangle> wolfCollider)
{
	if (hungry == true)
	{
		findGrass(grassCollider);
	}
}

void Sheep::decide()
{
	if (health < 35.0f)
	{
		hungry = true;
	}
	else
	{
		hungry = false;
	}

	if (grassFound == true)
	{
		currentState = lockedOnTarget;
	}

	if (health > 80.0f && breedCooldown < 0.0f)
	{
		currentState = breeding;
	}
}

void Sheep::act(std::list<Rectangle> wolfcollider)
{
	Evade(wolfcollider);
	takeDamage(wolfcollider);

	if (currentState == lockedOnTarget)
	{
		goToGrass();
		if (position.x == grassPosition.x &&
			position.y == grassPosition.y)
		{
			reachedTarget = true;
		}
	}
	else
	{
		Wander();
	}

	if (wolfFound == true && !BorderCollision())
	{
		runFromWolf();
		wolfFound = false;
	}

	if (currentState == breeding)
	{
		Breed();
	}

	if (reachedTarget == true && health < 70.0f && currentState != evading)
	{
		Eat();
		grassFound = false;
		reachedTarget = false;
		currentState = wandering;
		if (health > 80)
		{
			currentState = breeding;
		}
	}
	
	if (health < 0)
	{
		dead = true;
	}
	health -= 1 * GetFrameTime();
}

void Sheep::update()
{
	breedCooldown -= 1 * GetFrameTime();
	updateVector++;
	collisionBox();
	senseCollision();
	BorderCollision();
}

void Sheep::draw()
{
	const char* state[5] = { "wandering", "lockedOnTarget", "eating", "breeding", "evading"};
	if (dead == false)
	{
		DrawTextureRec(sheepTexture, Rectangle{ 0, 0, static_cast <float> (sheepTexture.width),static_cast <float> (sheepTexture.height) }, position, WHITE);
		DrawRectangle(static_cast <int> (position.x), static_cast <int> (position.y) - 10, static_cast <int> (health), 2, BLACK);
		DrawText(state[currentState], static_cast <int> (position.x), static_cast <int> (position.y) - 5, 10, BLACK);
	}
}

void Sheep::setBreedCooldown(float cooldown)
{
	breedCooldown = cooldown;
}


Sheep::Sheep(float posX, float posY, Texture2D sheep_Texture)
	:position{ posX, posY }
	,sheepTexture(sheep_Texture)
{
}

Sheep::Sheep(float posX, float posY, Texture2D sheep_Texture, float health, float _breedCooldown)
	:position{posX, posY}
	,sheepTexture(sheep_Texture)
	,health(health)
	,breedCooldown(_breedCooldown)
{
}

Rectangle Sheep::getSenseBox()
{
	return senseBox;
}

Rectangle Sheep::getCollisionBox()
{
	return collisionBox_entity;
}

Vector2 Sheep::getPosition()
{
	return position;
}

bool Sheep::getDead()
{
	return dead;
}

sheepState Sheep::getState()
{
	return currentState;
}

float Sheep::getBreedCooldown()
{
	return breedCooldown;
}
