#include "GameWindow.hpp"


GameWindow::GameWindow(const WindowState state, const sf::VideoMode mode, const sf::String &title, sf::Uint32 style,
                       const sf::ContextSettings &settings) : windowState(state)
{
    create(mode, title, style, settings);
}

auto GameWindow::getState() const -> WindowState {
    return windowState;
}

auto GameWindow::setState(const WindowState state) -> void {
    windowState = state;
}
