#include "Grass.h"
#include <iostream>

void Grass::setTextures(Texture2D _grass)
{
	grassTexture = _grass;
}

void Grass::collisionBox()
{
	collisionBox_entity.x = position.x;
	collisionBox_entity.y = position.y;
	collisionBox_entity.width = static_cast <float> (grassTexture.width);
	collisionBox_entity.height = static_cast <float> (grassTexture.height);
}

Vector2 Grass::getPosition()
{
	return position;
}

float Grass::getHealth()
{
	return health;
}

bool Grass::getSpreading()
{
	return isSpreading;
}

Rectangle Grass::getCollisionBox()
{
	return collisionBox_entity;
}

bool Grass::getStomped()
{
	return isTrampled;
}

bool Grass::getDead()
{
	return dead;
}

void Grass::sense(std::list<Rectangle> sheepCollider, std::list<Rectangle> wolfCollider)
{
	for (auto& sheepCollider : sheepCollider)
	{
		if (sheepCollider.x == collisionBox_entity.x &&
			sheepCollider.y == collisionBox_entity.y)
		{
			health -= 50 * GetFrameTime();
		}
	}

	for (auto sheepCollider : sheepCollider)
	{
		if (CheckCollisionRecs(sheepCollider, collisionBox_entity))
		{
			health -= 25 * GetFrameTime();
			isTrampled = true;
		}
		else
		{
			isTrampled = false;
		}
	}

	for (auto wolfCollider : wolfCollider)
	{
		if (CheckCollisionRecs(wolfCollider, collisionBox_entity))
		{
			health -= 25 * GetFrameTime();
			isTrampled = true;
		}
		else
		{
			isTrampled = false;
		}
	}
}

void Grass::decide()
{
	if (health < 100 && isMature == false && isTrampled == false)
	{
		growing = true;
	}
	else
	{
		growing = false;
	}

	if (health >= 100)
	{
		wantsToSpread = true;
		isMature = true;
	}
}

void Grass::act()
{
	if (wantsToSpread == true)
	{
		isSpreading = true;
	}

	if (growing == true)
	{
		health += 20 * GetFrameTime();
	}

	if (health < 0)
	{
		dead = true;
	}
}

void Grass::update()
{
	collisionBox();
}

void Grass::draw()
{
	if (dead == false)
	{
		DrawTextureRec(grassTexture, Rectangle{ 0, 0, static_cast <float> (grassTexture.width),static_cast <float> (grassTexture.height) }, position, WHITE);
	}
}

Grass::Grass(float posX, float posY, Texture2D grass_texture)
	:position{ posX, posY }
	, grassTexture(grass_texture)
{
}