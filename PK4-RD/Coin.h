#pragma once
#include "GraphicObjectWithCollision.h"
class Game;
class Coin : public GraphicObjectWithCollision
{
private:
	int points;
	float velocity;
	void move(sf::Vector2f shift);

public:
	bool isColliding(std::weak_ptr<GraphicObjectWithCollision> testedObject);
	void Update(float deltaTime);
	Coin(Game* pGame, sf::Texture pTexture, int pPoints);
	void onCollision();

};

