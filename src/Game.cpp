
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

	//main screen

	// menu text
	if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "font did not load \n";
	}
	menu_text.setString("Press enter to \n start the game \n press Q to quit in game");
	menu_text.setFont(font);
	menu_text.setCharacterSize(70);
	menu_text.setPosition((window.getSize().x - menu_text.getGlobalBounds().width) / 2, (window.getSize().y - menu_text.getGlobalBounds().height) / 10);
	menu_text.setFillColor(sf::Color(253, 184, 39, 128));

	//background
	if (!background_texture.loadFromFile("../Data/WhackaMole_Worksheet/background.png"))
	{
		std::cout << "background texture did not load \n";
	}
	background.setTexture(background_texture);

	//animal arrays
	std::string animalNames[3] = { "elephant", "moose", "penguin" };

	for (int i = 0; i < 3; i++)
	{
		// Load animal texture
		if (!animals[i].loadFromFile("../Data/Critter_Crossing_Customs/" + animalNames[i] + ".png"))
		{
			std::cout << animalNames[i] << " texture did not load \n";
		}

		// Load passport texture
		if (!passports[i].loadFromFile("../Data/Critter_Crossing_Customs/" + animalNames[i] + "_passport.png"))
		{
			std::cout << animalNames[i] << " passport texture did not load \n";
		}
	}

	//button

	if (!accept_texture.loadFromFile("../Data/Critter_Crossing_Customs/accept_button.png"))
	{
		std::cout << "accept texture did not load";
	}
	accept_button.setTexture(accept_texture);
	accept_button.setPosition(window.getSize().x / 12, (window.getSize().y / 2) + 25);

	if (!reject_texture.loadFromFile("../Data/Critter_Crossing_Customs/reject_button.png"))
	{
		std::cout << "reject texture did not load";
	}
	reject_button.setTexture(reject_texture);
	reject_button.setPosition(window.getSize().x / 12, (window.getSize().y / 2) + 150);



	newAnimal();



    return true;
}

void Game::update(float dt)
{
	dragSprite(dragged);
	
}

void Game::render()
{

	switch(current_state)
	{
		case GameState::MENUSCREEN:
			window.draw(menu_text);

			break;
		case GameState::PLAYING:

			window.draw(background);
			window.draw(*character);
			window.draw(*passport);
			window.draw(accept_button);
			window.draw(reject_button);
			
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

void Game::mousePressed(sf::Event event)
{
	//click position
	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);
		
		if (passport->getGlobalBounds().contains(mouse_positionf))
		{
			dragged = passport;
			drag_offset = mouse_positionf - dragged->getPosition();
		}

	}


}

void Game::mouseReleased(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			dragged = nullptr;
		}
	}
}

void Game::keyPressed(sf::Event event)
{
	if(event.key.code == sf::Keyboard::Enter)
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
	if(event.key.code == sf::Keyboard::Q)
	{
		if (current_state == GameState::PLAYING)
		{
			window.close();
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
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);
}

void Game::dragSprite(sf::Sprite* sprite)
{
	if (sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		sf::Vector2f drag_position = mouse_positionf - drag_offset;
		sprite->setPosition(drag_position.x, drag_position.y);
	}
}