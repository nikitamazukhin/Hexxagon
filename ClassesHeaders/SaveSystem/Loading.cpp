#include "Loading.hpp"


auto Loading::loadBoard(const sf::String &filename) -> std::array<std::array<Pawn, 9>, 9> {
    if (const std::string fullName = filename+".bin"; std::filesystem::exists(fullName)) {
        auto inStream = std::ifstream(fullName);
        auto toReturn = std::array<std::array<Pawn, 9>, 9>();

        auto toAdd = readNBytes(inStream, 3);

        while (!toAdd.empty()) {
            switch (toAdd[0]) {
                case Pawn::BLUE:
                    toReturn[toAdd[2]][toAdd[1]].setType(Pawn::BLUE);
                    break;
                case Pawn::RED:
                    toReturn[toAdd[2]][toAdd[1]].setType(Pawn::RED);
                    break;
                case Pawn::NONE:
                    toReturn[toAdd[2]][toAdd[1]].setType(Pawn::NONE);
                    break;
            }
            toAdd = readNBytes(inStream, 3);
        }
        return toReturn;
    }
    else
        throw MissingFile();
}

auto Loading::loadScores() -> std::vector<char> {
    const std::string fullName = "highScores.bin";
    if (std::filesystem::exists(fullName)) {
        auto inStream = std::ifstream(fullName);

        return readNBytes(inStream, 5);
    }
    else
        throw MissingFile();
}

auto Loading::readNBytes(std::ifstream &inStream, int n) -> std::vector<char> {
    char data;
    auto toReturn = std::vector<char>();
    for(int i = 0; i < n; ++i) {
        if(inStream >> data)
            toReturn.push_back(data);
    }
    return toReturn;
}