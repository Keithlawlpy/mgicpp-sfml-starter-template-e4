
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
	delete[] animals;
	delete[] passports;
	delete character;
	delete passport;
}

bool Game::init()
{
	character = new sf::Sprite();
	passport = new sf::Sprite();

	/*for (int i = 0; i < 3; i++)
	{
		if (!animals[i].loadFromFile("res/animal" + std::to_string(i) + ".png"))
		{
			std::cout << "Failed to load animal texture" << std::endl;
			return false;
		}
		if (!passports[i].loadFromFile("res/passport" + std::to_string(i) + ".png"))
		{
			std::cout << "Failed to load passport texture" << std::endl;
			return false;
		}
	}
	*/

	//background
	if (!background_texture.loadFromFile("../Data/WhackaMole_Worksheet/background.png"))
	{
		std::cout << "background texture did not load \n";
	}
	background.setTexture(background_texture);


    return true;
}

void Game::update(float dt)
{

}

void Game::render()
{
	window.draw(background);

}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{

}


