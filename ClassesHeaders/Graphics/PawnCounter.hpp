#pragma once
#include <SFML/Graphics.hpp>
#include "PawnSprite.hpp"

/**
 * @brief A graphical counter for all instances one type of Pawn on the boeard
 */

struct PawnCounter {
public:
    /**
     *
     * @param n Starting value
     * @param charSize Size of the characters
     * @param font Font for the characters
     * @param textColor Color of the text
     * @param leftAligned Whether the counter is to the left or right of the pawn sprite
     * @param radius The radius of the pawn sprite
     * @param texture The texture applied to the pawn sprite
     */
    PawnCounter(int n, unsigned int charSize, const sf::Font &font,
                const sf::Color &textColor, bool leftAligned, float radius, const sf::Texture &texture);

    auto setPosition(sf::Vector2f pos) -> void;

    /**
     * Sets the counter value to the value specified
     * @param n Value to update the counter
     */
    auto update(int n) -> void;

    auto getDrawn(sf::RenderWindow &window) const -> void;

private:
    sf::Text counter;
    PawnSprite sprite;
    bool leftAligned;
};