#pragma once
#include "Grid.h"
#include "raylib.h"
#include "SheepManager.h"
#include "WolfManager.h"

class Scene
{
	Grid grid;
	SheepManager sheepManager;
	WolfManager wolfManager;

	void loadTextures();
	Texture2D sheepTexture;
	Texture2D wolfTexture;

	std::list<Rectangle> sheepCollider;
	std::list<Rectangle> grassCollider;
	std::list<Rectangle> wolfCollider;

private:
	void createSheepColliderList();
	void createGrassColliderList();
	void createWolfColliderList();

public:
	Scene() = default;
	~Scene() = default;

	void onStart();
	void update();
	void draw();

	void unloadTextures();
};
