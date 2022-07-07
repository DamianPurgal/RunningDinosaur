#include "Game.h"
#include <iostream>

//---------------------------------------------------------------------

Game::Game()
	:window(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Running Dinosaur")),
	score(0),
	Vx(2),
	totalTimePointsForTime(0),
	totalTimeSpawningCactus(0),
	totalTimeSpawningCoin(0),
	totalTimeSpawningFlyingDinosaur(0)
{
	//menu nad scoreboard
	sf::Texture menuBackgroundTexture;
	menuBackgroundTexture.loadFromFile("graphics/menu.png");
	sf::Texture menuButtonTexture;
	menuButtonTexture.loadFromFile("graphics/button.png");
	menu = std::make_unique<Menu>(menuBackgroundTexture, menuButtonTexture, window);
	scoreboard = std::make_unique<Scoreboard>(menuBackgroundTexture, menuButtonTexture);
}

//---------------------------------------------------------------------

Game::~Game()
{
	while (!objects.empty())
		objects.pop_back();
	window->close();
}

//---------------------------------------------------------------------

std::weak_ptr<sf::RenderWindow> Game::getRenderWindow()
{
	return window;
}

//---------------------------------------------------------------------

void Game::addScore(int score)
{
	this->score += score;
}

//---------------------------------------------------------------------

void Game::subScore(int score)
{
	this->score -= score;
}

//---------------------------------------------------------------------

void Game::drawUI()
{
	score_text.setString("Score: " + to_string(score));
	window->draw(score_text);
}

//---------------------------------------------------------------------

void Game::showScoreboard()
{
	scoreboard->setScore(score);
	scoreboard->showScoreboard();
}

//---------------------------------------------------------------------

void Game::init()
{
	//Dostosowanie parametrow UI (wynik wyswietlany w trakcie gry)
	font.loadFromFile("Rubik.ttf");
	score_text.setPosition({ SCORE_POS_WIDTH, SCORE_POS_HEIGHT });
	score_text.setFont(font);
	score_text.setCharacterSize(FONT_SIZE);

	//zaladowanie tekstur
	cactusTexture.loadFromFile("graphics/cact.png");
	flyingDinosaurTexture.loadFromFile("graphics/flyingdinosaur.png");
	coinTexture.loadFromFile("graphics/coin.png");
	backgroundTexture.loadFromFile("graphics/background.png");
	background.setSize({ float(WINDOW_WIDTH),float(WINDOW_HEIGHT) });
	background.setTexture(&backgroundTexture);
	background.setTextureRect(sf::IntRect(0, 0, backgroundTexture.getSize().x, backgroundTexture.getSize().y));
	sf::Texture playerTexture;
	playerTexture.loadFromFile("graphics/player.png");

	//stworzenie generatora liczb losowych
	random_engine.seed(unsigned int(std::chrono::system_clock::now().time_since_epoch().count()));
	
	//stworzenie gracza
	Vector2f position = { PLAYER_START_POS_X,PLAYER_START_POS_Y };
	Vector2f size = { PLAYER_WIDTH, PLAYER_HEIGHT };
	player = std::make_shared<Player>(position, size, playerTexture, this, true);
	objects.push_back(player);
}

//---------------------------------------------------------------------

void Game::startGame()
{
	int choosedButton = menu->showMenu();
	if (choosedButton == 0)
	{
		init();
		menu->showMenu();
		startGameLoop();
		showScoreboard();
	}
}

//---------------------------------------------------------------------

void Game::startGameLoop()
{
	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Clock playerJumpClock;
	sf::Event event;
	while (window->isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		while (window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				window->close();

		//obsluga skakania,punktow za czas gry, oraz tworzenie przeszkod
 		handlePlayerJump(playerJumpClock);
		handlePointsForTime(deltaTime);
		handleObjectSpawning(deltaTime);

		//Updateowanie obiektow. Poruszanie itp.
		std::for_each(objects.begin(), objects.end(), [&](std::shared_ptr<GraphicObjectWithCollision>& obj)
			{
				if (obj != NULL)
					obj->Update(deltaTime);
			}
		);

		//Sprawdzanie kolizji obiektow oraz wywo³ywanie reakcji na kolizje
		std::for_each(objects.begin(), objects.end(), [&](std::shared_ptr<GraphicObjectWithCollision>& obj)
			{
				if (obj != NULL)
					obj->isColliding(player);
			}
		);

		//Rysowanie obiektow, tla oraz UI
		window->clear();
		window->draw(background);
		std::for_each(objects.begin(), objects.end(), [](std::shared_ptr<GraphicObjectWithCollision>& obj)
			{
				obj->draw();
			}
		);
		drawUI();
		window->display();

		//Sprawdzanie warunku konca gry
		if (!player->isAlive())
			break;
			
	}
}

//---------------------------------------------------------------------

void Game::handlePlayerJump(sf::Clock& playerJumpClock)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (playerJumpClock.getElapsedTime().asSeconds() >= JUMP_DELAY && player->isJumping() == false)
		{
			player->setJumpingStatus(true);
			playerJumpClock.restart();
			player->setVelocity(V_START);
		}
	}
}

//---------------------------------------------------------------------

void Game::handlePointsForTime(float deltaTime)
{
	totalTimePointsForTime += deltaTime;
	if (totalTimePointsForTime >= GAME_POINTS_SWITCH_TIME)
	{
		totalTimePointsForTime = 0;
		score += GAME_POINTS_PER_TIME_UNIT;
	}
}

//---------------------------------------------------------------------

void Game::handleObjectSpawning(float deltaTime)
{
	std::uniform_real_distribution<float> random_number(0.0,1.0);
	totalTimeSpawningFlyingDinosaur += deltaTime;
	totalTimeSpawningCactus += deltaTime;
	totalTimeSpawningCoin += deltaTime;
	if (totalTimeSpawningFlyingDinosaur >= SPAWNING_TIME_FLYING_DINOSAUR + random_number(random_engine))
	{
		totalTimeSpawningFlyingDinosaur = 0;
		objects.push_back(std::make_shared<FlyingDinosaur>(this, flyingDinosaurTexture));
	}
	if (totalTimeSpawningCactus >= SPAWNING_TIME_CACTUS + random_number(random_engine))
	{
		totalTimeSpawningCactus = 0;
		if(random_number(random_engine) > 0.5)
			objects.push_back(std::make_shared<Cactus>(this, cactusTexture, Cactus::cactusType::small));
		else
			objects.push_back(std::make_shared<Cactus>(this, cactusTexture, Cactus::cactusType::big));
	}
	if (totalTimeSpawningCoin >= SPAWNING_TIME_COIN + random_number(random_engine))
	{
		totalTimeSpawningCoin = 0;
		objects.push_back(std::make_shared<Coin>(this, coinTexture, 50));
	}
}

//---------------------------------------------------------------------

void Game::removeObject(GraphicObjectWithCollision* objectToRemove)
{
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		if (&(*((*it).get())) == &(*objectToRemove))
		{
			objects.erase(it);
			return;
		}
	}
}

//---------------------------------------------------------------------