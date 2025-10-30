
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{

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

	//animal initialization

	for (const auto& name : animalNames)
	{
		Animal animal;
		animal.initialiseSprite(*new sf::Texture, "../Data/Critter_Crossing_Customs/" + name + ".png");
		animals.push_back(animal);

		Passport passport;
		passport.initialiseSprite(*new sf::Texture, "../Data/Critter_Crossing_Customs/" + name + "_passport.png");
		passports.push_back(passport);
	}
	//button

	if (!accept_texture.loadFromFile("../Data/Critter_Crossing_Customs/accept_button.png"))
	{
		std::cout << "accept texture did not load";
	}
	accept_button.setTexture(accept_texture);
	accepted_stamp.getSprite()->setScale(0.5, 0.5);
	accept_button.setPosition(window.getSize().x / 12, (window.getSize().y / 2) + 25);

	if (!reject_texture.loadFromFile("../Data/Critter_Crossing_Customs/reject_button.png"))
	{
		std::cout << "reject texture did not load";
	}
	reject_button.setTexture(reject_texture);
	rejected_stamp.getSprite()->setScale(0.5, 0.5);
	reject_button.setPosition(window.getSize().x / 12, (window.getSize().y / 2) + 150);

	//stamps

	accepted_stamp.initialiseSprite(*new sf::Texture, "../Data/Critter_Crossing_Customs/accept.png");
	rejected_stamp.initialiseSprite(*new sf::Texture, "../Data/Critter_Crossing_Customs/reject.png");

	accepted_stamp.getSprite()->setScale(1, 1);
	rejected_stamp.getSprite()->setScale(1, 1);

	//score text
	Score_text.setFont(font);
	Score_text.setCharacterSize(50);
	Score_text.setPosition(10,20);
	Score_text.setString("Score: " + std::to_string(Score));


	newAnimal();
    return true;
}

void Game::update(float dt)
{
	sf::Vector2f stamp_offset = {20, 40};
	dragSprite(dragged);


	//check for passport validation
	if (accept_button.getGlobalBounds().intersects(currentPassport->getSprite()->getGlobalBounds()) && mouse_dragging)
	{
		std::cout << "accept stamped \n";
		passport_accepted = true;
		passport_rejected = false;
	}
	if (reject_button.getGlobalBounds().intersects(currentPassport->getSprite()->getGlobalBounds()) && mouse_dragging)
	{
		std::cout << "reject stamped \n";
		passport_rejected = true;
		passport_accepted = false;
	}

	//position stamps
	if (passport_accepted)
	{
		accepted_stamp.getSprite()->setPosition(currentPassport->getSprite()->getPosition() + stamp_offset);
	}
	else if (passport_rejected)
	{
		rejected_stamp.getSprite()->setPosition(currentPassport->getSprite()->getPosition() + stamp_offset);
	}

	if(currentPassport->getSprite()->getGlobalBounds().intersects(currentAnimal->getSprite()->getGlobalBounds()))
	{
		if (passport_accepted && should_accept)
		{
			std::cout << "Correctly accepted\n";
			++Score;
			newAnimal();
		}
		else if (passport_rejected && !should_accept)
		{
			std::cout << "Correctly rejected\n";
			++Score;
			newAnimal();
		}
		else if (passport_accepted && !should_accept)
		{
			std::cout << "Wrongly accepted\n";
			--Score;
			newAnimal();
		}
		else if (passport_rejected && should_accept)
		{
			std::cout << "Wrongly rejected\n";
			--Score;
			newAnimal();	
		}
		else
		{
			std::cout << "No decision made\n";
		}

	}
	
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
			window.draw(*currentAnimal->getSprite());
			window.draw(*currentPassport->getSprite());
			window.draw(Score_text);
			
			if (passport_accepted)
			{
				window.draw(*accepted_stamp.getSprite());
			}
			else if (passport_rejected)
			{
				window.draw(*rejected_stamp.getSprite());
			}

			window.draw(accept_button);
			window.draw(reject_button);

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
		
		if (currentPassport->getSprite()->getGlobalBounds().contains(mouse_positionf))
		{
			dragged = currentPassport->getSprite();	
			drag_offset = mouse_positionf - dragged->getPosition();
			mouse_dragging = false;

		}
		if (accept_button.getGlobalBounds().contains(mouse_positionf))
		{
			dragged = &accept_button;
			drag_offset = mouse_positionf - dragged->getPosition();
			mouse_dragging = true;
		}
		if (reject_button.getGlobalBounds().contains(mouse_positionf))
		{
			dragged = &reject_button;
			drag_offset = mouse_positionf - dragged->getPosition();
			mouse_dragging = true;
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
	if(event.key.code == sf::Keyboard::R)
	{
		newAnimal();
	}
}

void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % animals.size();
	int passport_index = rand() % passports.size();

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}

	currentAnimal = std::make_unique<Animal>(animals[animal_index]);
	currentPassport = std::make_unique<Passport>(passports[passport_index]);

	currentAnimal->getSprite()->setScale(1.8f, 1.8f);
	currentAnimal->getSprite()->setPosition(window.getSize().x / 12, window.getSize().y / 12);

	currentPassport->getSprite()->setScale(0.6f, 0.6f);
	currentPassport->getSprite()->setPosition(window.getSize().x / 2 + 100, window.getSize().y / 3);

	//reset buttons position
	accept_button.setPosition(window.getSize().x / 12, (window.getSize().y / 2) + 25);
	reject_button.setPosition(window.getSize().x / 12, (window.getSize().y / 2) + 150);

	Score_text.setString("Score: " + std::to_string(Score));


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