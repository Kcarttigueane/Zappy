/*
** EPITECH PROJECT, 2023
** gui
** File description:
** entities
*/

#include "../../include/display.hpp"

void Display::entitySelect(Entity *entity, sf::Vector2f *pos)
{
    int x = int(entity->_x);
    int y = int(entity->_y);

    if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y)) {
        pos->y -= 30 * _scale;
    }
}

void Display::moveEntity(Entity *entity)
{
    int move = 0;
    if (entity->_objX > entity->_x) {
        entity->_x += 0.05;
        move += 1;
    }
    if (entity->_objX < entity->_x) {
        entity->_x -= 0.05;
        move += -1;
    }
    if (entity->_objY > entity->_y) {
        entity->_y += 0.05;
        move += -2;
    }
    if (entity->_objY < entity->_y) {
        entity->_y -= 0.05;
        move += 2;
    }
    if (!move)
        entity->_move = 0;
}

void Display::animateEntity(Entity *entity)
{
    sf::IntRect rect;

    if (_frame % 15 != 0)
        return;
    rect.width = 168;
    rect.height = 207;
    int top_anim[3] = {271, 271 + 291, 271 + (291 * 2)}; 
    if (!entity->_move) {
        rect.left = 809;
        rect.top = 271 + 291;
        entity->setRect(rect);
        return;
    }
    if (entity->_direction == DIR_SOUTH) {
        rect.left = 1010;
    } else if (entity->_direction == DIR_NORTH) {
        rect.left = 210;
    } else if (entity->_direction == DIR_WEST) {
        rect.left = 1417;
    } else if (entity->_direction == DIR_EAST) {
        rect.left = 612;
    }
    rect.top = top_anim[entity->_animationPoint % 3];
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
        moveEntity(&_entities[i]);
        animateEntity(&_entities[i]);
        sf::Vector2f ortho_pos = _entities[i].getPosition();
        ortho_pos.y -= 0.5;
        sf::Vector2f pos = getIsometricPos(ortho_pos.x, ortho_pos.y, _scale, rect, _x_offset, _y_offset);
        entitySelect(&_entities[i], &pos);
        _sprite->setColor(sf::Color::White);
        _sprite->setTexture(*(_entities[i].getTexture()));
        _sprite->setPosition(pos);
        _sprite->setScale(sf::Vector2f(_scale, _scale));
        _sprite->setTextureRect(_entities[i].getRect());
        _window->draw(*_sprite);
    }
}