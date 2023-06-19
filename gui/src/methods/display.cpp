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
    drawEgg();
    drawEntities();
    drawBroadcast();
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

    _sprite->setTexture(*_cubeTexture);
    _sprite->setScale(sf::Vector2f(_scale, _scale));
    _sprite->setTextureRect(rect);

    for (int i = -EXTRA_TILES; i < EXTRA_TILES + _mapWidth; i++) {
        for (int j = -EXTRA_TILES; j < EXTRA_TILES + _mapHeight; j++) {
            createIsometricCube(i, j, _scale, rect, isMapCube(i, j));
            _window->draw(*_sprite);
        }
    }
}

bool Display::isMapCube(int x, int y)
{
    return x >= 0 && x < _mapWidth && y >= 0 && y < _mapHeight;
}

#define WAVE_FREQ 0.02
#define TIME_INCREMENT 3.9
#define OFFSET_SCALE 100
#define DENOMINATOR 1.2

sf::Color color_multi(sf::Color color, double scalar)
{
    return sf::Color(color.r * scalar, color.g * scalar, color.b * scalar);
}

void Display::createIsometricCube(float x, float y, float scale, sf::IntRect rect, bool isCenterCube)
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
        tile.offset = sin((x / DENOMINATOR) + WAVE_FREQ * t) + cos((y / DENOMINATOR) + WAVE_FREQ * t);
        color_offset = std::min(((-tile.offset + 2.0) / 2.0) * 0.15 + 0.8, 1.0);
        tile.offset *= OFFSET_SCALE;
        pos.y += (tile.offset * _scale) + 20;
    }   
    _sprite->setColor(color_multi(colors[int(isCenterCube)][oddeven], color_offset));
    if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y) && isCenterCube) {
        pos.y -= 30 * _scale;
        _sprite->setColor(sf::Color::Yellow);
    }
    _sprite->setPosition(pos);
}

void Display::drawUI()
{
    sf::Text text;
    text.setFont(*_font);

    if (_highlightedPlayerNumber != -1) {
        int entityIndex = findEntity(_entities, _highlightedPlayerNumber);
        std::string lvl = std::to_string(_entities[entityIndex]._lvl);
        text.setString(lvl);
        text.setFillColor(sf::Color::Red);
        text.setCharacterSize(100);
        sf::Vector2f selectedPlayerPos = _entities[entityIndex].getPosition();
        sf::IntRect rect;
        rect.left = 183;
        rect.top = 42;
        rect.height = ASSET_HEIGHT;
        rect.width = ASSET_WIDHT;
        sf::Vector2f isometricPos = getIsometricPos(selectedPlayerPos.x, selectedPlayerPos.y, _scale, rect, _x_offset, _y_offset);
        isometricPos.x += 140 * _scale;
        isometricPos.y -= 220 * _scale;
        text.setScale(sf::Vector2f(_scale, _scale));
        text.setPosition(isometricPos);
        _window->draw(text);
    }
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
    text.setScale(1, 1);
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

    if (_notFirstSelect) {
        int entityIndex = findEntity(_entities, _selectedPlayerNumber);
        tile = _entities[entityIndex]._inventory;
        std::sprintf(buffer, "    %d     %d     %d     %d     %d     %d     %d", tile.food, tile.linemate, tile.deraumere, tile.sibur, tile.mendiane, tile.phiras, tile.thystame);
        text.setString(buffer);
        text.setPosition(sf::Vector2f(_uiPlayerPosition.x, _uiPlayerPosition.y + 70));
        _window->draw(text);
    }
}


void Display::drawBroadcast()
{
    size_t size = _broadcasts.size();
    _sprite->setTexture(*_speechTexture);
    _sprite->setTextureRect(sf::IntRect(0, 0, 1012, 558));
    _sprite->setColor(sf::Color::White);
    sf::Text text;
    text.setFont(*_font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(60);
    text.setScale(_scale, _scale);

    for (size_t i = 0; i < size; i++) {
        Broadcast broadcast = _broadcasts[i];
        if (broadcast.frames <= 0)
            continue;
        _broadcasts[i].frames--;
        int entityIndex = findEntity(_entities, broadcast.playerNumber);
        sf::Vector2f selectedPlayerPos = _entities[entityIndex].getPosition();
        sf::IntRect rect;
        rect.left = 183;
        rect.top = 42;
        rect.height = ASSET_HEIGHT;
        rect.width = ASSET_WIDHT;
        sf::Vector2f isometricPos = getIsometricPos(selectedPlayerPos.x, selectedPlayerPos.y, _scale, rect, _x_offset, _y_offset);
        isometricPos.x += 200 * _scale;
        isometricPos.y -= 590 * _scale;
        _sprite->setPosition(isometricPos);
        int offset = int(broadcast.message.length()) - 12;
        double x_scale_push = std::max(0.0, double(offset)) * 0.1 * _scale;
        _sprite->setScale(sf::Vector2f(_scale + x_scale_push, _scale));
        isometricPos.x += 250 * (_scale + x_scale_push);
        isometricPos.y += 180 * _scale;
        text.setPosition(isometricPos);
        text.setString(broadcast.message);
        _window->draw(*_sprite);
        _window->draw(text);
    }
}


void Display::drawEgg()
{
    size_t size = _eggs.size();
    _sprite->setTexture(*_eggTexture);
    _sprite->setTextureRect(sf::IntRect(0, 0, 289, 253));
    _sprite->setScale(_scale * 0.7, _scale * 0.7);
    sf::IntRect rect;
    rect.left = 183;
    rect.top = 42;
    rect.height = ASSET_HEIGHT;
    rect.width = ASSET_WIDHT;
    
    for (size_t i = 0; i < size; i++) {
        Egg egg = _eggs[i];
        if (!egg.display)
            continue;
        sf::Vector2f isometricPos = getIsometricPos(egg.x, egg.y, _scale, rect, _x_offset, _y_offset);
        isometricPos.x += 120 * _scale;
        isometricPos.y -= 0 * _scale;
        if (egg.x == int(_mouseGridCoords.x) && egg.y == int(_mouseGridCoords.y)) {
            isometricPos.y -= 50 * _scale;
        }
        _sprite->setColor(sf::Color(egg.r, egg.g, egg.b, 255));
        _sprite->setPosition(isometricPos);
        _window->draw(*_sprite);
    }
}
