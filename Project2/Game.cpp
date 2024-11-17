#include "Game.h"

std::vector<sf::RectangleShape> static createSquares(int numRows, int numCols, float squareSize) {
    std::vector<sf::RectangleShape> squares;
    sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            square.setPosition((squareSize + 10) * (i + 1), (squareSize + 10) * (j + 1));
            squares.push_back(square);
        }
    }

    return squares;
}

sf::Color static randColor(const sf::Color& baseColor) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(5, 15);

    return sf::Color(
        baseColor.r + distrib(gen),
        baseColor.g + distrib(gen),
        baseColor.b + distrib(gen)
    );
}

//private functions
void Game::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Tugas Akhir");
    this->window->setFramerateLimit(60);
}

void Game::initVariables()
{
	this->window = nullptr;
    this->gameTimerMax = 3600.f;
    this->gameTimer = this->gameTimerMax;
    this->score = 0;
    this->diffPos = 0;
    this->current = 0;
    this->highScore = 0;
    this->mainMenu = true;
}

void Game::initColors()
{
    this->colors = 
    {sf::Color(205, 110, 50),
     sf::Color(31, 30, 51),
     sf::Color(75, 75, 200),
     sf::Color(50, 50, 150),
     sf::Color(25, 25, 100),
     sf::Color(175, 20, 20),
     sf::Color(25, 85, 35),
     sf::Color(30, 15, 85),
     sf::Color(50, 150, 90)};
}

void Game::initText()
{
    this->font1.loadFromFile("American Captain.otf");
    this->font2.loadFromFile("Gameplay.ttf");
    //score
    this->scoreboard.setFont(font1);
    this->scoreboard.setCharacterSize(24);
    this->scoreboard.setFillColor(sf::Color::Black);
    this->scoreboard.setPosition(100, 40);
    //timer
    this->timer.setFont(font1);
    this->timer.setCharacterSize(24);
    this->timer.setFillColor(sf::Color::Black);
    this->timer.setPosition(100, 70);
    //title
    this->title.setFont(font2);
    this->title.setCharacterSize(100);
    this->title.setFillColor(sf::Color::Black);
    this->title.setPosition(250,100);
    this->title.setString("title");
    //high score
    this->textHighScore.setFont(font2);
    this->textHighScore.setCharacterSize(30);
    this->textHighScore.setFillColor(sf::Color::Black);
    this->textHighScore.setPosition(0, 0);
    //end score
    this->scoreDisplay.setFont(font2);
    this->scoreDisplay.setCharacterSize(30);
    this->scoreDisplay.setFillColor(sf::Color::Black);
    this->scoreDisplay.setPosition(0, 30);
    //start
    this->startText.setCharacterSize(48);
    this->startText.setFont(font2);
    this->startText.setFillColor(sf::Color::Black);
    this->startText.setString("Start");
    this->startText.setPosition(312, 390);
    //retry
    this->retryText.setCharacterSize(48);
    this->retryText.setFont(font2);
    this->retryText.setFillColor(sf::Color::Black);
    this->retryText.setString("retry");
    this->retryText.setPosition(312, 390);

}

void Game::initStartButton()
{
    this->button.setFillColor(sf::Color(86, 132, 191));
    this->button.setOutlineColor(sf::Color::Black);
    this->button.setOutlineThickness(2.f);
    this->button.setSize(sf::Vector2f(200.f,80.f));    
}


void Game::currentColor()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, this->colors.size() - 1);
    this->current = distrib(gen);
    for (auto& square : this->squares) {
        square.setFillColor(this->colors[this->current]);
    }
}

void Game::initSquares()
{
    this->squares = createSquares(6, 6, 90);
}

void Game::initDiffSquare()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randPos(0, this->squares.size() - 1);
    this->diffPos = randPos(gen);
    this->squares[diffPos].setFillColor(randColor(this->colors[this->current]));
}

//constructor/destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initSquares();
    this->initText();
    this->initStartButton();
    this->initColors();
    this->currentColor();
    this->initDiffSquare();

}

Game::~Game()
{
	delete this->window;
}

//accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollGameEvents()
{
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape) {
                this->window->close();
            }break;
        case sf::Event::MouseButtonPressed:
            if (this->ev.mouseButton.button == sf::Mouse::Left) {
                if (this->squares[this->diffPos].getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePos))) {
                    this->currentColor();
                    this->initDiffSquare();
                    this->score++;
                }
            }break;
        }
    }
}

void Game::pollMainMenuEvents()
{
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape) {
                this->window->close();
            }break;
        case sf::Event::MouseButtonPressed:
            if (this->ev.mouseButton.button == sf::Mouse::Left) {
                if (this->button.getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePos))) {
                    this->gameTimer = 0;
                    this->mainMenu = false;
                }
            }break;
        }
        
    }
}

void Game::pollEndScreenEvents()
{
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape) {
                this->mainMenu = true;
                this->score = 0;
            }break;
        case sf::Event::MouseButtonPressed:
            if (this->ev.mouseButton.button==sf::Mouse::Left) {
                if (this->button.getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePos))) {
                    this->gameTimer = 0;
                    this->score = 0;
                }
            }

        }
    }
}


//Functions
void Game::updateGame()
{
    this->mousePos = sf::Mouse::getPosition(*this->window);
    if (this->gameTimer == this->gameTimerMax) {
        if (this->mainMenu == true) {
            //update main manu
            this->button.setPosition(300, 380);
            this->pollMainMenuEvents();
        }else {
            //update endscreen
            if (this->score > this->highScore) {
                this->highScore = this->score;
            }
            this->button.setPosition(300, 380);
            this->textHighScore.setString("high score : " + std::to_string(this->highScore));
            this->scoreDisplay.setString("score : " + std::to_string(this->score));
            this->pollEndScreenEvents();
        }
    }else {
        //update game
        this->pollGameEvents();
        this->scoreboard.setString(std::to_string(score));
        this->timer.setString(std::to_string((gameTimerMax - gameTimer) / 60));
        this->gameTimer++;
    }
    
}

void Game::render()
{
    /*
        @return void

        -clear old frame
        -rendedr obj
        -display new frame
    */

    
    if (this->gameTimer == this->gameTimerMax) {
        if (this->mainMenu == true) {
            //load main menu
            this->window->clear(sf::Color(220, 220, 220));
            this->window->draw(this->title);
            this->window->draw(this->button);
            this->window->draw(this->startText);
            this->window->display();
        }else {
            //load end screen
            this->window->clear(sf::Color(220, 220, 220));
            this->window->draw(this->textHighScore);
            this->window->draw(this->scoreDisplay);
            this->window->draw(this->button);
            this->window->draw(this->retryText);
            this->window->display();
        }
    }else {
        //load game
        this->window->clear(sf::Color(220, 220, 220));
        this->window->draw(this->timer);
        this->window->draw(this->scoreboard);
        for (const auto& square : squares) {
            this->window->draw(square);
        }

        this->window->display();
    }
}
