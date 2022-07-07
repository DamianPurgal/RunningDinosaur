#include "Coin.h"
#include "Game.h"

//---------------------------------------------------------------------

void Coin::move(sf::Vector2f shift)
{
	position.x += shift.x;
	position.y += shift.y;
	shape.setPosition(position);
	if (position.x + COIN_WIDTH <= 0)
		game->removeObject(this);
}

//---------------------------------------------------------------------

bool Coin::isColliding(std::weak_ptr<GraphicObjectWithCollision> testedObject)
{
	if (this->getCollisionBox().intersects(testedObject.lock()->getCollisionBox()))
	{
		this->onCollision();
		return true;
	}
	return false;
}

//---------------------------------------------------------------------

void Coin::Update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime = 0;
		move({ -velocity, 0 });
	}
}

//---------------------------------------------------------------------

Coin::Coin(Game* pGame, sf::Texture pTexture, int pPoints)
	:GraphicObjectWithCollision({ COIN_START_POS_X + 300,COIN_START_POS_Y }, { COIN_WIDTH,COIN_HEIGHT }, pTexture, pGame),
	velocity(COIN_VELOCITY),
	points(pPoints)
{
	this->switchTime = COIN_SWITCH_TIME;
}

//---------------------------------------------------------------------

void Coin::onCollision()
{
	game->addScore(points);
	game->removeObject(this);
}

//---------------------------------------------------------------------
