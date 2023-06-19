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
#include <thread>
#include <cmath>
#include <mutex>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <random>
#include <sys/select.h>
#include <fcntl.h>

#include "tile.hpp"
#include "broadcasts.hpp"

#define PLAYER_TYPE 0
#define ROCK_TYPE 1
#define DIR_STOP 0
#define DIR_NORTH 1
#define DIR_EAST 2
#define DIR_SOUTH 3
#define DIR_WEST 4

class Entity {
    public:
        Entity(sf::Texture *texture, int playerNumber, int x, int y, int direction, int lvl, std::string teamName) {
            _texture = texture;
            _playerNumber = playerNumber;
            _x = float(x);
            _y = float(y);
            _objX = _x;
            _objY = _y;
            _direction = direction;
            _lvl = lvl;
            _teamName = teamName;
            Tile tile = {10, 0, 0, 0, 0, 0, 0, 0, 0.0f};
            _inventory = tile;
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

        int _direction = DIR_STOP;
        int _animationPoint = 0;
        int _inverseScale = 1;
        float _x;
        float _y;
        float _objX;
        float _objY;
        int _playerNumber;
        int _lvl = 1;
        size_t _teamNumb = 0;
        int _dead = 0;
        int _move = 0;
        int _inv = 255;
        int _incantation = 0;
        Tile _inventory;
        std::string _teamName;
        sf::Texture *_texture;
        sf::IntRect _rect;
};

int findEntity(std::vector<Entity> entities, int playerNumber);