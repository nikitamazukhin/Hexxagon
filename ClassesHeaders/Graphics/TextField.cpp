#include "TextField.hpp"

TextField::TextField(const sf::String &infoText, unsigned int charSize, const sf::Font &font, sf::Color textColor, bool activity, bool drawable)
: textbox("", font, charSize), label(infoText, font, charSize), isActive(activity), isDrawable(drawable)
{
    textbox.setFillColor(textColor);
    label.setFillColor(textColor);
}

auto TextField::setPosition(sf::Vector2f pos) -> void {
    float xPos = pos.x - label.getLocalBounds().width/2;
    float yPos = pos.y - label.getLocalBounds().height * 3;

    textbox.setPosition(xPos, pos.y);
    label.setPosition(xPos, yPos);
}

auto TextField::setText(const sf::String &str) -> void {
    input.str("");
    textbox.setString(str);
}

auto TextField::setActivity(bool b) -> void {
    isActive = b;
    auto currentInput = input.str();
    auto newStr = std::string();

    for (char i : currentInput)
        newStr += i;

    if (isActive)
        textbox.setString(newStr + "_");
    else
        textbox.setString(newStr);

}

auto TextField::setDrawable(bool d) -> void {
    isDrawable = d;
}

auto TextField::getTypedOn(const sf::Event &keyInput) -> void {
    if (isActive) {
        auto charTyped = keyInput.text.unicode;
        if (charTyped < 128) {
            receiveInput(static_cast<char>(charTyped));
        }
    }
}


auto TextField::receiveInput(char charTyped) -> void {
    if (charTyped != BACKSPACE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY && charTyped != HOME_KEY) {
        input << charTyped;
    }
    else {
        if (charTyped == BACKSPACE_KEY) {
            if (textbox.getString().getSize() != 0)
                removeLastChar();
        }
    }
    textbox.setString(input.str() + "_");
}

auto TextField::removeLastChar() -> void {
    const auto oldStr = input.str();
    auto newStr = std::string();

    if (!oldStr.empty()) {
        for (int i = 0; i < oldStr.size() - 1; ++i) {
            newStr += static_cast<char>(oldStr[i]);
        }

        input.str("");
        input << newStr;

        textbox.setString(input.str());
    }
}

auto TextField::getString() const -> std::string {
    auto str = textbox.getString();
    if (isActive)
        return str.substring(0, str.getSize() - 1);
    else
        return str;
}

auto TextField::getDrawn(sf::RenderWindow &window) const -> void {
    if (isDrawable) {
        window.draw(textbox);
        window.draw(label);
    }
}