#pragma once
#include <SFML/Graphics.hpp>
#include "GraphicObject.h"
#include <memory>
class Game;
class GraphicObjectWithCollision : public GraphicObject
{
protected:
	Game* game;
public:
	GraphicObjectWithCollision(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame);
	virtual ~GraphicObjectWithCollision() {};
	virtual void onCollision() {};
	virtual bool isColliding(std::weak_ptr<GraphicObjectWithCollision> testedObject);
	virtual void Update(float deltaTime) {};
	virtual void move(sf::Vector2f shift);
	void draw();
	sf::FloatRect getCollisionBox();
};

