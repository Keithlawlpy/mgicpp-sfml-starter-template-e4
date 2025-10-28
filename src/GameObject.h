#ifndef PLATFORMER_GAMEOBJECT_H
#define PLATFORMER_GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject
{
	public:
		GameObject();
		~GameObject();


		bool initialiseSprite(sf::Texture& texture, std::string  filename);
		sf::Sprite* getSprite();

		bool initialiseText(sf::Font& font, std::string  filename);
		sf::Text* getText();

	private:
		sf::Sprite* sprite = nullptr;
		sf::Text* Text = nullptr;
};



#endif