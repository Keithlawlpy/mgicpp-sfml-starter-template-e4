#ifndef PLATFORMER_ANIMAL_H
#define PLATFORMER_ANIMAL_H

#include <SFML/Graphics.hpp>
#include <string>

class Animals
{

public:
    Animal(const std::string& texturePath);
    sf::Sprite& getSprite();
    void setPosition(float x, float y);
    void setScale(float x, float y);

private:
    sf::Texture texture;
    sf::Sprite sprite;

};

#endif  // PLATFORMER_ANIMAL_H