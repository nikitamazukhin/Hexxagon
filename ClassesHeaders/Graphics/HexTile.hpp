#pragma once
#include <SFML/Graphics.hpp>
#include "cmath"

struct HexTile {
private:
    sf::CircleShape button;

    bool isActive;

    bool highlighted;

public:
    HexTile();

    HexTile(float radius, const sf::Color &bg, bool activity);

    auto setBorder(const sf::Color &color, float thickness) -> void;

    auto setDefaultLook() -> void;

    auto removeBorder() -> void;

    auto getPosition() const -> sf::Vector2f;

    auto setPosition(sf::RenderWindow &window, int x, int y) -> void;

    auto getSize() const -> sf::FloatRect;

    auto isMousedOver(sf::RenderWindow &window) const -> bool;

    auto setActivity(bool t) -> void;

    auto highlight() -> void;

    auto removeHighlight() -> void;

    auto getDrawn(sf::RenderWindow &window) const -> void;
};
