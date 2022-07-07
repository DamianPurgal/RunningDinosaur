#pragma once
#include <vector>
#include <memory>
#include "Button.h"
#include "GraphicObject.h"
#include "constant.h"
class Menu : public GraphicObject
{
private:
	std::vector<std::unique_ptr<Button>> buttons;
	std::weak_ptr<RenderWindow> window;
public:
	Menu(sf::Texture backgroundTexture, sf::Texture buttonTexture, std::weak_ptr<RenderWindow> pWindow);
	~Menu();
	void Update(float deltaTime) {};
	void draw();
	int showMenu(); //zwraca wybrany przycisk
};

