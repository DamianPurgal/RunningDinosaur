#include "Scoreboard.h"

//---------------------------------------------------------------------

int Scoreboard::showScoreboard()
{
	init();
	return startLoop();	
}

//---------------------------------------------------------------------

void Scoreboard::setScore(int score)
{
	actualScore = score;
}

//---------------------------------------------------------------------

Scoreboard::Scoreboard(sf::Texture backgroundTexture, sf::Texture pButtonTexture)
	:GraphicObject({ 0,0 }, { WINDOW_WIDTH,WINDOW_HEIGHT }, backgroundTexture),
	buttonTexture(pButtonTexture),
	gamesPlayed(0),
	highestScore(0),
	actualScore(0)
{
	font.loadFromFile("Rubik.ttf");
	textHighestScore.setFont(font);
	textHighestScore.setCharacterSize(int(BUTTON_HEIGHT * 3 / 5));
	textHighestScore.setPosition({ (WINDOW_WIDTH - BUTTON_WIDTH) / 2, SCORE_TEXT_START_POST_Y });

	textGamesPlayed.setFont(font);
	textGamesPlayed.setCharacterSize(int(BUTTON_HEIGHT * 3 / 5));
	textGamesPlayed.setPosition({ (WINDOW_WIDTH - BUTTON_WIDTH) / 2, SCORE_TEXT_START_POST_Y + BUTTON_HEIGHT });

	textActualScore.setFont(font);
	textActualScore.setCharacterSize(int(BUTTON_HEIGHT * 3 / 5));
	textActualScore.setPosition({ (WINDOW_WIDTH - BUTTON_WIDTH) / 2, SCORE_TEXT_START_POST_Y + 2*BUTTON_HEIGHT });
}

//---------------------------------------------------------------------

Scoreboard::~Scoreboard()
{
	while (buttons.size() > 0)
		buttons.pop_back();
	if (window != nullptr)
		window->close();
}

//---------------------------------------------------------------------

void Scoreboard::draw()
{
	window->draw(shape);
	std::for_each(buttons.begin(), buttons.end(), [](std::unique_ptr<Button>& button)
		{
			button->draw();
		}
	);
	window->draw(textActualScore);
	window->draw(textHighestScore);
	window->draw(textGamesPlayed);
}

//---------------------------------------------------------------------

void Scoreboard::init()
{
	window = std::make_shared<RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Running Dinosaur Scoreboard");
	window->setActive(true);
	buttons.push_back(std::make_unique<Button>(sf::Vector2f((WINDOW_WIDTH - BUTTON_WIDTH) / 2, SCORE_TEXT_START_POST_Y + 3 * BUTTON_HEIGHT), sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT), buttonTexture, window, "       EXIT"));
	getDataFromFile();
	gamesPlayed++;
	if (actualScore > highestScore)
		highestScore = actualScore;
	saveDataToFile();
	textHighestScore.setString("  Highest score: " + std::to_string(highestScore));
	textGamesPlayed.setString("  Games played: " + std::to_string(gamesPlayed));
	textActualScore.setString("  Score: " + std::to_string(actualScore));
}

//---------------------------------------------------------------------

int Scoreboard::startLoop()
{
	int actualButtonFocus = 0;
	buttons[actualButtonFocus]->setFocused(true);
	sf::Event event;

	while (window->isOpen())
	{
		while (window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				window->close();
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
			if (unsigned int(actualButtonFocus + 1) < buttons.size())
			{
				buttons[actualButtonFocus]->setFocused(false);
				actualButtonFocus++;
				buttons[actualButtonFocus]->setFocused(true);
			}
		}
		window->clear();
		draw();
		window->display();
	}
	return 404;
}

//---------------------------------------------------------------------

void Scoreboard::getDataFromFile()
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open("score.txt");
		file >> highestScore;
		file >> gamesPlayed;
		file.close();
	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Blad przy otwieraniu pliku z wynikami";
		highestScore = gamesPlayed = 0;
	}
}

//---------------------------------------------------------------------

void Scoreboard::saveDataToFile()
{
	std::ofstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open("score.txt");
		file << highestScore << " ";
		file << gamesPlayed;
		file.close();
	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Blad przy otwieraniu pliku z wynikami" << std::endl;
		std::cout << "Aktualne postepy nie zostaly zapisane" << std::endl;
	}
}

//---------------------------------------------------------------------
