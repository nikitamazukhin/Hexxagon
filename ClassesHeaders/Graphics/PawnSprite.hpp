#pragma once
#include <SFML/Graphics.hpp>

/**
 * A sprite for the pawns
 */

struct PawnSprite {
public:
    PawnSprite();

    explicit PawnSprite(float radius);

    PawnSprite(float radius, const sf::Texture *texture);

    auto setTexture(const sf::Texture *texture) -> void;

    auto getRadius() const -> float;

    auto getOrigin() const -> sf::Vector2f;

    auto setPosition(sf::Vector2f pos) -> void;

    auto setPosition(const sf::RenderWindow &window, int x, int y) -> void;

    /**
     * Draws the sprite inside the window
     * @param window window to draw in
     */
    auto getDrawn(sf::RenderWindow &window) const -> void;

private:
    sf::CircleShape sprite;

};
