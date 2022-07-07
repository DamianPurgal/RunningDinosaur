#pragma once
#include "GraphicObjectWithCollision.h"
#include "constant.h"
#include <cmath>
#include <memory>
class Game;
class Player : public GraphicObjectWithCollision
{
private:
	int alive;
	float acceleration;
	float velocity;
	bool jumping;
	void move(sf::Vector2f shift);
public:
	bool isJumping();
	void setJumpingStatus(bool status);
	Player(Vector2f pPosition, Vector2f pSize , Texture pTexture, Game* pGame, bool pAlive = true);
	void Update(float deltaTime);
	bool isAlive();
	void onCollision();
	bool isColliding(std::weak_ptr<GraphicObjectWithCollision> testedObject);
	void setVelocity(float v);

};

