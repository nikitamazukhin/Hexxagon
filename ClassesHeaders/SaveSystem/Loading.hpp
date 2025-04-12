#pragma once
#include "../PlayBoard.hpp"
#include "SFML/System/String.hpp"
#include "../Exceptions/MissingFile.cpp"
#include <filesystem>
#include <fstream>
struct Loading {
    static auto loadBoard(const sf::String &filename) -> std::array<std::array<Pawn, 9>, 9>;

    auto loadScores() -> std::vector<char>;

    static auto readNBytes(std::ifstream &inStream, int n) -> std::vector<char>;
};