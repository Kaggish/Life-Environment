#pragma once
#include "raylib.h"
#include <list>
#include <vector>
#include <unordered_map>
#include "Wolf.h"

class WolfManager
{
	Texture2D wolfTexture;

	unsigned int frameTime = 0;

private:
	void breedWolf();
	void deleteWolf();
	void spawnFirstWolf();

public:
	std::vector<Wolf> wolf;
	void setTexture(Texture2D _wolfTexture);
	void onStart();
	void update(std::list<Rectangle> sheepCollider);
	void draw();
};