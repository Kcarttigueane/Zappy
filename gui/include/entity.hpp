/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** entity
*/

#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <SFML/System/String.hpp>
#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <sstream>

#define PLAYER_TYPE 0
#define ROCK_TYPE 1
#define DIR_STOP 0
#define DIR_LEFT 1
#define DIR_RIGHT 2
#define DIR_UP 3
#define DIR_DOWN 4

class Entity {
    public:
        Entity(sf::Texture *texture, int entityType) {
            _texture = texture;
            _entityType = entityType;
        }
        void setPosition(float x, float y) {
            _x = x;
            _y = y;
        }
        void setPosition(sf::Vector2f pos) {
            _x = pos.x;
            _y = pos.y;
        }
        void setRect(sf::IntRect rect) {
            _rect = rect;
        }
        sf::Vector2f getPosition() {
            sf::Vector2f pos;
            pos.x = _x;
            pos.y = _y;
            return pos;
        }

        sf::IntRect getRect() {
            return _rect;
        }

        sf::Texture *getTexture() {
            return _texture;
        }

        int getEntityType() {
            return _entityType;
        }

        int _direction = DIR_STOP;
        int _animationPoint = 0;
        int _inverseScale = 1;
    
    protected:
        float _x;
        float _y;
        sf::Texture *_texture;
        sf::IntRect _rect;
        int _entityType;
};