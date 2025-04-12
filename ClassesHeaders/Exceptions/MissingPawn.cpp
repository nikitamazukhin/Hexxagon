#pragma once
#include <exception>

struct MissingPawn : std::exception {
    const char *what() {
        return "No pawn selected. Please select a valid pawn before trying to move.";
    }
};