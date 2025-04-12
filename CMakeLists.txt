cmake_minimum_required(VERSION 3.22)
project(Hexxagon)
set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML.git
        GIT_TAG         2.5.1
)
FetchContent_MakeAvailable(SFML)
add_executable(Hexxagon main.cpp
        ClassesHeaders/Exceptions/BadMove.cpp
        ClassesHeaders/Coordinate.cpp
        ClassesHeaders/Graphics/GameWindow.cpp
        ClassesHeaders/Graphics/GraphicalBoard.cpp
        ClassesHeaders/Graphics/HexTile.cpp
        ClassesHeaders/SaveSystem/Loading.cpp
        ClassesHeaders/Graphics/MenuButton.cpp
        ClassesHeaders/Exceptions/MissingFile.cpp
        ClassesHeaders/Exceptions/MissingPawn.cpp
        ClassesHeaders/Pawn.cpp
        ClassesHeaders/Graphics/PawnCounter.cpp
        ClassesHeaders/Graphics/PawnSprite.cpp
        ClassesHeaders/PlayBoard.cpp
        ClassesHeaders/SaveSystem/Saving.cpp
        ClassesHeaders/Exceptions/WrongPawn.cpp
        ClassesHeaders/Graphics/TextField.cpp)
target_compile_definitions(Hexxagon PRIVATE SFML_BUILD_STATIC)
target_link_libraries(Hexxagon sfml-graphics sfml-audio sfml-network sfml-window sfml-system)
