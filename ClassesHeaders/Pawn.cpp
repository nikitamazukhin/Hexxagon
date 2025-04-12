#include "Pawn.hpp"


Pawn::Pawn() : type(NONE) {

}

Pawn::Pawn(const PawnType type) : type(type) {

}

Pawn::Pawn(const Pawn &p) {
    type = p.type;
}

auto Pawn::getType() const -> PawnType {
    return type;
}

auto Pawn::setType(PawnType pawnType) -> void {
    this->type = pawnType;
}

auto Pawn::getOneTileMoves() -> std::array<Coordinate, 6> {
    return oneTileMoves;
}

auto Pawn::getTwoTileMoves() -> std::array<Coordinate, 12> {
    return twoTileMoves;
}

auto Pawn::getMoves() -> std::array<Coordinate, 18> {
    auto toReturn = std::array<Coordinate, 18>{Coordinate()};

    std::ranges::copy(oneTileMoves, toReturn.begin());
    std::ranges::copy(oneTileMoves, toReturn.begin());
    std::ranges::copy(twoTileMoves, toReturn.begin() + oneTileMoves.size());

    return toReturn;
}

std::array<Coordinate, 6> Pawn::oneTileMoves = {
        Coordinate(-1, -1),
        Coordinate(0, -1),
        Coordinate(-1, 0),
        Coordinate(1, 0),
        Coordinate(0, 1),
        Coordinate(1, 1)
};

std::array<Coordinate, 12> Pawn::twoTileMoves = {
        Coordinate(-2, -2), Coordinate(-1, -2), Coordinate(0, -2),
        Coordinate(1, -1), Coordinate(2, 0), Coordinate(-2, -1),
        Coordinate(2, 1), Coordinate(-2, 0), Coordinate(2, 2),
        Coordinate(-1, 1), Coordinate(0, 2), Coordinate(1, 2),
};
