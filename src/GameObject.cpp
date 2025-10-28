#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
    sprite = new sf::Sprite();
    Text = new sf::Text();
}

GameObject::~GameObject()
{

}


bool GameObject::initialiseSprite(sf::Texture& texture, std::string  filename)
{
    if (!texture.loadFromFile(filename))
    {
        std::cout << "couldn't load file: " << filename << "\n";
    }
    sprite->setTexture(texture);
    return true;
}

bool GameObject::initialiseText(sf::Font& font, std::string  filename)
{
    if (!font.loadFromFile(filename))
    {
        std::cout << "couldn't load file: " << filename << "\n";
    }
    Text->setFont(font);
    return true;
}



sf::Sprite* GameObject::getSprite()
{
    return sprite;
}

sf::Text* GameObject::getText()
{
    return Text;
}