
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void newAnimal();

 private:
  sf::RenderWindow& window;

  //chara
  sf::Sprite* character;
  sf::Sprite* passport;
  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];

  //background
  sf::Sprite background;
  sf::Texture background_texture;

  //vaildation
  bool passport_accepted = true;
  bool passport_rejected = true;
  bool should_accept = true;


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
