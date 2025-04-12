#include "Saving.hpp"

auto Saving::pieceTypeInfo(Pawn::PawnType type) -> char {
    switch(type) {
        case Pawn::BLUE:
            return 1;
        case Pawn::RED:
            return 0;
        case Pawn::NONE:
            return -1;
        default:
            throw std::exception();
    }
}

auto Saving::pieceSaver(Pawn::PawnType type, int x, int y) -> std::array<char, 3> {
    auto toWrite = std::array<char, 3>{};

    toWrite[0] = pieceTypeInfo(type);
    toWrite[1] = static_cast<char>(x);
    toWrite[2] = static_cast<char>(y);

    return toWrite;
}

auto Saving::boardSaver(PlayBoard &board, sf::String &filename) -> void {
    auto outStream = std::ofstream(filename+".bin");

    for (int y = 0; y < board.getHeight(); ++y) {
        for (int x = 0; x < board.getWidth(); ++x) {

            auto temp = pieceSaver(board.getPawnTypeAt(x, y), x, y);

            for (auto const &elem : temp) {
                outStream << elem;
            }
        }
    }
    outStream.close();
}
