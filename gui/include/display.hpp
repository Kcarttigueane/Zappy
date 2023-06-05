/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** window
*/

#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <SFML/System/String.hpp>
#include <iostream>
#include <string>

class Display {
    public:
        Display(int width_res, int height_res, std::string title) {
            _width = width_res;
            _height = height_res;
            _window = new sf::RenderWindow(sf::VideoMode(_width, _height), title);
            _texture = new sf::Texture;
            _sprite = new sf::Sprite;
            _font = new sf::Font;
            _text = new sf::Text;
            _event = new sf::Event;
            _texture->loadFromFile("./assets/inv_cube.png");
        }
        ~Display() {
            delete _window;
            delete _texture;
            delete _sprite;
            delete _font;
            delete _text;
        }

        void createIsometricEntity(float x, float y, float scale, sf::Texture *texture, sf::IntRect rect);
        void drawTileMap(int w, int h);
        void handleEvents();
        void handleMouseEvents();
        void draw();

        sf::RenderWindow *_window;
        sf::Texture *_texture;
        sf::Event *_event;
        sf::Sprite *_sprite;
        sf::Font *_font;
        sf::Text *_text;
        sf::Vector2f _mouseGridCoords;
        int _displayLoop = 1;
        int _width;
        int _height;

};
