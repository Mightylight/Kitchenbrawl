#include "button.hpp"

#include <SFML/Window/Event.hpp>

Button::Button(std::string identifier, sf::Font& font, std::string buttonText, sf::Vector2f size) :
    GameObject(identifier), font(font), buttonText(buttonText)
{
    this->shape.setSize(size);
    //this->shape.setFillColor(color);
    this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setOutlineThickness(1);

    this->text.setFont(font);
    this->text.setString(buttonText);
    this->text.setCharacterSize(26);
    this->text.setFillColor(sf::Color::White);

    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);

    this->setPosition(sf::Vector2f(0.0f, 0.0f));
}

Button::~Button() { }

void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if(event.type == sf::Event::MouseButtonPressed  && 
        event.mouseButton.button == sf::Mouse::Button::Left) {

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f size = shape.getSize();
        sf::Vector2f position = shape.getPosition();

        if(isHovering(window)) {
                this->onClick();
        }
    }
}

void Button::update() { }

void Button::render(sf::RenderWindow& window) {
    if(isHovering(window)){
        shape.setFillColor(sf::Color(132, 146, 166, 255));
    } else {
        shape.setFillColor(sf::Color(71, 82, 94, 255));
    }
    window.draw(this->shape);
    window.draw(this->text);
}

void Button::setCharacterSize(const int size) {
    this->text.setCharacterSize(size);
}

void Button::setPosition(const sf::Vector2f position) {
    this->shape.setPosition(position);
    sf::Vector2f size = this->shape.getSize();
    sf::Vector2f centerButton(position.x + (size.x / 2.0f), position.y + (size.y / 2.0f));
    this->text.setPosition(centerButton);
}

void Button::onClick() {
    this->action();
}

void Button::setButtonAction(std::function<void()> action) {
        this->action = action;
}

void Button::setText(const std::string string) {
    this->text.setString(string);
    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
}

bool Button::isHovering(const sf::RenderWindow& window) {
    return shape.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window));
}
