/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** events
*/

#include "../../include/display.hpp"

// left : 0 top: 434 width: 67  Height: 170
// 
void Display::handleEvents()
{
    static bool isDragging = false;
    static sf::Vector2i dragStartPosition;
    sf::Vector2i currentMousePosition;

    getMousePosition();
    while (_window->pollEvent(*_event)) {
        if (_event->type == sf::Event::KeyPressed) {
            if (_event->key.code == sf::Keyboard::Escape || _event->key.code == sf::Keyboard::Q)
                _displayLoop = 0;
            if (_event->key.code == sf::Keyboard::R) {
                _x_offset = ISOMETRIC_X_OFFSET;
                _y_offset = ISOMETRIC_Y_OFFSET;
                _scale = SCALE;
            }
            if (_event->key.code == sf::Keyboard::Left) {
                _selectedTeam = (_selectedTeam - 1) % _teamNames.size();
                checkTotalLvls();
            }
            if (_event->key.code == sf::Keyboard::Right) {
                _selectedTeam = (_selectedTeam + 1) % _teamNames.size();
                checkTotalLvls();
            }
        } else if (_event->type == sf::Event::Closed) {
            _displayLoop = 0;
        } else if (_event->type == sf::Event::MouseWheelScrolled) {
            if (_event->mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                if (_event->mouseWheelScroll.delta > 0 && _scale < 1.0) {
                    _scale += 0.05;
                    _scale = std::min(1.0, _scale);
                } else if (_event->mouseWheelScroll.delta < 0 && _scale >= 0.15) {
                    _scale -= 0.05;
                    _scale = std::max(0.01, _scale);
                }
            }
        } else if (_event->type == sf::Event::MouseButtonPressed) {
            if (_event->mouseButton.button == sf::Mouse::Left) {
                _tileClicked = false;
                _uiAnimationPoint = 0;
                _uiPlayerPoint = 0;
                isDragging = true;
                dragStartPosition = sf::Mouse::getPosition(*_window);
                currentMousePosition = dragStartPosition;
                if (_mouseGridCoords.x >= 0 && _mouseGridCoords.x < _mapWidth && _mouseGridCoords.y >= 0 && _mouseGridCoords.y < _mapHeight) {
                    _lastClickedCoords = _mouseGridCoords;
                    _sideUIState = 0;
                    _tileClicked = true;
                    _uiAnimationPoint = 1;
                    for (size_t i = 0; i < _entities.size(); i++) {
                        int x = int(_entities[i]._x + 0.05);
                        int y = int(_entities[i]._y + 0.05);
                        if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y) && !_entities[i]._dead) {
                            _notFirstSelect = 1;
                            _uiPlayerPoint = 1;
                            _selectedPlayerNumber = _entities[i]._playerNumber;
                            char buffer[10];
                            std::sprintf(buffer, "pin %d\n", _entities[i]._playerNumber);
                            sendData(buffer);
                        }
                    }
                }
                if (_sliderHandle.getGlobalBounds().contains(_event->mouseButton.x, _event->mouseButton.y)) {
                    _sliderDrag = true;
                    isDragging = false;
                }
                sf::FloatRect sideUIRect(_sideUI_x + 245, 434, 67, 170);
                if (sideUIRect.contains(_event->mouseButton.x, _event->mouseButton.y)) {
                    _sideUIState = !_sideUIState;
                }
            }
        } else if (_event->type == sf::Event::MouseMoved) {
            if (isDragging) {
                sf::Vector2i newMousePosition = sf::Mouse::getPosition(*_window);
                int deltaX = newMousePosition.x - dragStartPosition.x;
                int deltaY = newMousePosition.y - dragStartPosition.y;
                _x_offset += deltaX;
                _y_offset += deltaY;
                dragStartPosition = newMousePosition;
            }
            if (_sliderDrag) {
                int sliderx = _event->mouseMove.x - SLIDER_OFFSET - 15.0;
                if (sliderx < -5) {
                    sliderx = -5;
                }
                if (sliderx > 181) {
                    sliderx = 181;
                }
                sf::Vector2f sliderFillSize = _sliderFill.getSize();
                sliderFillSize.x = float(sliderx) + 5.0;
                _sliderFill.setSize(sliderFillSize);
                sf::Vector2f sliderPos = _sliderHandle.getPosition();
                sliderPos.x = float(sliderx) + SLIDER_OFFSET;
                _sliderHandle.setPosition(sliderPos);
                int outputMin = log(2);
                int outputMax = log(10000);
                int inputMin = -5;
                int inputMax = 181;
                int inputRange = inputMax - inputMin;
                int outputRange = outputMax - outputMin;
                double power = 1.2;
                double mappedValue = exp((((sliderx - inputMin) * outputRange) / inputRange) + outputMin);
                mappedValue = pow(mappedValue, power);
                _serverTime = int(mappedValue);
                _serverTime = std::min(10000, _serverTime);
                _serverTime = std::max(2, _serverTime);
                if (_serverTime != _oldServerTime) {
                    char buffer[50];
                    std::sprintf(buffer, "sst %d\n", _serverTime);
                    sendData(buffer);
                }
            }
        } else if (_event->type == sf::Event::MouseButtonReleased) {
            if (_event->mouseButton.button == sf::Mouse::Left) {
                isDragging = false;
                _sliderDrag = false;
            }
        }
    }
}


void Display::getMousePosition()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
    int mouseX = mousePosition.x;
    int mouseY = mousePosition.y;
    _mouseGridCoords = getGridCoordinates(float(mouseX), float(mouseY), _scale, _x_offset, _y_offset);

    _highlightedPlayerNumber = -1;
    for (size_t i = 0; i < _entities.size(); i++) {
        int x = int(_entities[i]._x + 0.05);
        int y = int(_entities[i]._y + 0.05);
        if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y) && !_entities[i]._dead) {
            _highlightedPlayerNumber = _entities[i]._playerNumber;
            break;
        }
    }
}