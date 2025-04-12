#pragma once
#include <exception>

struct WrongPawn : std::exception {
    const char *what() {
        return "Can't select enemy pawn. Pick empty tile or friendly pawn.";
    }
};