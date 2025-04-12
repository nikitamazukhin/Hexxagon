#include "PawnSprite.hpp"

PawnSprite::PawnSprite() = default;

PawnSprite::PawnSprite(const float radius) : sprite(radius, 3) {
    sprite.setOrigin( { sprite.getRadius(), sprite.getRadius() });
    sprite.setRotation(180);
}

PawnSprite::PawnSprite(const float radius, const sf::Texture *texture) : sprite(radius, 3) {
    sprite.setOrigin( { sprite.getRadius(), sprite.getRadius() });
    sprite.setRotation(180);
    sprite.setTexture(texture);
}

auto PawnSprite::setTexture(const sf::Texture *texture) -> void {
    sprite.setTexture(texture);
}

auto PawnSprite::getRadius() const -> float {
    return sprite.getRadius();
}

auto PawnSprite::getOrigin() const -> sf::Vector2f {
    return sprite.getOrigin();
}

auto PawnSprite::setPosition(const sf::Vector2f pos) -> void {
    sprite.setPosition(pos);
}

auto PawnSprite::setPosition(const sf::RenderWindow &window, int x, int y) -> void {
    auto windowDim = window.getSize();

    auto xCoord = x * 70;
    auto yCoord = y * 70;

    auto pixToAddX = windowDim.x/2 - 4*70;
    auto pixToAdDY = windowDim.y/2 - 4*70;

    setPosition( { static_cast<float>(xCoord + pixToAddX), static_cast<float>(yCoord - xCoord/2 + pixToAdDY) });
}

auto PawnSprite::getDrawn(sf::RenderWindow &window) const -> void {
    window.draw(sprite);
}