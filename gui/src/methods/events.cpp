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
    sf::Vector2f playerPos = _entities[0].getPosition();

    while (_window->pollEvent(*_event)) {
        if (_event->type == sf::Event::KeyPressed) {
            if (_event->key.code == sf::Keyboard::Escape || _event->key.code == sf::Keyboard::Q)
                _displayLoop = 0;
            if (_event->key.code == sf::Keyboard::R) {
                _x_offset = ISOMETRIC_X_OFFSET;
                _y_offset = ISOMETRIC_Y_OFFSET;
                _scale = SCALE;
            } if (_event->key.code == sf::Keyboard::Left) {\
                playerPos.x -= 0.4;
                _entities[0]._direction = DIR_LEFT;
            } else if (_event->key.code == sf::Keyboard::Right) {
                playerPos.x += 0.4;
                _entities[0]._direction = DIR_RIGHT;
            } else if (_event->key.code == sf::Keyboard::Up) {
                playerPos.y -= 0.4;
                _entities[0]._direction = DIR_UP;
            } else if (_event->key.code == sf::Keyboard::Down) {
                playerPos.y += 0.4;
                _entities[0]._direction = DIR_DOWN;
            }
        } else {
            _entities[0]._direction = DIR_STOP;
        } if (_event->type == sf::Event::Closed) {
            _displayLoop = 0;
        } else if (_event->type == sf::Event::MouseWheelScrolled) {
            if (_event->mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                if (_event->mouseWheelScroll.delta > 0 && _scale < 1.0) {
                    _scale += 0.05;
                    _scale = std::min(1.0, _scale);
                } else if (_event->mouseWheelScroll.delta < 0 && _scale > 0.00) {
                    _scale -= 0.05;
                    _scale = std::max(0.01, _scale);
                }
            }
        } else if (_event->type == sf::Event::MouseButtonPressed) {
            if (_event->mouseButton.button == sf::Mouse::Left) {
                isDragging = true;
                dragStartPosition = sf::Mouse::getPosition(*_window);
                currentMousePosition = dragStartPosition;
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
    getMousePosition();
    _entities[0].setPosition(playerPos);
}


void Display::getMousePosition()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
    int mouseX = mousePosition.x;
    int mouseY = mousePosition.y;
    _mouseGridCoords = getGridCoordinates(float(mouseX), float(mouseY), _scale, _x_offset, _y_offset);
}