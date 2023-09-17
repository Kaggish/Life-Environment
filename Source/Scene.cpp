#include "raylib.h"
#include "Scene.h"

void Scene::loadTextures()
{
	sheepTexture = LoadTexture("Assets/Sheep.png");
	wolfTexture = LoadTexture("Assets/Wolf.png");
}

void Scene::createSheepColliderList()
{
	for (int i = 0; i < sheepManager.sheep.size(); ++i)
	{
		sheepCollider.push_back(sheepManager.sheep.at(i).getCollisionBox());
	}
}

void Scene::createGrassColliderList()
{
	for (int i = 0; i < grid.grass.size(); ++i)
	{
		grassCollider.push_back(grid.grass.at(i).getCollisionBox());
	}
}

void Scene::createWolfColliderList()
{
	for (int i = 0; i < wolfManager.wolf.size(); ++i)
	{
		wolfCollider.push_back(wolfManager.wolf.at(i).getCollisionBox());
	}
}

void Scene::onStart()
{
	loadTextures();
	sheepManager.setTexture(sheepTexture);
	wolfManager.setTexture(wolfTexture);

	grid.onStart();
	sheepManager.onStart();
	wolfManager.onStart();
}

void Scene::update()
{
	sheepManager.update(grassCollider, wolfCollider);

	wolfCollider.clear();
	grassCollider.clear();

	createSheepColliderList();

	wolfManager.update(sheepCollider);

	createWolfColliderList();
	createGrassColliderList();

	grid.update(sheepCollider, wolfCollider);

	sheepCollider.clear();
}

void Scene::draw()
{
	grid.draw();
	sheepManager.draw();
	wolfManager.draw();
}

void Scene::unloadTextures()
{
	UnloadTexture(wolfTexture);
	UnloadTexture(sheepTexture);
	grid.unloadTextures();
}
