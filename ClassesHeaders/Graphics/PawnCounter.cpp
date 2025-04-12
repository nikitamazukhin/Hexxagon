#include "PawnCounter.hpp"

PawnCounter::PawnCounter(int n, unsigned int charSize, const sf::Font &font,
                         const sf::Color &textColor, bool leftAligned, float radius, const sf::Texture &texture) :
                         sprite(radius, &texture), leftAligned(leftAligned) {

    counter.setString(std::to_string(n));
    counter.setFont(font);
    counter.setCharacterSize(charSize);
    counter.setFillColor(textColor);
}

auto PawnCounter::setPosition(sf::Vector2f pos) -> void {
    sprite.setPosition(pos);

    float xPos;

    if (leftAligned)
        xPos = pos.x - sprite.getRadius() * 2.5f;
    else
        xPos = pos.x + sprite.getRadius() * 1.5f;

    float yPos = pos.y - counter.getLocalBounds().height/1.5f;

    counter.setPosition(xPos, yPos);
}

auto PawnCounter::update(int n) -> void {
    counter.setString(std::to_string(n));
}

auto PawnCounter::getDrawn(sf::RenderWindow &window) const -> void {
    window.draw(counter);
    sprite.getDrawn(window);
}