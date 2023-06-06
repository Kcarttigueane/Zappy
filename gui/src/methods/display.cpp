/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** display
*/

#include "../../include/display.hpp"


void Display::draw()
{
    sf::Color skyColor(135, 206, 235, 255);
    _window->clear(skyColor);
    drawTileMap(15, 15);
    drawEntities();
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
            createIsometricCube(i, j, _scale, _cubeTexture, rect);
            _window->draw(*_sprite);
        }
    }
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

void Display::createIsometricCube(float x, float y, float scale, sf::Texture *texture, sf::IntRect rect)
{
    sf::Vector2f pos = getIsometricPos(x, y, scale, rect, _x_offset, _y_offset);
    int type = (int(x) + int(y)) % 2;
    sf::Color colors[2] = {sf::Color(124, 252, 0, 255), sf::Color(50, 205, 0, 255)};
    
    _sprite->setColor(colors[type]);
    if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y)) {
        pos.y -= 30 * _scale;
        _sprite->setColor(sf::Color::Yellow);
    }
    _sprite->setTexture(*texture);
    _sprite->setPosition(pos);
    _sprite->setScale(sf::Vector2f(scale, scale));
    _sprite->setTextureRect(rect);
}
