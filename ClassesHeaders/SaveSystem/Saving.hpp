#pragma once
#include "../PlayBoard.hpp"
#include "../../cmake-build-debug/_deps/sfml-src/include/SFML/System/String.hpp"
#include "fstream"

/**
 * @brief Static methods useful for saving data to binary files
 */
struct Saving {
    /**
     * @brief Converts PawnType into a char value
     *
     * @param type The PawnType to convert
     * @return An unsigned character value representing the type
     */
    static auto pieceTypeInfo(Pawn::PawnType type) -> char;

    /**
     * @brief Packs information about a Pawn
     *
     * @param type The specified type of the Pawn the needs to be saved
     * @param x The X coordinate of the Pawn on the board
     * @param y The Y coordinate of the Pawn on the board
     * @return An array, consisting of 3 values in sequence: Type, X position, Y position on the board
     */
    static auto pieceSaver(Pawn::PawnType type, int x, int y) -> std::array<char, 3>;

    /**
     * @brief Saves an entire Hexxagon board to a file
     *
     * @param board The board to save
     * @param filename The name of the file that the board data will be saved to
     */
    static auto boardSaver(PlayBoard &board, sf::String &filename) -> void;
};
