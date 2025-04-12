#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>


/**
 * @brief Special key macros
 *
 * Macros for the character values of keys that are used in member methods which have special uses depending on the key.
 */
#define BACKSPACE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
#define HOME_KEY 36

/**
 * @brief Writable text field.
 *
 * This class can take input from the user's keyboard and show it on the screen.
 */
struct TextField {
public:
    /**
     * @brief Constructor for TextField class
     *
     * This creates a new TextField object with a specified label above the written text, along with setting
     * the sizes of the characters and their color. The specified activity state determines if the TextField
     * responds to keyboard input immediately after creation, and the drawable flag is similar but for
     * drawing the object on the screen
     *
     * @param label Informative text string that will appear above the written text
     * @param charSize The font size applied to each character of the label and written text
     * @param font The style of font which is applied to the text
     * @param textColor The color of the label and written text
     * @param activity Determines if the text field responds to keyboard input
     * @param drawable Determines if the text and label can be drawn on the screen
     */
    TextField(const sf::String &label, unsigned int charSize, const sf::Font &font, sf::Color textColor, bool activity, bool drawable);

    /**
     * @brief Receives input from the keyboard through an event
     *
     * @param input Event that should contain a unicode character value
     */
    auto getTypedOn(const sf::Event &input) -> void;

    /**
     * @brief Moves both the label and the text to a specified position
     *
     * @param pos A vector containing 2 float values for the x and y position on the screen
     */
    auto setPosition(sf::Vector2f pos) -> void;

    /**
     * @brief Sets the text String of the TextField to the specified parameter
     *
     * @param str String to replace the current text
     */
    auto setText(const sf::String &str) -> void;

    /**
     * @brief Sets the activity state of the TextField, whether it receives input or not
     *
     * @param b Boolean which sets the activity flag
     */
    auto setActivity(bool b) -> void;

    /**
     * @brief Sets the drawable state of the TextField, whether it will be drawn on the screen or not
     *
     * @param d Boolean which sets the drawable flag
     */
    auto setDrawable (bool d) -> void;

    /**
     * @brief Tells the specified window to draw the text and label Strings on the screen
     *
     * @param window RenderWindow that will draw the text and label
     */
    auto getDrawn(sf::RenderWindow &window) const -> void;

    /**
     * @return Current text string
     */
    auto getString() const -> std::string;

private:
    sf::Text textbox;
    sf::Text label;
    std::ostringstream input;
    bool isActive;
    bool isDrawable;

    /**
     * @brief Depending on the character value received, either appends the text string or deletes the last element.
     * The supported character values are limited to character value 128.
     *
     * @param charTyped Value of the unicode character to receive
     */
    auto receiveInput(char charTyped) -> void;

    /**
     * @brief Removes the last character
     */
    auto removeLastChar() -> void;
};