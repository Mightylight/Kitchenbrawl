#include "textObject.hpp"

TextObject::TextObject(std::string identifier, sf::Font& font, std::string textStr) : GameObject(identifier), font(font), textStr(textStr) {
    this->text.setString(this->textStr);
    this->text.setFont(this->font);
    this->text.setCharacterSize(12);
    this->text.setFillColor(sf::Color::White);

    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    this->text.setPosition(this->position);
}

TextObject::~TextObject() { }

void TextObject::update() { }

void TextObject::render(sf::RenderWindow& window) {
    window.draw(this->text);
}

std::string TextObject::getTextStr() const {
    return this->textStr;
}

void TextObject::setText(const std::string textStr) {
    this->textStr = textStr;
    this->text.setString(this->textStr);
}

void TextObject::setCharacterSize(const int size) {
    this->text.setCharacterSize(size);
}

void TextObject::setFillColor(const sf::Color color) {
    this->text.setFillColor(color);
}

void TextObject::setPosition(const sf::Vector2f position) {
    this->text.setPosition(position);
}
