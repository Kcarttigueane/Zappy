/*
** EPITECH PROJECT, 2023
** gui
** File description:
** entities
*/

#include "../../include/display.hpp"

int findEntity(std::vector<Entity> entities, int playerNumber)
{
    size_t size = entities.size();

    for (size_t i = 0; i < size; i++)
        if (entities[i]._playerNumber == playerNumber)
            return i;
    return -1;
}

void Display::entitySelect(Entity *entity, sf::Vector2f *pos)
{
    int x = int(entity->_x + 0.05);
    int y = int(entity->_y + 0.05);

    if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y)) {
        pos->y -= 30 * _scale;
    }

}

void Display::teleportEntity(Entity *e)
{
    if (e->_objX == _mapWidth - 1 && e->_direction == DIR_WEST)
        e->_x = _mapWidth - 1;
    if (e->_objX == 0 && e->_direction == DIR_EAST)
        e->_x = 0;
    if (e->_objY == _mapHeight - 1 && e->_direction == DIR_NORTH)
        e->_y = _mapHeight - 1;
    if (e->_objY == 0 && e->_direction == DIR_SOUTH)
        e->_y = 0;
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

    if (_frame % 5 != 0)
        return;
    rect.width = 168;
    rect.height = 207;
    int top_anim[3] = {271, 271 + 291, 271 + (291 * 2)}; 
    // if (!entity->_move) {
    //     rect.left = 809;
    //     rect.top = 271 + 291;
    //     entity->setRect(rect);
    //     return;
    // }
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
    if (entity->_move)
        entity->_animationPoint += 1;
}


void Display::entityIncantation(Entity *entity)
{
    if (!entity->_incantation) 
        return;
    sf::Color colors[4] = {sf::Color(2, 165, 255, 255), sf::Color(255, 51, 0, 255),
    sf::Color(102, 204, 51, 255), sf::Color(255, 204, 0, 255)};
    _sprite->setColor(colors[entity->_incantationColor % 4]);
    if (_frame % 10 == 0)
        entity->_incantationColor++;
}

#define PLAYER_HEIGHT 207
void Display::drawEntities()
{
    size_t size = _entities.size();
    sf::IntRect rect;
    rect.left = 183;
    rect.top = 42;
    rect.height = ASSET_HEIGHT;
    rect.width = ASSET_WIDHT;

    for (size_t i = 0; i < size; i++) {
        if (_entities[i]._dead)
            _entities[i]._inv -= 2;
        if (_entities[i]._inv <= 0)
            continue;
        moveEntity(&_entities[i]);
        teleportEntity(&_entities[i]);
        animateEntity(&_entities[i]);
        sf::Vector2f ortho_pos = _entities[i].getPosition();
        ortho_pos.y -= 0.5;
        sf::Vector2f pos = getIsometricPos(ortho_pos.x, ortho_pos.y, _scale, rect, _x_offset, _y_offset);
        entitySelect(&_entities[i], &pos);
        sf::Color teamColor = _teamColors[_entities[i]._teamNumb];
        teamColor.a = _entities[i]._inv;
        _sprite->setColor(teamColor);
        entityIncantation(&_entities[i]);
        _sprite->setTexture(*(_entities[i].getTexture()));
        _sprite->setPosition(pos);
        _sprite->setScale(sf::Vector2f(_scale, _scale));
        _sprite->setTextureRect(_entities[i].getRect());
        _window->draw(*_sprite);
        if (_frame % 60 == 0) {
            char buffer[10];
            std::sprintf(buffer, "ppo %d\n", _entities[i]._playerNumber);
            sendData(buffer);
        }
    }
}
