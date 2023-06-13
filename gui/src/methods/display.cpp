/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** display
*/

#include "../../include/display.hpp"


void Display::draw()
{
    _window->clear(sf::Color(0, 50, 70));
    drawTileMap();
    drawEntities();
    drawUI();
    _window->display();
}

void Display::drawTileMap()
{
    sf::IntRect rect;
    rect.left = 183;
    rect.top = 42;
    rect.height = ASSET_HEIGHT;
    rect.width = ASSET_WIDHT;

    for (int i = -EXTRA_TILES; i < EXTRA_TILES + _mapWidth; i++) {
        for (int j = -EXTRA_TILES; j < EXTRA_TILES + _mapHeight; j++) {
            createIsometricCube(i, j, _scale, _cubeTexture, rect, isMapCube(i, j));
            _window->draw(*_sprite);
        }
    }
}

bool Display::isMapCube(int x, int y)
{
    return x >= 0 && x < _mapWidth && y >= 0 && y < _mapHeight;
}

#define WAVE_FREQ 0.02
#define TIME_INCREMENT 3.5
#define OFFSET_SCALE 130

sf::Color color_multi(sf::Color color, double scalar)
{
    return sf::Color(color.r * scalar, color.g * scalar, color.b * scalar);
}

void Display::createIsometricCube(float x, float y, float scale, sf::Texture *texture, sf::IntRect rect, bool isCenterCube)
{
    sf::Vector2f pos = getIsometricPos(x, y, scale, rect, _x_offset, _y_offset);
    int oddeven = (int(std::abs(x)) + int(std::abs(y))) % 2;
    sf::Color colors[2][2] = {{sf::Color(0, 84, 118), sf::Color(0, 84, 118)}, {sf::Color(124, 252, 0, 255), sf::Color(50, 205, 0, 255)}};
    float color_offset = 1;
    
    if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y) && isCenterCube) {
        pos.y -= 30 * _scale;
        _sprite->setColor(sf::Color::Yellow);
    }
    if (!isCenterCube) {
        Tile tile = _tileMovement[(int(y) + EXTRA_TILES) * (EXTRA_TILES * 2 + 1) + (int(x) + EXTRA_TILES)];
        float t = _frame * TIME_INCREMENT;
        tile.offset = sin(x + WAVE_FREQ * t) + cos(y + WAVE_FREQ * t);
        color_offset = std::max(((-tile.offset + 2.0) / 2.0), 0.6);
        tile.offset *= OFFSET_SCALE;
        pos.y += (tile.offset * _scale) + 20;
    }
    _sprite->setColor(color_multi(colors[int(isCenterCube)][oddeven], color_offset));
    if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y) && isCenterCube) {
        pos.y -= 30 * _scale;
        _sprite->setColor(sf::Color::Yellow);
    }
    _sprite->setTexture(*texture);
    _sprite->setPosition(pos);
    _sprite->setScale(sf::Vector2f(scale, scale));
    _sprite->setTextureRect(rect);
}

void Display::drawUI()
{
    //Tile ui
    sf::Vector2u size = _uiTexture->getSize();
    _sprite->setTexture(*_uiTexture);
    _sprite->setTextureRect(sf::IntRect(0, 0, size.x, size.y));
    _sprite->setScale(0.773, 1);
    _sprite->setPosition(_uiPosition);
    _sprite->setColor(sf::Color::White);
    if (_uiAnimationPoint && _uiPosition.y > 800)
        _uiPosition.y -= 10;
    if (!_uiAnimationPoint && _uiPosition.y < 1080)
        _uiPosition.y += 10;;
    _window->draw(*_sprite);

    char buffer[100];
    Tile tile = _tiles[(_mapHeight - int(_lastClickedCoords.y) - 1) * _mapWidth + int(_lastClickedCoords.x)];
    std::sprintf(buffer, "    %d     %d     %d     %d     %d     %d     %d", tile.food, tile.linemate, tile.deraumere, tile.sibur, tile.mendiane, tile.phiras, tile.thystame);
    sf::Text text;
    text.setFont(*_font);
    text.setString(buffer);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(40);
    text.setPosition(sf::Vector2f(_uiPosition.x, _uiPosition.y + 70));
    _window->draw(text);

    //Player UI
    if (_uiPlayerPoint && _uiPlayerPosition.y < 50)
        _uiPlayerPosition.y += 10;
    if (!_uiPlayerPoint && _uiPlayerPosition.y > -200)
        _uiPlayerPosition.y -= 10;
    _sprite->setPosition(_uiPlayerPosition);
    _window->draw(*_sprite);
    tile = _playerTile;
    std::sprintf(buffer, "    %d     %d     %d     %d     %d     %d     %d", tile.food, tile.linemate, tile.deraumere, tile.sibur, tile.mendiane, tile.phiras, tile.thystame);
    text.setString(buffer);
    text.setPosition(sf::Vector2f(_uiPlayerPosition.x, _uiPlayerPosition.y + 70));
    _window->draw(text);

}