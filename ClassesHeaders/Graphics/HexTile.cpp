#include "HexTile.hpp"

HexTile::HexTile() : button(0, 0), isActive(false), highlighted(false) {

}

HexTile::HexTile(float radius, const sf::Color &bg, bool activity) : isActive(activity), highlighted(false), button(radius, 6) {
    button.setOrigin({ button.getRadius(), button.getRadius() });
    button.rotate(30);
    button.setFillColor(bg);
}

auto HexTile::setBorder(const sf::Color &color, float thickness) -> void {
    button.setOutlineColor(color);
    button.setOutlineThickness(thickness);
}

auto HexTile::setDefaultLook() -> void {
    button = sf::CircleShape(30, 6);
    button.setOrigin({ 30, 30 });
    button.rotate(30);
    button.setFillColor(sf::Color::Magenta);
    isActive = false;
}

auto HexTile::removeBorder() -> void {
    button.setOutlineColor(sf::Color::Transparent);
    button.setOutlineThickness(0);

    if (highlighted)
        setBorder(sf::Color::Green, 5);
}

auto HexTile::getPosition() const -> sf::Vector2f {
    return button.getPosition();
}

auto HexTile::setPosition(sf::RenderWindow &window, int x, int y) -> void {
    auto windowDim = window.getSize();

    auto xCoord = x * 70;
    auto yCoord = y * 70;

    auto pixToAddX = windowDim.x/2 - 4*70;
    auto pixToAdDY = windowDim.y/2 - 4*70;

    button.setPosition( { static_cast<float>(xCoord + pixToAddX), static_cast<float>(yCoord - xCoord/2 + pixToAdDY) });
}

auto HexTile::getSize() const -> sf::FloatRect {
    return button.getLocalBounds();
}

auto HexTile::isMousedOver(sf::RenderWindow &window) const -> bool {
    if(isActive) {
        auto mousePos = sf::Mouse::getPosition(window);
        auto mouseX = mousePos.x;
        auto mouseY = mousePos.y;

        auto hexOrigin = button.getPosition();
        auto hexXCenter = hexOrigin.x;
        auto hexYCenter = hexOrigin.y;

        return (std::pow((static_cast<float>(mouseX) - hexXCenter), 2) + std::pow((static_cast<float>(mouseY) - hexYCenter), 2) < std::pow(button.getRadius() - 5, 2));
    }
    else
        return false;
}

auto HexTile::highlight() -> void {
    removeBorder();
    setBorder(sf::Color::Green, 5);
    highlighted = true;
}

auto HexTile::removeHighlight() -> void {
    highlighted = false;
    removeBorder();
}

auto HexTile::setActivity(bool t) -> void {
    isActive = t;
}

auto HexTile::getDrawn(sf::RenderWindow &window) const -> void {
    window.draw(button);
}
