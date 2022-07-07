#pragma once
#include "GraphicObjectWithCollision.h"
#include "constant.h"

class FlyingDinosaur : public GraphicObjectWithCollision
{
private:

	enum class textureType {
		wings_down = 0,
		wings_up = 1
	}actualTexture;

	float velocity;
	float textureChangeTotalTime;
private:
	void changeTexture();
	void move(sf::Vector2f shift);

public:
	void Update(float deltaTime);
	FlyingDinosaur(Game* pGame, sf::Texture pTexture);
};

