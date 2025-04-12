#include <algorithm>
#include <map>
#include <iostream>
#include "PlayBoard.hpp"

PlayBoard::PlayBoard() : grid{std::array<Pawn, 9>{Pawn()}}, selected(nullptr), selectedCoords(Coordinate()), blueTurn(true), againstAI(false){

    grid[0][4].setType(Pawn::BLUE);
    grid[4][0].setType(Pawn::BLUE);
    grid[8][8].setType(Pawn::BLUE);

    grid[8][4].setType(Pawn::RED);
    grid[4][8].setType(Pawn::RED);
    grid[0][0].setType(Pawn::RED);
}

auto PlayBoard::startGame(bool ai) -> void {
    blueTurn = true;
    againstAI = ai;
}

auto PlayBoard::startGame(std::array<std::array<Pawn, 9>, 9> &board) -> void {
    blueTurn = true;
    grid = board;
}

auto PlayBoard::getPawnCoords(const Pawn::PawnType &type) const -> std::vector<Coordinate> {
    auto result = std::vector<Coordinate>();
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x].getType() == type) {
                result.emplace_back(x, y);
            }
        }
    }
    return result;
}

auto PlayBoard::getSurroundingEnemyPawns(Pawn::PawnType attackingType, int x, int y) -> std::vector<Pawn*> {
    auto enemies = std::vector<Pawn*>();
    auto oneTileDist = Pawn::getOneTileMoves();

    std::ranges::for_each(oneTileDist, [&](Coordinate coord) -> void {
        auto cx = x + coord.x;
        auto cy = y + coord.y;

        if (coordsInBounds(cx, cy)) {

            if (grid[cy][cx].getType() != attackingType && grid[cy][cx].getType() != Pawn::NONE) {
                enemies.push_back(&grid[cy][cx]);
            }
        }
    });

    return enemies;
}

auto PlayBoard::getMoveOpportunities() const -> std::vector<Coordinate> {
    auto moveOpportunities = std::vector<Coordinate>();
    if (selected != nullptr) {
        auto oneTileDist = Pawn::getOneTileMoves();

        std::ranges::for_each(oneTileDist, [&](Coordinate coord) -> void {
            auto cx = selectedCoords.x + coord.x;
            auto cy = selectedCoords.y + coord.y;

            if (coordsInBounds(cx, cy)) {
                if (grid[cy][cx].getType() == Pawn::NONE) {
                    moveOpportunities.emplace_back(cx, cy);
                }
            }
        });

        auto twoTileDist = Pawn::getTwoTileMoves();
        std::ranges::for_each(twoTileDist, [&](Coordinate coord) -> void {
            auto cx = selectedCoords.x + coord.x;
            auto cy = selectedCoords.y + coord.y;

            if (coordsInBounds(cx, cy)) {
                if (grid[cy][cx].getType() == Pawn::NONE) {
                    moveOpportunities.emplace_back(cx, cy);
                }
            }
        });
    }
    return moveOpportunities;
}

auto PlayBoard::getMoveOpportunities(int x, int y) const -> std::vector<Coordinate> {
    auto moveOpportunities = std::vector<Coordinate>();
    if (grid[y][x].getType() != Pawn::NONE) {
        auto oneTileDist = Pawn::getOneTileMoves();

        std::ranges::for_each(oneTileDist, [&](Coordinate coord) -> void {
            auto cx = x + coord.x;
            auto cy = y + coord.y;

            if (coordsInBounds(cx, cy)) {
                if (grid[cy][cx].getType() == Pawn::NONE) {
                    moveOpportunities.emplace_back(cx, cy);
                }
            }
        });

        auto twoTileDist = Pawn::getTwoTileMoves();
        std::ranges::for_each(twoTileDist, [&](Coordinate coord) -> void {
            auto cx = x + coord.x;
            auto cy = y + coord.y;

            if (coordsInBounds(cx, cy)) {
                if (grid[cy][cx].getType() == Pawn::NONE) {
                    moveOpportunities.emplace_back(cx, cy);
                }
            }
        });
    }
    return moveOpportunities;
}

auto PlayBoard::capturePawns(const std::vector<Pawn*> &toCapture) -> void {
    std::for_each(toCapture.begin(), toCapture.end(), [](Pawn *pawn) -> void {
        if (pawn->getType() == Pawn::BLUE)
            pawn->setType(Pawn::RED);
        else
            pawn->setType(Pawn::BLUE);
    });
}

auto PlayBoard::coordsInBounds(int x, int y) -> bool {
    return (-4 <= x - y && x - y <= 4) && (!(x == 3 && y == 4) && !(x == 4 && y == 3) && !(x == 5 && y == 5));
}

auto PlayBoard::movePawn(int x, int y) -> void {
    auto selType = selected->getType();

    for (Coordinate coord : Pawn::getOneTileMoves()) {
        if (coord.x == selectedCoords.x - x && coord.y == selectedCoords.y - y) {
            grid[y][x].setType(selType);

            capturePawns(getSurroundingEnemyPawns(selType, x, y));

            selected = nullptr;
            blueTurn = !blueTurn;

            if (againstAI)
                AIMove();
            return;
        }
    }

    for (Coordinate coord : Pawn::getTwoTileMoves()) {
        if (coord.x == selectedCoords.x - x && coord.y == selectedCoords.y - y) {
            grid[y][x].setType(selType);

            selected->setType(Pawn::NONE);
            capturePawns(getSurroundingEnemyPawns(selType, x, y));

            selected = nullptr;
            blueTurn = !blueTurn;

            if (againstAI)
                AIMove();
            return;
        }
    }
    throw BadMove();
}

auto PlayBoard::AIMove() -> void {
    auto AIPawns = getPawnCoords(Pawn::RED);
    auto largestKillCount = 0;
    auto count = 0;
    auto bestPawnCoords = Coordinate();
    auto bestAttackCoord = Coordinate();
    auto mostCaptives = std::vector<Pawn*>();
    auto moves = std::vector<Coordinate>();
    auto temp = std::vector<Pawn*>();

    for(const auto &p : AIPawns) {
        moves = getMoveOpportunities(p.x, p.y);

        for(const auto &move : moves) {
            temp = getSurroundingEnemyPawns(Pawn::RED, move.x, move.y);
            count = temp.size();
            if (count >= largestKillCount) {
                largestKillCount = count;
                bestPawnCoords = p;
                bestAttackCoord = move;
                mostCaptives = temp;
            }
        }
    }

    auto oneTile = Pawn::getOneTileMoves();
    for (const auto &coord : oneTile) {
        if (coord.x == bestAttackCoord.x && coord.y == bestAttackCoord.y) {
            grid[bestAttackCoord.y][bestAttackCoord.x].setType(Pawn::RED);
            capturePawns(mostCaptives);
            blueTurn = !blueTurn;
            return;
        }
    }

    auto twoTile = Pawn::getTwoTileMoves();
    for (const auto &coord : twoTile) {
        if (coord.x == bestAttackCoord.x && coord.y == bestAttackCoord.y) {
            grid[bestAttackCoord.y][bestAttackCoord.x].setType(Pawn::RED);
            grid[bestPawnCoords.y][bestPawnCoords.y].setType(Pawn::NONE);
            capturePawns(mostCaptives);
            blueTurn = !blueTurn;
            return;
        }
    }
}

auto PlayBoard::getInput(int x, int y) -> void {
    if (coordsInBounds(x, y)) {
        if(grid[y][x].getType() == Pawn::NONE) {
            if (selected == nullptr)
                throw MissingPawn();
            else {
                try {
                    movePawn(x, y);
                } catch (BadMove &bad) {
                    bad.what();
                }
            }
        }
        else if(grid[y][x].getType() == blueTurn) {
            selected = &grid[y][x];
            selectedCoords = Coordinate(x, y);
        }
        else
            throw WrongPawn();
    }
}

auto PlayBoard::getHeight() const -> int {
    return grid.size();
}

auto PlayBoard::getWidth() const -> int {
    return grid[0].size();
}

auto PlayBoard::getPawnTypeAt(int x, int y) const -> Pawn::PawnType {
    return grid[y][x].getType();
}

auto PlayBoard::getPawnCount(Pawn::PawnType type) const -> int {
    auto totalSum = 0;

    for (const auto &row : grid) {
        totalSum += static_cast<int>(std::ranges::count_if(row, [&type](const Pawn& p) -> bool {
            return p.getType() == type;
        }));
    }

    return totalSum;
}