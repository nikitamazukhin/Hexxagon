#pragma once
#include "HexTile.hpp"
#include "../PlayBoard.hpp"
#include "PawnSprite.hpp"
#include "../Exceptions/WrongPawn.cpp"
#include "../Exceptions/MissingPawn.cpp"
#include <array>
#include <iostream>
/**
 * The graphical representation of the logical game board, complete with clickable hex tiles and pawn sprites
 */

struct GraphicalBoard {
private:
    PlayBoard* logicBoard;

    sf::Texture* diamondTexture;

    sf::Texture* rubyTexture;

    std::array<std::array<HexTile, 9>, 9> hexGrid;

    std::array<std::array<PawnSprite, 9>, 9> pawns;

public:
    GraphicalBoard(sf::Texture &diamonds, sf::Texture &rubies);

    /**
     * Links this class with a complementary logical Hexxagon game board
     * @param logic The play board to link with
     */
    auto setLogic(PlayBoard* logic) -> void;

    auto setActivity(bool activity) -> void;

    /**
     * Highlights the specified coordinates
     * @param coordsToHighlight The coordinates that must be highlighted
     */
    auto setHighlight(std::vector<Coordinate> &coordsToHighlight) -> void;

    auto getDrawn(sf::RenderWindow &window) -> void;

    auto getMousedOver(sf::RenderWindow &window) -> void;

    auto getPressed(sf::RenderWindow &window) -> void;
};
