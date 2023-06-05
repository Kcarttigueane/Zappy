/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** display
*/

#include "../../include/display.hpp"
#define ASSET_WIDHT 444
#define ASSET_HEIGHT 498
#define SCALE 0.2
#define ISOMETRIC_WIDTH_OFFSET 930
#define ISOMETRIC_HEIGH_OFFSET 400

void Display::handleEvents()
{
    while (_window->pollEvent(*_event)) {
        if (_event->type == sf::Event::KeyPressed) {
            if (_event->key.code == sf::Keyboard::Escape || _event->key.code == sf::Keyboard::Q)
                _displayLoop = 0;
        } else if (_event->type == sf::Event::Closed) {
            _displayLoop = 0;
        }
    }
    handleMouseEvents();
}

sf::Vector2f getGridCoordinates(float x, float y)
{
    float og_a = 0.5 * ASSET_WIDHT * SCALE;
    float og_b = -0.5 * ASSET_WIDHT * SCALE;
    float og_c = 0.25 * ASSET_HEIGHT * SCALE;
    float og_d = 0.25 * ASSET_HEIGHT * SCALE;
    float det = (-1 / (og_a * og_d - og_b * og_c));

    float a = det * og_d;
    float b = det * -og_b;
    float c = det * -og_c;
    float d = det * og_a;

    sf::Vector2f pos;
    pos.x = -(x * a + y * b) - 19;
    pos.y = -(x * c + y * d) + 3;
    return pos;
}

void Display::handleMouseEvents()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
    int mouseX = mousePosition.x;
    int mouseY = mousePosition.y;
    _mouseGridCoords = getGridCoordinates(float(mouseX), float(mouseY));
}

void Display::draw()
{
    sf::Color myGrey(15, 15, 15, 255);
    _window->clear(myGrey);
    drawTileMap(10, 10);
    _window->display();
}

void Display::drawTileMap(int width, int height)
{
    sf::IntRect rect;
    rect.left = 183;
    rect.top = 42;
    rect.height = ASSET_HEIGHT;
    rect.width = ASSET_WIDHT;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            createIsometricEntity(i, j, SCALE, _texture, rect);
            _window->draw(*_sprite);
        }
    }
}

sf::Vector2f getIsometricPos(float x, float y, float scale, sf::IntRect rect)
{
    sf::Vector2f pos;

    pos.x = (x * (0.5 * rect.width) + y * (-0.5 * rect.width)) * scale;
    pos.y = (x * (0.25 * rect.height) + y * (0.25 * rect.height)) * scale;
    pos.x += ISOMETRIC_WIDTH_OFFSET;
    pos.y += ISOMETRIC_HEIGH_OFFSET;
    return pos;
}

void Display::createIsometricEntity(float x, float y, float scale, sf::Texture *texture, sf::IntRect rect)
{
    sf::Vector2f pos = getIsometricPos(x, y, scale, rect);
    if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y))
        pos.y -= 5;
    _sprite->setTexture(*texture);
    _sprite->setPosition(pos);
    _sprite->setScale(sf::Vector2f(scale, scale));
    _sprite->setTextureRect(rect);

}
