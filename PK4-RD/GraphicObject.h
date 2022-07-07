#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class GraphicObject
{
protected:
	RectangleShape shape;
	Texture texture;
	Vector2f position;
	float switchTime;
	float totalTime;
public:
	GraphicObject(Vector2f pPosition, Vector2f pSize, Texture pTexture = Texture::Texture());
	virtual void draw() = 0;
	virtual void Update(float deltaTime) = 0;
	void setPosition(Vector2f pPosition);

};

