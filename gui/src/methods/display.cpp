/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** display
*/

#include "../../include/display.hpp"


void Display::draw()
{
    // sf::Color skyColor(135, 206, 235, 255);
    _window->clear(sf::Color(12, 79, 106));
    drawTileMap(_mapWidth, _mapHeight);
    drawEntities();
    drawUI();
    _window->display();
}

void Display::drawTileMap(int width, int height)
{
    sf::IntRect rect;
    rect.left = 183;
    rect.top = 42;
    rect.height = ASSET_HEIGHT;
    rect.width = ASSET_WIDHT;

    for (int i = -EXTRA_TILES; i < EXTRA_TILES; i++) {
        for (int j = -EXTRA_TILES; j < EXTRA_TILES; j++) {
            createIsometricCube(i, j, _scale, _cubeTexture, rect, isMapCube(i, j));
            _window->draw(*_sprite);
        }
    }
}

bool Display::isMapCube(int x, int y)
{
    return x >= 0 && x < _mapWidth && y >= 0 && y < _mapHeight;
}

void Display::animateEntity(Entity *entity)
{
    sf::IntRect rect;

    if (entity->getEntityType() == PLAYER_TYPE) {
        rect.width = 192;
        rect.height = 347;
        int frontLefts[3] = {785, 508, 195};
        int backLefts[3] = {1682, 1368, 1062};
        if (entity->_direction == DIR_STOP)
            return;
        rect.top = 396;
        entity->_inverseScale = 1;
        if (entity->_direction == DIR_DOWN) {
            rect.left = frontLefts[entity->_animationPoint % 3];
        } else if (entity->_direction == DIR_UP) {
            rect.left = backLefts[entity->_animationPoint % 3];
            entity->_inverseScale = -1;
        } else if (entity->_direction == DIR_LEFT) {
            rect.left = backLefts[entity->_animationPoint % 3];
        } else if (entity->_direction == DIR_RIGHT) {
            rect.left = frontLefts[entity->_animationPoint % 3];
            entity->_inverseScale = -1;
        }
    }
    entity->setRect(rect);
    entity->_animationPoint += 1;
}

void Display::drawEntities()
{
    size_t size = _entities.size();
    sf::IntRect rect;
    rect.left = 183;
    rect.top = 42;
    rect.height = ASSET_HEIGHT;
    rect.width = ASSET_WIDHT;

    for (size_t i = 0; i < size; i++) {
        animateEntity(&_entities[i]);
        sf::Vector2f ortho_pos = _entities[i].getPosition();
        ortho_pos.x -= 0.7;
        ortho_pos.y -= 1.2;
        sf::Vector2f pos = getIsometricPos(ortho_pos.x, ortho_pos.y, _scale, rect, _x_offset, _y_offset);
        _sprite->setColor(sf::Color::White);
        _sprite->setTexture(*(_entities[i].getTexture()));
        _sprite->setPosition(pos);
        _sprite->setScale(sf::Vector2f(_scale * _entities[i]._inverseScale, _scale));
        _sprite->setTextureRect(_entities[i].getRect());
        _window->draw(*_sprite);
    }
}

void Display::createIsometricCube(float x, float y, float scale, sf::Texture *texture, sf::IntRect rect, bool isCenterCube)
{
    sf::Vector2f pos = getIsometricPos(x, y, scale, rect, _x_offset, _y_offset);
    int oddeven = (int(std::abs(x)) + int(std::abs(y))) % 2;
    sf::Color colors[2][2] = {{sf::Color(0, 105, 148), sf::Color(0, 84, 118)}, {sf::Color(124, 252, 0, 255), sf::Color(50, 205, 0, 255)}};
    
    _sprite->setColor(colors[int(isCenterCube)][oddeven]);
    if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y) && isCenterCube) {
        pos.y -= 30 * _scale;
        _sprite->setColor(sf::Color::Yellow);
    }
    if (!isCenterCube) {
        Tile tile = _tileMovement[(int(y) + EXTRA_TILES) * (EXTRA_TILES * 2 + 1) + (int(x) + EXTRA_TILES)];
        if (tile.direction == UP) {
            if (tile.offset >= 300)
                tile.direction = DOWN;
            else
                tile.offset += 12;
        } else {
            if (tile.offset <= -50)
                tile.direction = UP;
            else
                tile.offset -= 12;
        }
        _tileMovement[(int(y) + EXTRA_TILES) * (EXTRA_TILES * 2 + 1) + (int(x) + EXTRA_TILES)] = tile;
        pos.y += tile.offset * _scale;
    }
    _sprite->setTexture(*texture);
    _sprite->setPosition(pos);
    _sprite->setScale(sf::Vector2f(scale, scale));
    _sprite->setTextureRect(rect);
}

void Display::drawUI()
{
    sf::Vector2u size = _uiTexture->getSize();
    _sprite->setTexture(*_uiTexture);
    _sprite->setTextureRect(sf::IntRect(0, 0, size.x, size.y));
    _sprite->setScale(0.773, 1);
    _sprite->setPosition(_uiPosition);
    if (_uiAnimationPoint && _uiPosition.y > 800)
        _uiPosition.y -= 10;
    if (!_uiAnimationPoint && _uiPosition.y < 1080)
        _uiPosition.y += 10;;
    _window->draw(*_sprite);

    char buffer[100];
    Tile tile = _tiles[int(_lastClickedCoords.y) * _mapWidth + int(_lastClickedCoords.x)];
    std::sprintf(buffer, "    %d     %d     %d     %d     %d     %d     %d", tile.food, tile.linemate, tile.deraumere, tile.sibur, tile.mendiane, tile.phiras, tile.thystame);
    sf::Text text;
    text.setFont(*_font);
    text.setString(buffer);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(40);
    text.setPosition(sf::Vector2f(_uiPosition.x, _uiPosition.y + 70));
    _window->draw(text);
}