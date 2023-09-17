#include "WolfManager.h"

void WolfManager::setTexture(Texture2D _wolfTexture)
{
	wolfTexture = _wolfTexture;
}

void WolfManager::breedWolf()
{
	for (int i = 0; i < wolf.size(); ++i)
	{
		if (wolf.at(i).getBreedCooldown() < 0 && wolf.at(i).getState() == wolfState::breed)
		{
			wolf.push_back(Wolf(wolf.at(i).getPosition().x + 50, wolf.at(i).getPosition().y + 50, wolfTexture, 30.0f, 100.0f));
			wolf.at(i).setBreedCooldown(100.0f);
		}
	}
}

void WolfManager::deleteWolf()
{
	for (int i = 0; i < wolf.size(); ++i)
	{
		if (wolf.at(i).getDead() == true)
		{
			if (i < wolf.size() - 1)
			{
				std::swap(wolf.at(i), wolf.at(i + 1));
			}
			if (i == wolf.size() - 1)
			{
				wolf.pop_back();
			}
		}
	}
}

void WolfManager::spawnFirstWolf()
{
	float posX = static_cast <float> (rand() % 1150 + 50);
	float posY = static_cast <float> (rand() % 650 + 50);
	wolf.push_back(Wolf(posX, posY, wolfTexture));
}

void WolfManager::onStart()
{
	spawnFirstWolf();
}

void WolfManager::update(std::list<Rectangle> sheepCollider)
{
	frameTime++;

	for (int i = 0; i < wolf.size(); ++i)
	{
		wolf.at(i).update();
		if (frameTime % 3 == 0)
		{
			wolf.at(i).sense(sheepCollider);
			wolf.at(i).decide();
		}
		wolf.at(i).act(sheepCollider);
	}
	breedWolf();

	if (frameTime % 10 == 0)
	{
		deleteWolf();
	}
}

void WolfManager::draw()
{
	for (int i = 0; i < wolf.size(); ++i)
	{
		wolf.at(i).draw();
	}
}
