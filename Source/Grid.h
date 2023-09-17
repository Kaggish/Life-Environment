#pragma once
#include "raylib.h"
#include <list>
#include <vector>
#include <unordered_map>
#include "Grass.h"

class Tile
{
private:
	Vector2 position;
	int textureID;
	int uniqueID;
	bool isTaken = false;

	Texture2D dirtTexture;
	Texture2D wallTexture;

public:
	Tile() = default;
	Tile(Vector2 position);
	~Tile() = default;
	void draw();

	Vector2 getPosition();
	int getTextureID();
	int getUniqueID(float posX, float posY);
	bool getIsTaken();

	void setDirtTextures(Texture2D _dirt);
	void setWallTextures(Texture2D _wall);
	void setTextureID(int _id);
	void setUniqueID(int _id);
	void setIsTaken(bool _isTaken);
};

class Grid
{
	const float width;
	const float height;
	float tileDiameter;
	float gridsizeX;
	float gridsizeY;

	Texture2D dirtTexture;
	Texture2D wallTexture;
	Texture2D grassTexture;
	Texture2D grassTexture2;
	Texture2D grassTexture3;

	int v1 = 0;
	int frameTime = 0;
	int ammountOfGrass = 0;



private:
	void changeTexture();
	void loadTextures();
	void spread(Vector2 spreadPosition);
	void checkIfNeighborValid(Tile& tile, Vector2 tileChecker);
	void searchNeighbors(float currentPosX, float currentPosY);
	bool validGrassLocation();
	void deleteGrass();
	void createMap();
	void positionTiles();
	void releaseTile(Tile& tile, Grass& tileChecker);

public:
	std::vector<Grass> grass;
	std::vector<Tile> tile;
	Grid();
	~Grid() = default;
	void onStart();
	void update(std::list<Rectangle> sheepCollider, std::list<Rectangle> wolfCollider);
	void draw();

	void unloadTextures();
	float getTileDiameter();
};