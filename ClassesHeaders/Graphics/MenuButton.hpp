#pragma once
#include <SFML/Graphics.hpp>

/**
 * A button which is used for the starting menu
 */

struct MenuButton {
public:
    /**
     *
     * @param size Size of the button
     * @param bg Background color for the button
     * @param text Text label for info
     * @param charSize Size of the characters of the label
     * @param font The font of the text label
     * @param textColor The color of the text
     * @param active The active state
     */
    MenuButton(const sf::Vector2f &size, const sf::Color &bg, const std::string &text, unsigned int charSize, const sf::Font &font, const sf::Color &textColor, bool active);

    auto setBorder(const sf::Color &color, float thickness) -> void;

    auto removeBorder() -> void;

    auto setPosition(sf::Vector2f pos) -> void;

    auto centerOnWindow(sf::RenderWindow &window) -> void;

    auto centerOnWindow(sf::RenderWindow &window, float xOffset, float yOffset) -> void;

    auto getSize() const -> sf::Vector2f;

    auto isMousedOver(sf::RenderWindow &window) const -> bool;

    auto setActivity(bool t) -> void;

    auto getDrawn(sf::RenderWindow &window) const -> void;

private:
    sf::RectangleShape button;
    sf::Text label;

    bool isActive;

};
