#pragma once
#include "Coordinate.hpp"
#include <array>
#include <algorithm>

struct Pawn {
    enum PawnType {
        NONE = -1,
        BLUE = 1,
        RED = 0
    };

    Pawn();

    explicit Pawn(PawnType type);

    Pawn(const Pawn &p);

    [[nodiscard]] auto getType() const -> PawnType;

    auto setType(PawnType pawnType) -> void;

    static auto getOneTileMoves() -> std::array<Coordinate, 6>;

    static auto getTwoTileMoves() -> std::array<Coordinate, 12>;

    static auto getMoves() -> std::array<Coordinate, 18>;


private:
    PawnType type;

    /**
     * @brief The possible moves a pawn can make 1 distance away
     */
    static std::array<Coordinate, 6> oneTileMoves;
    /**
     * @brief The possible moves a pawn can make 2 distance away
     */
    static std::array<Coordinate, 12> twoTileMoves;
};