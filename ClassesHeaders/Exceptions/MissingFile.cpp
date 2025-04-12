#pragma once
#include <exception>

struct MissingFile : std::exception {
    const char *what() {
        return "Unable to find specified file";
    }
};