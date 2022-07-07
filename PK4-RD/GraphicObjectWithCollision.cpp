#include "GraphicObjectWithCollision.h"
#include "Game.h"
//---------------------------------------------------------------------

GraphicObjectWithCollision::GraphicObjectWithCollision(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame)
	:GraphicObject(pPosition, pSize, pTexture),
	game(pGame)
{
}

//---------------------------------------------------------------------

bool GraphicObjectWithCollision::isColliding(std::weak_ptr<GraphicObjectWithCollision> testedObject)
{
	if (this->getCollisionBox().intersects(testedObject.lock()->getCollisionBox()))
	{
		this->onCollision();
		testedObject.lock()->onCollision();
		return true;
	}
	return false;
}

//---------------------------------------------------------------------

void GraphicObjectWithCollision::move(sf::Vector2f shift)
{
	position.x += shift.x;
	position.y += shift.y;
	shape.setPosition(position);
}


//---------------------------------------------------------------------

void GraphicObjectWithCollision::draw()
{
	game->getRenderWindow().lock()->draw(shape);
}

//---------------------------------------------------------------------

sf::FloatRect GraphicObjectWithCollision::getCollisionBox()
{
	return sf::FloatRect(shape.getPosition(), shape.getSize());
}

//---------------------------------------------------------------------
