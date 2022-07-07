#include "Menu.h"

//---------------------------------------------------------------------

int Menu::showMenu()
{
	int actualButtonFocus = 0;
	buttons[actualButtonFocus]->setFocused(true);
	sf::Event event;

	while (window.lock()->isOpen())
	{
		while (window.lock()->pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.lock()->close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		{
			return actualButtonFocus;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			if (actualButtonFocus - 1 >= 0)
			{
				buttons[actualButtonFocus]->setFocused(false);
				actualButtonFocus--;
				buttons[actualButtonFocus]->setFocused(true);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			if (actualButtonFocus + 1 < buttons.size())
			{
				buttons[actualButtonFocus]->setFocused(false);
				actualButtonFocus++;
				buttons[actualButtonFocus]->setFocused(true);
			}
		}
		window.lock()->clear();
		draw();
		window.lock()->display();
	}
	return 404;
}

//---------------------------------------------------------------------

Menu::Menu(sf::Texture backgroundTexture, sf::Texture buttonTexture, std::weak_ptr<RenderWindow> pWindow)
	:GraphicObject({ 0,0 }, { WINDOW_WIDTH,WINDOW_HEIGHT }, backgroundTexture),
	window(pWindow)
{
	buttons.push_back(std::make_unique<Button>(sf::Vector2f((WINDOW_WIDTH-BUTTON_WIDTH)/2, BUTTON_START_POS_Y), sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT), buttonTexture, pWindow, "START GAME"));
	buttons.push_back(std::make_unique<Button>(sf::Vector2f((WINDOW_WIDTH - BUTTON_WIDTH) / 2, BUTTON_START_POS_Y + BUTTON_HEIGHT + MENU_SPACING), sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT), buttonTexture, pWindow, "       EXIT"));
}

//---------------------------------------------------------------------

Menu::~Menu()
{
	while (buttons.size() > 0)
		buttons.pop_back();
}

//---------------------------------------------------------------------

void Menu::draw()
{
	window.lock()->draw(shape);
	std::for_each(buttons.begin(), buttons.end(), [](std::unique_ptr<Button>& button) 
		{
			button->draw();
		}
	);
}

//---------------------------------------------------------------------
