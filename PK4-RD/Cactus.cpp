#include "Cactus.h"
#include "Game.h"
#include <iostream>

//---------------------------------------------------------------------

Cactus::Cactus(Game* pGame, sf::Texture pTexture, cactusType pType)
	:GraphicObjectWithCollision({ CACT_START_POS_X,CACT_START_POS_Y }, { 10,10 }, pTexture, pGame),
	type(pType),
	velocity(CACTUS_VELOCITY)
{
	if (type == cactusType::small)
	{
		this->shape.setSize({CACT_SMALL_WIDTH,CACT_HEIGHT});
		shape.setTextureRect(sf::IntRect(0, 0, CACT_SMALL_WIDTH, CACT_HEIGHT));
	}
	else
	{
		this->shape.setSize({ CACT_BIG_WIDTH,CACT_HEIGHT });
		shape.setTextureRect(sf::IntRect(CACT_SMALL_WIDTH, 0, CACT_BIG_WIDTH, CACT_HEIGHT));
	}
	this->switchTime = CACTUS_SWITCH_TIME;
}

//---------------------------------------------------------------------

void Cactus::Update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime = 0;
		move({ -velocity, 0 });
	}
}

//---------------------------------------------------------------------

void Cactus::move(sf::Vector2f shift)
{
	position.x += shift.x;
	position.y += shift.y;
	shape.setPosition(position);
	if (type == cactusType::small)
	{
		if (position.x + CACT_SMALL_WIDTH <= 0)
			game->removeObject(this);
	}else if (position.x + CACT_BIG_WIDTH <= 0)
		game->removeObject(this);
}

//---------------------------------------------------------------------