/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** events
*/

#include "../../include/display.hpp"

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
                    _tileClicked = true;
                    _uiAnimationPoint = 1;
                    for (size_t i = 0; i < _entities.size(); i++) {
                        int x = int(_entities[i]._x + 0.05);
                        int y = int(_entities[i]._y + 0.05);
                        if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y)) {
                            _notFirstSelect = 1;
                            _uiPlayerPoint = 1;
                            _selectedPlayerNumber = _entities[i]._playerNumber;
                            char buffer[10];
                            std::sprintf(buffer, "pin %d\n", _entities[i]._playerNumber);
                            sendData(buffer);
                        }
                    }
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
        } else if (_event->type == sf::Event::MouseButtonReleased) {
            if (_event->mouseButton.button == sf::Mouse::Left)
                isDragging = false;
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
        if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y)) {
            _highlightedPlayerNumber = _entities[i]._playerNumber;
            break;
        }
    }
}