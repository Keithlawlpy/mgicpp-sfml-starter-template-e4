
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Animals.h"
#include "Passport.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();

  bool init();
  void update(float dt);
  void render();
  void mousePressed(sf::Event event);
  void mouseReleased(sf::Event event);
  void keyPressed(sf::Event event);
  void newAnimal();
  void dragSprite(sf::Sprite* sprite);

 private:
  sf::RenderWindow& window;

  //main screen
  sf::Font font;
  sf::Text menu_text;

  //game screen
  sf::Text Score_text;
  int Score = 0;

  // game objects

  std::vector<Animal> animals;
  std::vector<Passport> passports;

  std::unique_ptr<Animal> currentAnimal;
  std::unique_ptr<Passport> currentPassport;

  std::vector<std::string> animalNames = { "elephant", "moose", "penguin" };

  //buttons
  GameObject accept_button;
  GameObject reject_button;


  //stamps
  GameObject accepted_stamp;
  GameObject rejected_stamp;

  //background
  sf::Sprite background;
  sf::Texture background_texture;

  //vaildation
  bool passport_accepted = true;
  bool passport_rejected = true;
  bool should_accept = true;

  //dragging
  sf::Sprite* dragged = nullptr;
  sf::Vector2f drag_offset;
  bool mouse_dragging = false;


  //game state

  enum class GameState
  {
	MENUSCREEN,
	PLAYING,
	END
  };

  GameState current_state = GameState::MENUSCREEN;

};

#endif // PLATFORMER_GAME_H
