#include "MenuButton.hpp"

MenuButton::MenuButton(const sf::Vector2f &size, const sf::Color &bg, const std::string &text, unsigned int charSize, const sf::Font &font, const sf::Color &textColor, bool active) : isActive(active) {
    button.setSize(size);
    button.setFillColor(bg);

    label.setString(text);
    label.setFont(font);
    label.setCharacterSize(charSize);
    label.setFillColor(textColor);
}

auto MenuButton::setBorder(const sf::Color &color, float thickness) -> void {
    button.setOutlineColor(color);
    button.setOutlineThickness(thickness);
}

auto MenuButton::removeBorder() -> void {
    button.setOutlineColor(sf::Color::Transparent);
    button.setOutlineThickness(0);
}

auto MenuButton::setPosition(sf::Vector2f pos) -> void {
    button.setPosition(pos);
    auto buttonDim = button.getSize();

    float xPos = (pos.x + buttonDim.x / 2) - (label.getLocalBounds().width / 2);
    float yPos = (pos.y + buttonDim.y / 2) - (label.getLocalBounds().height / 1.5f);

    label.setPosition(xPos, yPos);
}

auto MenuButton::centerOnWindow(sf::RenderWindow &window) -> void {
    auto windowDim = window.getSize();
    auto buttonDim = button.getSize();

    setPosition({ static_cast<float>(windowDim.x) / 2.f - buttonDim.x / 2.f,
                 static_cast<float>(windowDim.y) / 2.f - buttonDim.y / 2.f });
}

auto MenuButton::centerOnWindow(sf::RenderWindow &window, float xOffset, float yOffset) -> void {
    auto windowDim = window.getSize();
    auto buttonDim = button.getSize();

    setPosition({ (static_cast<float>(windowDim.x) / 2.f - buttonDim.x / 2.f) + xOffset,
                        (static_cast<float>(windowDim.y) / 2.f - buttonDim.y / 2.f) + yOffset });
}

auto MenuButton::getSize() const -> sf::Vector2f {
    return button.getSize();
}

auto MenuButton::isMousedOver(sf::RenderWindow &window) const -> bool {
    if(isActive) {
        auto mousePos = sf::Mouse::getPosition(window);
        auto mouseX = mousePos.x;
        auto mouseY = mousePos.y;

        auto buttonPos = button.getPosition();
        auto buttonXStart = buttonPos.x;
        auto buttonYStart = buttonPos.y;

        auto buttonSize = button.getLocalBounds();
        auto buttonXEnd = buttonXStart + buttonSize.width;
        auto buttonYEnd = buttonYStart + buttonSize.height;

        return (buttonXStart < mouseX && mouseX < buttonXEnd && buttonYStart < mouseY && mouseY < buttonYEnd);
    }
    else
        return false;
}

auto MenuButton::setActivity(bool t) -> void {
    isActive = t;
}

auto MenuButton::getDrawn(sf::RenderWindow &window) const -> void {
        window.draw(button);
        window.draw(label);
}