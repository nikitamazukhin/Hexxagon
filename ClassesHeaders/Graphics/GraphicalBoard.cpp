#include "GraphicalBoard.hpp"

GraphicalBoard::GraphicalBoard(sf::Texture &diamonds, sf::Texture &rubies) : logicBoard(nullptr),
                                                                             hexGrid{std::array<HexTile, 9>{HexTile()}},
                                                                             pawns{std::array<PawnSprite, 9>{PawnSprite(20)}},
                                                                             diamondTexture(&diamonds),
                                                                             rubyTexture(&rubies)
{

}

auto GraphicalBoard::setLogic(PlayBoard *logic) -> void {
    logicBoard = logic;
    for (int y = 0; y < logicBoard->getHeight(); ++y) {
        for (int x = 0; x < logicBoard->getWidth(); ++x) {
            if (PlayBoard::coordsInBounds(x, y))
                hexGrid[y][x].setDefaultLook();
        }
    }
}

auto GraphicalBoard::setActivity(bool activity) -> void {
    for (int y = 0; y < logicBoard->getHeight(); ++y) {
        for (int x = 0; x < logicBoard->getWidth(); ++x) {
            if (PlayBoard::coordsInBounds(x, y))
                hexGrid[y][x].setActivity(activity);
        }
    }
}

auto GraphicalBoard::setHighlight(std::vector<Coordinate> &coordsToHighlight) -> void {
    for (int y = 0; y < logicBoard->getHeight(); ++y) {
        for (int x = 0; x < logicBoard->getWidth(); ++x) {
            hexGrid[y][x].removeHighlight();
        }
    }
    std::ranges::for_each(coordsToHighlight, [this](Coordinate &coord) -> void {
        hexGrid[coord.y][coord.x].highlight();
    });
}

auto GraphicalBoard::getDrawn(sf::RenderWindow &window) -> void {
    for (int y = 0; y < logicBoard->getHeight(); ++y) {
        for (int x = 0; x < logicBoard->getWidth(); ++x) {
            if (PlayBoard::coordsInBounds(x, y)) {

                hexGrid[y][x].setPosition(window, x, y);
                hexGrid[y][x].getDrawn(window);

                auto pawnType = logicBoard->getPawnTypeAt(x, y);

                if(pawnType != Pawn::NONE) {
                    auto tempSprite = PawnSprite(25);

                    if (pawnType == Pawn::BLUE)
                        tempSprite.setTexture(diamondTexture);
                    else
                        tempSprite.setTexture(rubyTexture);

                    tempSprite.setPosition(window, x, y);

                    pawns[y][x] = tempSprite;
                    pawns[y][x].getDrawn(window);
                }
            }
        }
    }
}

auto GraphicalBoard::getMousedOver(sf::RenderWindow &window) -> void {
    for (int y = 0; y < logicBoard->getHeight(); ++y) {
        for (int x = 0; x < logicBoard->getWidth(); ++x) {
            if (hexGrid[y][x].isMousedOver(window))
                hexGrid[y][x].setBorder(sf::Color::Cyan, 5);
            else
                hexGrid[y][x].removeBorder();
        }
    }
}

auto GraphicalBoard::getPressed(sf::RenderWindow &window) -> void {
    for (int y = 0; y < logicBoard->getHeight(); ++y) {
        for (int x = 0; x < logicBoard->getWidth(); ++x) {
            if (hexGrid[y][x].isMousedOver(window)) {
                try {
                    logicBoard->getInput(x, y);

                    auto toHighlight = logicBoard->getMoveOpportunities();
                    setHighlight(toHighlight);
                } catch (WrongPawn &wrong) {
                    std::cout << wrong.what() << std::endl;
                } catch (MissingPawn &missing) {
                    std::cout << missing.what() << std::endl;
                }
            }
        }
    }
}