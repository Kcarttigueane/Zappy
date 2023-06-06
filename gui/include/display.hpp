/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** window
*/

#pragma once

#include "entity.hpp"

#define ASSET_WIDHT 444
#define ASSET_HEIGHT 498
#define SCALE 0.2
#define ISOMETRIC_X_OFFSET 930.0
#define ISOMETRIC_Y_OFFSET 400.0
class Display {
    public:
        Display(int width_res, int height_res, std::string title) {
            _width = width_res;
            _height = height_res;
            _window = new sf::RenderWindow(sf::VideoMode(_width, _height), title);
            _cubeTexture = new sf::Texture;
            _playerTexture = new sf::Texture;
            _sprite = new sf::Sprite;
            _font = new sf::Font;
            _text = new sf::Text;
            _event = new sf::Event;
            _playerTexture->loadFromFile("./assets/player_inv.png");
            _cubeTexture->loadFromFile("./assets/inv_cube.png");
        }
        ~Display() {
            delete _window;
            delete _cubeTexture;
            delete _playerTexture;
            delete _sprite;
            delete _font;
            delete _text;
        }

        void createIsometricCube(float x, float y, float scale, sf::Texture *texture, sf::IntRect rect);
        void drawTileMap(int w, int h);
        void drawEntities();
        void animateEntity(Entity *entity);
        void handleEvents();
        void getMousePosition();
        void draw();

        sf::RenderWindow *_window;
        sf::Texture *_cubeTexture;
        sf::Texture *_playerTexture;
        sf::Event *_event;
        sf::Sprite *_sprite;
        sf::Font *_font;
        sf::Text *_text;
        sf::Vector2f _mouseGridCoords;
        std::vector<Entity> _entities;
        int _displayLoop = 1;
        int _width;
        int _height;
        double _scale = 0.2;
        double _x_offset = 930.0;
        double _y_offset = 400.0;
        sf::Clock clock;
        sf::Time deltaTime;
        sf::Time frameTime = sf::seconds(1.0f / 60.0f);
};


sf::Vector2f getGridCoordinates(float x, float y, double scale, double x_offset, double y_offset);
sf::Vector2f getIsometricPos(float x, float y, float scale, sf::IntRect rect, double x_offset, double y_offset);