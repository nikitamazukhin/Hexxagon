#include <SFML/Graphics.hpp>
#include <iostream>
#include "ClassesHeaders/Graphics/GameWindow.hpp"
#include "ClassesHeaders/Graphics/GraphicalBoard.hpp"
#include "ClassesHeaders/Graphics/MenuButton.hpp"
#include "ClassesHeaders/Pawn.hpp"
#include "ClassesHeaders/Graphics/PawnCounter.hpp"
#include "ClassesHeaders/PlayBoard.hpp"
#include "ClassesHeaders/Graphics/TextField.hpp"
#include "ClassesHeaders/SaveSystem/Loading.hpp"
#include "ClassesHeaders/SaveSystem/Saving.hpp"

auto main() -> int {

    auto bauhs = sf::Font();
    bauhs.loadFromFile("Content/Fonts/BAUHS93.TTF");

    auto diamondTexture = sf::Texture();
    diamondTexture.loadFromFile("Content/Textures/diamond.jpg");

    auto rubyTexture = sf::Texture();
    rubyTexture.loadFromFile("Content/Textures/ruby.jpg");

    auto myBoard = PlayBoard();
    auto graphicalBoard = GraphicalBoard(diamondTexture, rubyTexture);
    graphicalBoard.setLogic(&myBoard);

    auto myWindow = GameWindow(GameWindow::MAIN_MENU, sf::VideoMode(900, 900), "Hexxagon");

    auto title = sf::Text();
    title.setString("HEXXAGON");
    title.setFont(bauhs);
    title.setCharacterSize(120);
    title.setFillColor(sf::Color::White);

    auto info = sf::Text();
    info.setString("Press HOME to save the current game");
    info.setFont(bauhs);
    info.setCharacterSize(15);
    info.setFillColor(sf::Color::White);

    auto windowDim = myWindow.getSize();

    float xPos = (static_cast<float>(windowDim.x) / 2) - (title.getLocalBounds().width / 2);
    float yPos = (static_cast<float>(windowDim.y) / 2) - (title.getLocalBounds().height / 1.5f);

    title.setPosition(xPos, yPos -200);

    info.setPosition(static_cast<float>(windowDim.x) - (title.getLocalBounds().width / 2), 20);

    auto newGameButton = MenuButton({200, 60}, sf::Color::Blue, "NEW GAME", 30,
                                    bauhs, sf::Color::White, true);
    newGameButton.centerOnWindow(myWindow);

    auto loadGameButton = MenuButton({200, 60}, sf::Color::Blue, "LOAD GAME", 30,
                                     bauhs, sf::Color::White, true);
    loadGameButton.centerOnWindow(myWindow, 0, 100);

    auto inputBox = TextField("Name of file: ", 40, bauhs, sf::Color::Green, false, false);
    inputBox.setPosition({ static_cast<float>(myWindow.getSize().x / 2), static_cast<float>(myWindow.getSize().y / 2) });

    auto highScoresButton = MenuButton({200, 60}, sf::Color::Blue, "HIGH SCORES", 30,
                                       bauhs, sf::Color::White, true);
    highScoresButton.centerOnWindow(myWindow, 0, 200);

    auto modeAI = MenuButton({350, 60}, sf::Color::Blue, "BATTLE AGAINST AI", 30,
                             bauhs, sf::Color::White, false);
    modeAI.centerOnWindow(myWindow, -200, 0);

    auto modePlayer = MenuButton({350, 60}, sf::Color::Blue, "BATTLE AGAINST PLAYER", 30,
                                 bauhs, sf::Color::White, false);
    modePlayer.centerOnWindow(myWindow, 200, 0);

    auto menuReturnButton = MenuButton({300, 60}, sf::Color::Blue, "BACK TO MENU", 30,
                                       bauhs, sf::Color::White, false);
    menuReturnButton.centerOnWindow(myWindow, 0, 200);

    auto diamondCounter = PawnCounter(0, 50, bauhs, sf::Color::Blue, false, 30,
                                      diamondTexture);
    diamondCounter.setPosition({ 50 ,static_cast<float>(myWindow.getSize().y - 50) });

    auto rubyCounter = PawnCounter(0, 50, bauhs, sf::Color::Red, true, 30, rubyTexture);
    rubyCounter.setPosition({ static_cast<float>(myWindow.getSize().x - 50), static_cast<float>(myWindow.getSize().y - 50) });

    while (myWindow.isOpen()) {
        auto evt = sf::Event();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            sf::String text = inputBox.getString();
            if (myWindow.getState() == GameWindow::LOAD_GAME) {
                try {
                    auto loadedBoard = Loading::loadBoard(text);

                    graphicalBoard.setActivity(true);

                    newGameButton.setActivity(false);
                    loadGameButton.setActivity(false);
                    highScoresButton.setActivity(false);

                    modeAI.setActivity(false);
                    modePlayer.setActivity(false);
                    menuReturnButton.setActivity(false);

                    inputBox.setPosition( {static_cast<float>(myWindow.getSize().x / 2),
                                           static_cast<float>(myWindow.getSize().y / 2 + 300)} );
                    inputBox.setText("");
                    inputBox.setDrawable(false);

                    myWindow.setState(GameWindow::GAME_PLAY);

                    myBoard.startGame(loadedBoard);
                } catch (MissingFile &evt) {
                    std::cout << evt.what();
                }
            }
            else if (myWindow.getState() == GameWindow::GAME_PLAY) {
                Saving::boardSaver(myBoard, text);

                inputBox.setActivity(false);
                inputBox.setText("");
                inputBox.setDrawable(false);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (myWindow.getState() == GameWindow::GAME_PLAY) {
                inputBox.setDrawable(false);
                inputBox.setText("");
                inputBox.setActivity(false);
            }
            inputBox.setActivity(false);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home)) {
            inputBox.setActivity(true);
            inputBox.setDrawable(true);
        }

        while(myWindow.pollEvent(evt)) {
            switch(evt.type) {

                case sf::Event::Closed: {
                    myWindow.close();
                }

                case sf::Event::MouseMoved:
                    if(newGameButton.isMousedOver(myWindow))
                        newGameButton.setBorder(sf::Color::Magenta, 10);
                    else
                        newGameButton.removeBorder();

                    if (loadGameButton.isMousedOver(myWindow))
                        loadGameButton.setBorder(sf::Color::Magenta, 10);
                    else
                        loadGameButton.removeBorder();

                    if (highScoresButton.isMousedOver(myWindow))
                        highScoresButton.setBorder(sf::Color::Magenta, 10);
                    else
                        highScoresButton.removeBorder();

                    if(modeAI.isMousedOver(myWindow))
                        modeAI.setBorder(sf::Color::Magenta, 10);
                    else
                        modeAI.removeBorder();

                    if (modePlayer.isMousedOver(myWindow))
                        modePlayer.setBorder(sf::Color::Magenta, 10);
                    else
                        modePlayer.removeBorder();

                    if (menuReturnButton.isMousedOver(myWindow))
                        menuReturnButton.setBorder(sf::Color::Magenta, 10);
                    else
                        menuReturnButton.removeBorder();

                    graphicalBoard.getMousedOver(myWindow);
                    break;

                case sf::Event::MouseButtonPressed:
                    if (evt.mouseButton.button == sf::Mouse::Left) {
                        if (newGameButton.isMousedOver(myWindow)) {
                            myWindow.setState(GameWindow::GAME_MODE);

                            newGameButton.setActivity(false);
                            loadGameButton.setActivity(false);
                            highScoresButton.setActivity(false);

                            modeAI.setActivity(true);
                            modePlayer.setActivity(true);
                            menuReturnButton.setActivity(true);

                            break;
                        }

                        if (loadGameButton.isMousedOver(myWindow)) {
                            myWindow.setState(GameWindow::LOAD_GAME);

                            newGameButton.setActivity(false);
                            loadGameButton.setActivity(false);
                            highScoresButton.setActivity(false);

                            modeAI.setActivity(false);
                            modePlayer.setActivity(false);
                            menuReturnButton.setActivity(true);

                            inputBox.setActivity(true);
                            inputBox.setDrawable(true);

                            break;
                        }

                        if (highScoresButton.isMousedOver(myWindow)) {
                            myWindow.setState(GameWindow::HIGH_SCORES);

                            newGameButton.setActivity(false);
                            loadGameButton.setActivity(false);
                            highScoresButton.setActivity(false);

                            modeAI.setActivity(false);
                            modePlayer.setActivity(false);
                            menuReturnButton.setActivity(true);

                            break;
                        }

                        if (modeAI.isMousedOver(myWindow)) {
                            myWindow.setState(GameWindow::GAME_PLAY);
                            graphicalBoard.setActivity(true);
                            myBoard.startGame(true);

                            newGameButton.setActivity(false);
                            loadGameButton.setActivity(false);
                            highScoresButton.setActivity(false);

                            modeAI.setActivity(false);
                            modePlayer.setActivity(false);
                            menuReturnButton.setActivity(false);

                            inputBox.setPosition( {static_cast<float>(myWindow.getSize().x / 2),
                                                   static_cast<float>(myWindow.getSize().y /2 + 300)} );
                            inputBox.setText("");
                            inputBox.setDrawable(false);

                            break;
                        }

                        if (modePlayer.isMousedOver(myWindow)) {
                            myWindow.setState(GameWindow::GAME_PLAY);
                            graphicalBoard.setActivity(true);
                            myBoard.startGame(false);

                            newGameButton.setActivity(false);
                            loadGameButton.setActivity(false);
                            highScoresButton.setActivity(false);

                            modeAI.setActivity(false);
                            modePlayer.setActivity(false);
                            menuReturnButton.setActivity(false);

                            inputBox.setPosition( {static_cast<float>(myWindow.getSize().x / 2),
                                                   static_cast<float>(myWindow.getSize().y /2 + 300)} );
                            inputBox.setText("");
                            inputBox.setDrawable(false);

                            break;
                        }

                        if (menuReturnButton.isMousedOver(myWindow)) {
                            myWindow.setState(GameWindow::MAIN_MENU);

                            newGameButton.setActivity(true);
                            loadGameButton.setActivity(true);
                            highScoresButton.setActivity(true);

                            modeAI.setActivity(false);
                            modePlayer.setActivity(false);
                            menuReturnButton.setActivity(false);

                            inputBox.setText("");

                            break;
                        }
                        graphicalBoard.getPressed(myWindow);
                        break;
                    }

                case sf::Event::TextEntered: {
                    inputBox.getTypedOn(evt);
                    break;
                }
            }
        }

        switch(myWindow.getState()) {
            case GameWindow::MAIN_MENU:
                myWindow.clear(sf::Color::Black);

                myWindow.draw(title);

                newGameButton.getDrawn(myWindow);
                loadGameButton.getDrawn(myWindow);
                highScoresButton.getDrawn(myWindow);

                break;

            case GameWindow::GAME_MODE:
                myWindow.clear(sf::Color::Black);

                modeAI.getDrawn(myWindow);
                modePlayer.getDrawn(myWindow);
                menuReturnButton.getDrawn(myWindow);

                break;

            case GameWindow::LOAD_GAME:
                myWindow.clear(sf::Color::Black);

                inputBox.getDrawn(myWindow);
                menuReturnButton.getDrawn(myWindow);

                break;

            case GameWindow::HIGH_SCORES:
                myWindow.clear(sf::Color::Black);

                menuReturnButton.getDrawn(myWindow);

                break;

            case GameWindow::GAME_PLAY:
                myWindow.clear(sf::Color::Black);

                graphicalBoard.getDrawn(myWindow);

                diamondCounter.update(myBoard.getPawnCount(Pawn::BLUE));
                diamondCounter.getDrawn(myWindow);

                rubyCounter.update(myBoard.getPawnCount(Pawn::RED));
                rubyCounter.getDrawn(myWindow);

                myWindow.draw(info);
                inputBox.getDrawn(myWindow);

                break;
        }

        myWindow.display();
    }
}