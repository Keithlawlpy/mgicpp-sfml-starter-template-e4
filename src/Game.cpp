
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

	//background
	if (!background_texture.loadFromFile("../Data/WhackaMole_Worksheet/background.png"))
	{
		std::cout << "background texture did not load \n";
	}
	background.setTexture(background_texture);

	//animal arrays
	if (!animals[0].loadFromFile("../Data/Critter_Crossing_Customs/eleplant.png"))
	{
		std::cout << "eleplant texture did not load \n";
	}
	if (!animals[1].loadFromFile("../Data/Critter_Crossing_Customs/moose.png"))
	{
		std::cout << "moose texture did not load \n";
	}
	if (!animals[2].loadFromFile("../Data/Critter_Crossing_Customs/penguin.png"))
	{
		std::cout << "penguin texture did not load \n";
	}

	if (!passports[0].loadFromFile("../Data/Critter_Crossing_Customs/elephant_passport.png"))
	{
		std::cout << "eleplant passport texture did not load \n";
	}
	if (!passports[1].loadFromFile("../Data/Critter_Crossing_Customs/moose_passport.png"))
	{
		std::cout << "moose passport texture did not load \n";
	}
	if (!passports[2].loadFromFile("../Data/Critter_Crossing_Customs/penguin_passport.png"))
	{
		std::cout << "penguin passport texture did not load \n";
	}

	newAnimal();



    return true;
}

void Game::update(float dt)
{


}

void Game::render()
{

	switch(current_state)
	{
		case GameState::MENUSCREEN:
			//draw menu screen
			break;
		case GameState::PLAYING:

			window.draw(background);
			window.draw(*character);
			window.draw(*passport);
			
			if (passport_accepted)
			{
				//draw accepted stamp
			}
			else if (passport_rejected)
			{
				//draw rejected stamp
			}


			break;

		case GameState::END:
			//draw end screen
			break;

		default:
			break;
	}


}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
	if(event.key.code == sf::Keyboard::Space)
	{
		if (current_state == GameState::MENUSCREEN)
		{
			current_state = GameState::PLAYING;
		}
		else if (current_state == GameState::PLAYING)
		{
			current_state = GameState::END;
		}
		else if (current_state == GameState::END)
		{
			current_state = GameState::MENUSCREEN;
		}
	}
}

void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}

	character->setTexture(animals[animal_index], true);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);

	passport->setTexture(passports[passport_index]);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 2);
}
