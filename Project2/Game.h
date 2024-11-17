#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <random>


class Game
{
private:
	//window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	sf::Vector2i mousePos;

	//logic
	float gameTimer;
	float gameTimerMax;
	int score;
	int diffPos;
	int current;
	int highScore;
	bool mainMenu;

	//game obj
	std::vector<sf::RectangleShape> squares;
	std::vector<sf::Color> colors;
	sf::RectangleShape button;
	sf::Text startText;
	sf::Text retryText;
	sf::Font font1;
	sf::Font font2;
	sf::Text scoreboard;
	sf::Text scoreDisplay;
	sf::Text timer;
	sf::Text title;
	sf::Text textHighScore;

	//private function
	void initWindow();
	void initVariables();
	void initColors();
	void initText();
	void initStartButton();
	void currentColor();
	void initSquares();
	void initDiffSquare();
public:
	//	constructor/destructor
	Game();
	virtual ~Game();

	//accessors
	const bool running() const;


	//	Functions
	void pollGameEvents();
	void pollMainMenuEvents();
	void pollEndScreenEvents();
	void updateGame();
	void render();
};

