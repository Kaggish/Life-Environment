#include "Grid.h"
#include <iostream>



Tile::Tile(Vector2 position)
	: position(position)
	, textureID(0)
	, uniqueID(0)
{
}

void Tile::draw()
{
	if (textureID == 1)
	{
		DrawTextureRec(dirtTexture, Rectangle{0, 0, static_cast <float> (dirtTexture.width),static_cast <float> (dirtTexture.height)}, position, WHITE);
	}
	else
	{
		DrawTextureRec(wallTexture, Rectangle{0, 0, static_cast <float> (wallTexture.width),static_cast <float> (wallTexture.height)}, position, WHITE);
	}
}

void Tile::setDirtTextures(Texture2D _dirt)
{
	dirtTexture = _dirt;
}

void Tile::setWallTextures(Texture2D _wall)
{
	wallTexture = _wall;
}

void Tile::setTextureID(int texture_id)
{
	textureID = texture_id;
}

void Tile::setUniqueID(int unique_id)
{
	uniqueID = unique_id;
}

void Tile::setIsTaken(bool _isTaken)
{
	isTaken = _isTaken;
}

Vector2 Tile::getPosition()
{
	return position;
}

int Tile::getTextureID()
{
	return textureID;
}

int Tile::getUniqueID(float posX, float posY)
{
	if (posX == position.x && posY == position.y)
	{
		return uniqueID;
	}
	return false;
}

bool Tile::getIsTaken()
{
	return isTaken;
}

Grid::Grid()
	:width(1250)
	,height(750)
	,gridsizeX(0)
	,gridsizeY(0)
	,tileDiameter(0)
	
{
}

void Grid::createMap()
{
	for (int X = 0; X < gridsizeX; ++X)
	{	
		for (int Y = 0; Y < gridsizeY; ++Y)
		{
			tile.push_back(Tile(Vector2(X * tileDiameter, Y * tileDiameter)));
		}
	}
}

void Grid::positionTiles()
{
	float tileRadius = 25;
	tileDiameter = tileRadius * 2;
	gridsizeX = (width / tileDiameter);
	gridsizeY = (height / tileDiameter);
	loadTextures();
	createMap();

	for (int i = 0; i < tile.size(); ++i)
	{
		if (tile.at(i).getPosition().y > 0 && tile.at(i).getPosition().y < 700 &&
			tile.at(i).getPosition().x > 0 && tile.at(i).getPosition().x < 1200)
		{
			tile.at(i).setTextureID(1);
		}

		tile.at(i).setUniqueID(i);
	}

	for (int i = 0; i < tile.size(); ++i)
	{
		tile.at(i).setDirtTextures(dirtTexture);
		tile.at(i).setWallTextures(wallTexture);
	}
}

void Grid::releaseTile(Tile& tile, Grass& tileChecker)
{
	if (tile.getPosition().x == tileChecker.getPosition().x &&
		tile.getPosition().y == tileChecker.getPosition().y)
	{
		tile.setIsTaken(false);
	}
}

void Grid::checkIfNeighborValid(Tile& tile, Vector2 tileChecker)
{
	if (tile.getPosition().x == tileChecker.x &&
		tile.getPosition().y == tileChecker.y &&
		tile.getTextureID() == 1 && tile.getIsTaken() == false)
	{
		spread(tileChecker);
		tile.setIsTaken(true);
	}
}

void Grid::spread(Vector2 spreadPosition)
{
	grass.push_back(Grass(spreadPosition.x, spreadPosition.y, grassTexture));
}

void Grid::searchNeighbors(float currentPosX, float currentPosY)
{
	Vector2 northNeighbor = {currentPosX, currentPosY - tileDiameter};
	Vector2 eastNeighbor = {currentPosX + tileDiameter, currentPosY};
	Vector2 southNeighbor = {currentPosX, currentPosY + tileDiameter};
	Vector2 westNeighbor = {currentPosX - tileDiameter, currentPosY};

	for (int i = 0; i < tile.size(); ++i)
	{
		checkIfNeighborValid(tile.at(i), northNeighbor);
		checkIfNeighborValid(tile.at(i), eastNeighbor);
		checkIfNeighborValid(tile.at(i), southNeighbor);
		checkIfNeighborValid(tile.at(i), westNeighbor);
	}
}

bool Grid::validGrassLocation()
{
	while (ammountOfGrass < 2)
	{
		v1 = rand() % (tile.size() - 2);
		if (tile.at(v1).getTextureID() == 1)
		{
			grass.push_back(Grass(tile.at(v1).getPosition().x, tile.at(v1).getPosition().y, grassTexture));
			tile.at(v1).setIsTaken(true);
		}
		else
		{
			validGrassLocation();
		}
		ammountOfGrass++;
	}
	return true;
}

void Grid::deleteGrass()
{
	for (int i = 0; i < grass.size(); ++i)
	{
		if (grass.at(i).getDead() == true)
		{
			if (i < grass.size() - 1)
			{
				std::swap(grass.at(i), grass.at(i + 1));
			}
			else if (i == grass.size() - 1)
			{
				for (int x = 0; x < tile.size(); ++x)
				{
					releaseTile(tile.at(x), grass.at(i));
				}
				grass.pop_back();
			}
		}
	}
}

void Grid::changeTexture()
{
	for (int i = 0; i < grass.size(); ++i)
	{
		if (grass.at(i).getHealth() == 50)
		{
			grass.at(i).setTextures(grassTexture2);
		}
		else if (grass.at(i).getHealth() == 100)
		{
			grass.at(i).setTextures(grassTexture3);
		}
	}
}

void Grid::loadTextures()
{
	dirtTexture = LoadTexture("Assets/Dirt.png");

	wallTexture = LoadTexture("Assets/Wall.png");

	grassTexture = LoadTexture("Assets/Grass1.png");

	grassTexture2 = LoadTexture("Assets/Grass2.png");

	grassTexture3 = LoadTexture("Assets/Grass3.png");
}

void Grid::onStart()
{
	positionTiles();
	validGrassLocation();
}

void Grid::update(std::list<Rectangle> sheepCollider, std::list<Rectangle> wolfCollider)
{
	frameTime++;
	for (int i = 0; i < grass.size(); ++i)
	{
		grass.at(i).update();

		if (frameTime % 4 == 0)
		{
			grass.at(i).decide();
			grass.at(i).sense(sheepCollider, wolfCollider);
		}
		grass.at(i).act();

		changeTexture();

		if (grass.at(i).getSpreading() == true)
		{
			searchNeighbors(grass.at(i).getPosition().x, grass.at(i).getPosition().y);
		}
	}

	if (frameTime % 10 == 0)
	{
		deleteGrass();
	}
}

void Grid::draw()
{
	for (int i = 0; i < tile.size(); ++i)
	{
		tile.at(i).draw();
	}

	for (int i = 0; i < grass.size(); ++i)
	{
		grass.at(i).draw();
	}
}

void Grid::unloadTextures()
{
	UnloadTexture(grassTexture);
	UnloadTexture(grassTexture2);
	UnloadTexture(grassTexture3);
	UnloadTexture(wallTexture);
	UnloadTexture(dirtTexture);
}

float Grid::getTileDiameter()
{
	return tileDiameter;
}
