#pragma once

#include <array>
#include <vector>
#include "Pawn.hpp"
#include "Exceptions/BadMove.cpp"
#include "Exceptions/MissingPawn.cpp"
#include "Exceptions/WrongPawn.cpp"

/**
 * @brief The logical part of the Hexxagon game
 *
 * A class that contains the 9x9 grid of the play field with Pawns inside
 */

struct PlayBoard {
    PlayBoard();

    /**
     * @brief Starts the game with the default configuration of pawns
     *
     * @param againstAI Specifies whether the game is against an AI opponent
     */
    auto startGame(bool againstAI) -> void;

    /**
     * @brief Starts the game with an already created board. The board replaces the standard board of the Hexxagon configuration
     * @param board The board to replace the standard board
     */
    auto startGame(std::array<std::array<Pawn, 9>, 9> &board) -> void;

    /**
     * @brief Looks for pawns of the opposite type that are around the specified coordinates
     *
     * @param attackingType The friendly pawn type that is attacking the pawns at the position
     * @param x The x position of the attack
     * @param y The y position of the attack
     * @return Vector of pointers to pawns that are being attacked
     */
    auto getSurroundingEnemyPawns(Pawn::PawnType attackingType, int x, int y) -> std::vector<Pawn*>;

    /**
     * @brief Looks for possible moves for the selected pawn and returns them
     *
     * @return Coordinates with opportune moves
     */
    [[nodiscard]] auto getMoveOpportunities() const -> std::vector<Coordinate>;

    /**
     * @brief Looks for possible moves for the pawn on the specified position and returns them
     *
     * @param x The x position of the pawn that must move
     * @param y The y position of the pawn that must move
     * @return Vector of coordinates with opportune moves
     */
    [[nodiscard]] auto getMoveOpportunities(int x, int y) const -> std::vector<Coordinate>;

    /**
     * @brief "Captures" the pawns in the vector, reversing their type
     *
     * @param toCapture Pointers to pawns that must be captured
     */
    auto capturePawns(const std::vector<Pawn*> &toCapture) -> void;

    /**
     * Moves the selected pawn to the coordinates on the board
     *
     * @param x X coordinate
     * @param y Y coordinate
     */
    auto movePawn(int x, int y) -> void;

    /**
     * Checks if the moves are legal for the board
     *
     * @param x X coordinate to check
     * @param y Y coordinate to check
     * @return Returns true if the coordinates are legal
     */
    static auto coordsInBounds(int x, int y) -> bool;

    /**
     * @brief An algorithm is used to execute the best move for the AI
     *
     */
    auto AIMove() -> void;

    /**
     * Received input from the graphical component
     * @param x X coordinate
     * @param y Y coordinate
     */
    auto getInput(int x, int y) -> void;

    [[nodiscard]] auto getHeight() const -> int;

    [[nodiscard]] auto getWidth() const -> int;

    [[nodiscard]] auto getPawnTypeAt(int x, int y) const -> Pawn::PawnType;

    [[nodiscard]] auto getPawnCount(Pawn::PawnType type) const -> int;

private:
    std::array<std::array<Pawn, 9>, 9> grid;

    Pawn* selected;

    Coordinate selectedCoords;

    bool blueTurn;

    bool againstAI;

    [[nodiscard]] auto getPawnCoords(const Pawn::PawnType &type) const -> std::vector<Coordinate>;
};