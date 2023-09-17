#include "SheepManager.h"

void SheepManager::setTexture(Texture2D _sheepTexture)
{
	sheepTexture = _sheepTexture;
}

void SheepManager::deleteSheep()
{
	for (int i = 0; i < sheep.size(); ++i)
	{
		if (sheep.at(i).getDead() == true)
		{
			if (i < sheep.size() - 1)
			{
				std::swap(sheep.at(i), sheep.at(i + 1));
			}
			else if (i == sheep.size() - 1)
			{
				sheep.pop_back();
			}
		}
	}
}

void SheepManager::spawnFirstSheep()
{
	for (int i = 0; i < 10; ++i)
	{
		float posX = static_cast <float> (rand() % 1150 + 50);
		float posY = static_cast <float> (rand() % 500 + 50);
		sheep.push_back(Sheep(posX, posY, sheepTexture));
	}
}

void SheepManager::breedSheep()
{
	for (int i = 0; i < sheep.size(); ++i)
	{
		if (sheep.at(i).getBreedCooldown() < 0.0f && sheep.at(i).getState() == sheepState::breeding)
		{
			sheep.push_back(Sheep(sheep.at(i).getPosition().x + 50, sheep.at(i).getPosition().y + 50, sheepTexture, 30.0f, 100.0f));
			sheep.at(i).setBreedCooldown(100.0f);
		}
	}
}

void SheepManager::onStart()
{
	spawnFirstSheep();
}

void SheepManager::update(std::list<Rectangle> grassCollider, std::list<Rectangle> wolfCollider)
{
	frameTime++;
	for (int i = 0; i < sheep.size(); ++i)
	{
		if (frameTime % 10 == 0)
		{
			sheep.at(i).sense(grassCollider, wolfCollider);
			sheep.at(i).decide();
		}
		sheep.at(i).act(wolfCollider);
		sheep.at(i).update();
	}
	breedSheep();

	if (frameTime % 10 == 0)
	{
		deleteSheep();
	}
}

void SheepManager::draw()
{
	for (int i = 0; i < sheep.size(); ++i)
	{
		sheep.at(i).draw();
	}
}
