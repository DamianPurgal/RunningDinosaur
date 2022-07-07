#include "Player.h"

//---------------------------------------------------------------------

bool Player::isJumping()
{
	return jumping;
}

//---------------------------------------------------------------------

void Player::setJumpingStatus(bool status)
{
	jumping = status;
}

//---------------------------------------------------------------------

Player::Player(Vector2f pPosition, Vector2f pSize, Texture pTexture, Game* pGame, bool pAlive)
	: alive(pAlive),
	velocity(0),
	acceleration(ACCELERATION),
	jumping(false),
	GraphicObjectWithCollision(pPosition, pSize, pTexture, pGame)
{
}

//---------------------------------------------------------------------

void Player::Update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime = 0;
		velocity = velocity - acceleration * 0.01;
		move({ 0,-velocity });
	}
}

//---------------------------------------------------------------------

bool Player::isAlive()
{
	return alive;
}

//---------------------------------------------------------------------

void Player::onCollision()
{
	alive = false;
}

//---------------------------------------------------------------------

bool Player::isColliding(std::weak_ptr<GraphicObjectWithCollision> testedObject)
{
	return false;
}

//---------------------------------------------------------------------

void Player::setVelocity(float v)
{
	velocity = v;
}

//---------------------------------------------------------------------

void Player::move(sf::Vector2f shift)
{
	position.x += shift.x;
	position.y += shift.y;
	if (this->position.y > PLAYER_START_POS_Y)
	{
		position.y = PLAYER_START_POS_Y;
		jumping = false;
	}
	shape.setPosition(position);
}

//---------------------------------------------------------------------