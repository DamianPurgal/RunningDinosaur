#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include <random>
#include <chrono>
#include <thread>
#include "GraphicObjectWithCollision.h"
#include "constant.h"
#include "Player.h"
#include "Cactus.h"
#include "FlyingDinosaur.h"
#include "Coin.h"
#include "Menu.h"
#include "Scoreboard.h"
using namespace std;
class Game
{
private:
	vector<std::shared_ptr<GraphicObjectWithCollision>> objects;
	int score;
	std::shared_ptr<Player> player;
	sf::Font font;
	sf::Text score_text;
	float Vx;
	float totalTimePointsForTime;
	float totalTimeSpawningFlyingDinosaur;
	float totalTimeSpawningCactus;
	float totalTimeSpawningCoin;
	std::shared_ptr<sf::RenderWindow> window;
	sf::Texture backgroundTexture;
	sf::Texture cactusTexture;
	sf::Texture flyingDinosaurTexture;
	sf::Texture coinTexture;
	sf::RectangleShape background;
	std::default_random_engine random_engine;
	std::unique_ptr<Menu> menu;
	std::unique_ptr<Scoreboard> scoreboard;
private:
	void showScoreboard();
	void init();
	void drawUI();
	void startGameLoop();
	void handlePlayerJump(sf::Clock& playerJumpClock);
	void handlePointsForTime(float deltaTime);
	void handleObjectSpawning(float deltaTime);
public:
	Game();
	~Game();
	std::weak_ptr<sf::RenderWindow> getRenderWindow();
	void addScore(int score);
	void subScore(int score);
	void startGame();
	void removeObject(GraphicObjectWithCollision* objectToRemove);

};