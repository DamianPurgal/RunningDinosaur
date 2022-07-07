#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include "Button.h"
#include "GraphicObject.h"
#include "constant.h"
class Scoreboard : public GraphicObject
{
private:
	std::vector<std::unique_ptr<Button>> buttons;
	std::shared_ptr<RenderWindow> window;
	sf::Text textHighestScore;
	sf::Text textGamesPlayed;
	sf::Text textActualScore;
	sf::Font font;
	sf::Texture buttonTexture;
	int highestScore;
	int gamesPlayed;
	int actualScore;
	void getDataFromFile();
	void saveDataToFile();
	void Update(float deltaTime) {};
	void draw();
	void init();
	int startLoop();
public:
	void setScore(int score);
	Scoreboard(sf::Texture backgroundTexture, sf::Texture pButtonTexture);
	~Scoreboard();
	int showScoreboard(); 
};

