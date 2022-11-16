#include "quitButton.hpp"

QuitButton::QuitButton(std::string identifier, sf::Font& font, std::string buttonText, 
        sf::Vector2f size, sf::RenderWindow& window) :
        Button(identifier, font, buttonText, size), window(window) { }

QuitButton::~QuitButton() { }

void QuitButton::onClick() {
    this->window.close();
}


