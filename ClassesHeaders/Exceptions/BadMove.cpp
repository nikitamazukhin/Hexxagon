#pragma once
#include <exception>

struct BadMove final : std::exception {
    const char *what() {
        return "You can't move your selected pawn there.";
    }
};