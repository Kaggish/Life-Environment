#pragma once
#include "raylib.h"
#include <list>
#include <vector>
#include <unordered_map>
#include "Sheep.h"

class SheepManager
{
	Texture2D sheepTexture;

	unsigned int frameTime = 0;

private:
	void breedSheep();
	void deleteSheep();
	void spawnFirstSheep();

public:
	std::vector<Sheep> sheep;
	void setTexture(Texture2D _sheepTexture);
	void onStart();
	void update(std::list<Rectangle> grassCollider, std::list<Rectangle> wolfCollider);
	void draw();
};