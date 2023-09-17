#include "Wolf.h"
#include "raymath.h"
#include <iostream>
#include <string>

bool Wolf::BorderCollision()
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

void Wolf::senseCollision()
{
	senseBox.x = position.x - wolfTexture.width * 2;
	senseBox.y = position.y - wolfTexture.height * 2;
	senseBox.width = static_cast <float> (wolfTexture.width * 5);
	senseBox.height = static_cast <float> (wolfTexture.height * 5);
}

void Wolf::collisionBox()
{
	collisionBox_entity.x = position.x;
	collisionBox_entity.y = position.y;
	collisionBox_entity.width = static_cast <float> (wolfTexture.width);
	collisionBox_entity.height = static_cast <float> (wolfTexture.height);
}

void Wolf::findSheep(std::list<Rectangle> collider)
{
	float closestDistance = 100000;
	for (auto& sheepCollider : collider)
	{
		if (CheckCollisionRecs(senseBox, sheepCollider))
		{
			if (abs(Vector2Distance(Vector2{ sheepCollider.x, sheepCollider.y }, position)) < 150)
			{
				sheepFound = true;
				targetDirection.x = sheepCollider.x;
				targetDirection.y = sheepCollider.y;
			}
			sheepPosition = targetDirection;
		}
	}
}

void Wolf::Wander()
{
	if (updateVector % 60 == 0)
	{
		direction.y = static_cast <float> (GetRandomValue(-1, 1));
		direction.x = static_cast <float> (GetRandomValue(-1, 1));
	}
	Vector2Normalize(direction);
	currentState = wander;
	position = Vector2Add(position, direction);
}

void Wolf::collideCheckSheep(std::list<Rectangle> collider)
{
	for (auto& sheepCollider : collider)
	{
		if (CheckCollisionRecs(collisionBox_entity, sheepCollider))
		{
			Eat();
		}
	}
}

void Wolf::Eat()
{
	health = health + 50.0f;
	currentState = eat;
}

void Wolf::Breed()
{
	currentState = breed;
	health = 25.0f;
}

void Wolf::goToSheep()
{
	position = Vector2MoveTowards(position, sheepPosition, 3);
}

void Wolf::sense(std::list<Rectangle> collider)
{
	if (hungry == true)
	{
		findSheep(collider);
	}
}

void Wolf::decide()
{
	if (health < 35.0f)
	{
		hungry = true;
	}
	else
	{
		hungry = false;
	}

	if (sheepFound == true && hungry == true)
	{
		currentState = pursuing;
	}
	else
	{
		currentState = wander;
	}

	if (health > 80.0f && breedCooldown < 0.0f)
	{
		currentState = breed;
	}
}

void Wolf::act(std::list<Rectangle> collider)
{
	if (currentState == pursuing)
	{
		goToSheep();
		if (position.x == sheepPosition.x &&
			position.y == sheepPosition.y)
		{
			reachedTarget = true;
		}
	}
	else
	{
		Wander();
	}

	if (currentState == breed)
	{
		Breed();
	}

	if (reachedTarget == true && health < 70.0f)
	{
		Eat();
		sheepFound = false;
		reachedTarget = false;
		currentState = wander;
		if (health > 80)
		{
			currentState = breed;
		}
	}

	if (health < 0)
	{
		dead = true;
	}

	health -= 1 * GetFrameTime();
}

void Wolf::update()
{
	breedCooldown -= 1 * GetFrameTime();
	updateVector++;
	collisionBox();
	senseCollision();
	BorderCollision();

}

void Wolf::draw()
{
	const char* state[4] = { "wandering", "pursuing", "eating", "breeding" };
	if (dead == false)
	{
		DrawTextureRec(wolfTexture, Rectangle{ 0, 0, static_cast <float> (wolfTexture.width),static_cast <float> (wolfTexture.height) }, position, WHITE);
		DrawRectangle(static_cast <int> (position.x), static_cast <int> (position.y) - 10, static_cast <int> (health), 2, BLACK);
		DrawText(state[currentState], static_cast <int> (position.x), static_cast <int> (position.y) - 5, 10, BLACK);
	}
}

Wolf::Wolf(float posX, float posY, Texture2D wolf_Texture)
	:position{posX, posY}
	,wolfTexture(wolf_Texture)
{
}

Wolf::Wolf(float posX, float posY, Texture2D wolf_Texture, float health, float coolDown)
	:position{ posX, posY }
	,wolfTexture(wolf_Texture)
	,health(health)
	,breedCooldown(coolDown)
{
}

void Wolf::setBreedCooldown(float coolDown)
{
	breedCooldown = coolDown;
}

Rectangle Wolf::getSenseBox()
{
    return senseBox;
}

Rectangle Wolf::getCollisionBox()
{
    return collisionBox_entity;
}

bool Wolf::getDead()
{
    return dead;
}

float Wolf::getBreedCooldown()
{
	return breedCooldown;
}

Vector2 Wolf::getPosition()
{
	return position;
}

wolfState Wolf::getState()
{
	return currentState;
}
