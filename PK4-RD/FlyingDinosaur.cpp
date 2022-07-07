#include "FlyingDinosaur.h"
#include "Game.h"

//---------------------------------------------------------------------

void FlyingDinosaur::changeTexture()
{
	if (actualTexture == textureType::wings_down)
		actualTexture = textureType::wings_up;
	else
		actualTexture = textureType::wings_down;

	sf::Vector2u textureSize = texture.getSize();
	shape.setTextureRect(sf::IntRect(int(actualTexture) * textureSize.x / 2, 0, FLYING_DINOSAUR_WIDTH, FLYING_DINOSAUR_HEIGHT));
}

//---------------------------------------------------------------------

void FlyingDinosaur::move(sf::Vector2f shift)
{
	position.x += shift.x;
	position.y += shift.y;
	shape.setPosition(position);
	if (position.x + FLYING_DINOSAUR_WIDTH <= 0)
		game->removeObject(this);
}

//---------------------------------------------------------------------

void FlyingDinosaur::Update(float deltaTime)
{
	textureChangeTotalTime += deltaTime;
	if (textureChangeTotalTime >= FLYING_DINOSAUR_TEXTURE_SWITCH_TIME)
	{
		textureChangeTotalTime = 0;
		changeTexture();
	}
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime = 0;
		move({ -velocity, 0 });
	}
}

//---------------------------------------------------------------------

FlyingDinosaur::FlyingDinosaur(Game* pGame, sf::Texture pTexture)
	:GraphicObjectWithCollision({ FLYING_DINOSAUR_START_POS_X,FLYING_DINOSAUR_START_POS_Y }, { FLYING_DINOSAUR_WIDTH,FLYING_DINOSAUR_HEIGHT }, pTexture, pGame),
	velocity(FLYING_DINOSAUR_VELOCITY),
	actualTexture(textureType::wings_up),
	textureChangeTotalTime(0.0)
{
	changeTexture();
	this->switchTime = FLYING_DINOSAUR_SWITCH_TIME;
}

//---------------------------------------------------------------------