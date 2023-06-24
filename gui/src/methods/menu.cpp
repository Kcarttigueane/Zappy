/*
** EPITECH PROJECT, 2023
** gui
** File description:
** menu
*/

#include "../../include/display.hpp"

std::string Display::handleClient()
{
    if (connectToServer()) {
        std::string response = receiveData();
        if (!response.empty())
            std::cout << response << std::endl;
        std::string message = "GRAPHIC\n";
        if (sendData(message)) {
            std::string response = receiveData();
            if (!response.empty()) {
                return response;
            }
        }
    }
    return "";
}

void Display::setupMenu()
{
    sf::RectangleShape inputBox(sf::Vector2f(300.f, 40.f));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineThickness(4.f);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setPosition(800.f, 400.f);

    _inputBoxIP = inputBox;
    inputBox.setPosition(800.f, 600.f);
    _inputBoxPort = inputBox;

    sf::RectangleShape button(sf::Vector2f(100.f, 50.f));
    button.setFillColor(sf::Color::Green);
    button.setOutlineThickness(2.f);
    button.setOutlineColor(sf::Color::Black);
    button.setPosition(900.f, 800.f);
    _playButton = button;


    sf::RectangleShape sliderBackground(sf::Vector2f(200.0f, 12.0f));
    sliderBackground.setPosition(SLIDER_OFFSET, 400.f);
    sliderBackground.setFillColor(sf::Color(155,155,155));

    sf::RectangleShape sliderFill;
    sliderFill.setPosition(SLIDER_OFFSET, 400.f);
    sliderFill.setFillColor(sf::Color::White);
    _sliderFill = sliderFill;

    sf::CircleShape sliderHandle(12.f);
    sliderHandle.setFillColor(sf::Color::White);
    _sliderBackground = sliderBackground;
    _sliderHandle = sliderHandle;

    _sliderHandle.setPosition(float(_serverTime) + SLIDER_OFFSET, 394.f);
    _sliderFill.setSize(sf::Vector2f(float(_serverTime) + 5.0, 12.f));

}

void Display::handleMenuEvents()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
    while (_window->pollEvent(*_event)) {
        if (_event->type == sf::Event::KeyPressed) {
            if (_event->key.code == sf::Keyboard::Escape) {
                _menuLoop = 0;
                _quit = 1;
            }
            if (_event->key.code == sf::Keyboard::Enter) {
                _clickedBox = 0;
                serverIP = _menuIpString;
                serverPort = atoi(_menuPortString.c_str()); 
                _serverResponse = handleClient();
                if (_serverResponse != "")
                    _menuLoop = 0;
                else
                    _errorServer = 1;
            }
        } else if (_event->type == sf::Event::Closed) {
            _menuLoop = 0;
            _quit = 1;
        }
        if (_event->type == sf::Event::MouseButtonPressed)
            if (_event->mouseButton.button == sf::Mouse::Left) {
                if (_inputBoxIP.getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y)))
                    _clickedBox = 1;
                else if (_inputBoxPort.getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y)))
                    _clickedBox = 2;
                else if (_playButton.getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
                    _clickedBox = 0;
                    serverIP = _menuIpString;
                    serverPort = atoi(_menuPortString.c_str()); 
                    _serverResponse = handleClient();
                    if (_serverResponse != "")
                        _menuLoop = 0;
                    else
                        _errorServer = 1;
                } else
                    _clickedBox = -1;
            }

        if (_event->type == sf::Event::TextEntered && _clickedBox > 0) {
            if (_event->text.unicode < 128) {
                _errorServer = 0;
                if (_event->text.unicode == '\b') {
                    if (_clickedBox == 1 && !_menuIpString.empty())
                        _menuIpString.erase(_menuIpString.length() - 1);
                    else if (_clickedBox == 2 && !_menuPortString.empty())
                        _menuPortString.erase(_menuPortString.length() - 1);
                } else if (_event->text.unicode != '\b') {
                    if (_clickedBox == 1 && _menuIpString.length() < 20)
                        _menuIpString += static_cast<char>(_event->text.unicode);
                    else if (_menuPortString.length() < 20)
                        _menuPortString += static_cast<char>(_event->text.unicode);
                }
            }
        }
    }

    if (_inputBoxPort.getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y)) || _clickedBox == 2) {
        _inputBoxPort.setOutlineColor(sf::Color::Yellow);
    } else {
        _inputBoxPort.setOutlineColor(sf::Color::Black);
    }
    if (_inputBoxIP.getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y)) || _clickedBox == 1) {
        _inputBoxIP.setOutlineColor(sf::Color::Yellow);
    } else {
        _inputBoxIP.setOutlineColor(sf::Color::Black);
    }
    if (_playButton.getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
        _playButton.setOutlineColor(sf::Color::Yellow);
    } else {
        _playButton.setOutlineColor(sf::Color::Black);
    }
}

void Display::drawMenu()
{
    _window->clear(sf::Color(0, 50, 70));
    sf::Text text;
    text.setFont(*_font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(10);

    _sprite->setTexture(*_titleTexture);
    _sprite->setPosition(sf::Vector2f(750, 60));
    _sprite->setTextureRect(sf::IntRect(0, 0, 415, 146));
    _sprite->setScale(sf::Vector2f(1.0, 1.0));
    _window->draw(*_sprite);

    text.setPosition(805.f, 375.f);
    text.setString("Server IP:");
    _window->draw(text);
    _window->draw(_inputBoxIP);
    text.setPosition(805.f, 575.f);
    text.setString("Server Port:");
    _window->draw(text);
    _window->draw(_inputBoxPort);

    _window->draw(_playButton);
    text.setCharacterSize(20);
    text.setPosition(910.f, 810.f);
    text.setString("PLAY");
    _window->draw(text);
    if (_errorServer) {
        text.setFillColor(sf::Color::Red);
        text.setCharacterSize(10);
        text.setPosition(820.f, 900.f);
        text.setString("Failed to connect to server.");
        _window->draw(text);
    }


    text.setCharacterSize(13);
    text.setFillColor(sf::Color::Black);
    text.setPosition(820.f, 410.f);
    std::string input = _menuIpString;
    if (_clickedBox == 1)
        input.append("|");
    text.setString(input);
    _window->draw(text);
    text.setPosition(820.f, 610.f);
    input = _menuPortString;
    if (_clickedBox == 2)
        input.append("|");
    text.setString(input);
    _window->draw(text);

    _window->display();
}


void Display::handleMenu()
{
    while (_menuLoop) {
        _deltaTime = _clock.restart();
        handleMenuEvents();
        drawMenu();
        sf::Time elapsedTime = _clock.getElapsedTime();
        if (elapsedTime < _frameTime)
            sf::sleep(_frameTime - elapsedTime);
    }
}