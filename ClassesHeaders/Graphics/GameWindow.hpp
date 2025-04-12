#pragma once
#include <SFML/Graphics.hpp>

struct GameWindow final : sf::RenderWindow {
    enum WindowState {
        MAIN_MENU,
        GAME_MODE,
        LOAD_GAME,
        HIGH_SCORES,
        GAME_PLAY,
    };

private:
    WindowState windowState;

public:
    GameWindow(WindowState state, sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default,
               const sf::ContextSettings& settings = sf::ContextSettings());

    auto getState() const -> WindowState;

    auto setState(WindowState state) -> void;
};

