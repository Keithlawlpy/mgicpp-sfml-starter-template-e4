
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

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
  sf::Text Score;

  //chara
  sf::Sprite* character;
  sf::Sprite* passport;
  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];

  //buttons
  sf::Sprite accept_button;
  sf::Texture accept_texture;
  sf::Sprite reject_button;
  sf::Texture reject_texture;

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
