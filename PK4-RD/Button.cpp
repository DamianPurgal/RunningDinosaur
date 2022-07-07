#include "Button.h"

//---------------------------------------------------------------------

Button::Button(Vector2f pPosition, Vector2f pSize, Texture pTexture, std::weak_ptr<RenderWindow> pWindow, std::string pText, bool pFocused)
	:GraphicObject(pPosition, pSize, pTexture),
	window(pWindow),
	focused(pFocused)
{
	font.loadFromFile("Rubik.ttf");
	text.setString(pText);
	text.setFont(font);
	text.setCharacterSize(BUTTON_HEIGHT * 3 / 5);
	text.setPosition({ shape.getPosition().x + 80,shape.getPosition().y + BUTTON_HEIGHT * 1 / 6 });
	setActualTexture();
}

//---------------------------------------------------------------------

void Button::setActualTexture()
{
	sf::Vector2u textureSize = texture.getSize();
	textureSize.x /= 2;
	shape.setTextureRect(IntRect(focused * textureSize.x, 0, textureSize.x, textureSize.y));
}

//---------------------------------------------------------------------

bool Button::isFocused()
{
	return focused;
}

//---------------------------------------------------------------------

void Button::setFocused(bool focus)
{
	focused = focus;
	setActualTexture();
}

//---------------------------------------------------------------------

void Button::draw()
{
	window.lock()->draw(shape);
	window.lock()->draw(text);
}

//---------------------------------------------------------------------
