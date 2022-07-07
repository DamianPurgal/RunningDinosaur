#pragma once
#include "GraphicObjectWithCollision.h"
#include "constant.h"
#include <cmath>
#include <memory>
class Game;
class Cactus : public GraphicObjectWithCollision
{
public:
	enum class cactusType
	{
		small = 0,
		big = 1
	};

private:
	int size;
	cactusType type;
	float velocity;
	void move(sf::Vector2f shift);
public:
	void Update(float deltaTime);
	Cactus(Game* pGame, sf::Texture pTexture, cactusType pType = Cactus::cactusType::small);
};

