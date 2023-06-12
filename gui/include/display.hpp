/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** window
*/

#pragma once

#include "entity.hpp"
#include "tile.hpp"

#define ASSET_WIDHT 444
#define ASSET_HEIGHT 498
#define SCALE 0.2
#define ISOMETRIC_X_OFFSET 930.0
#define ISOMETRIC_Y_OFFSET 400.0
#define EXTRA_TILES 50
class Display {
    public:
        Display(int width_res, int height_res, std::string title) {
            _width = width_res;
            _height = height_res;
            _window = new sf::RenderWindow(sf::VideoMode(_width, _height), title);
            _cubeTexture = new sf::Texture;
            _playerTexture = new sf::Texture;
            _uiTexture = new sf::Texture;
            _sprite = new sf::Sprite;
            _font = new sf::Font;
            _event = new sf::Event;
            _playerTexture->loadFromFile("./assets/players_scaled.png");
            _cubeTexture->loadFromFile("./assets/white_inv_cube.png");
            _uiTexture->loadFromFile("./assets/custompanel.png");
            _uiPosition = sf::Vector2f(100, 1080);
            _font->loadFromFile("./assets/font.ttf");
        }
        ~Display() {
            delete _window;
            delete _cubeTexture;
            delete _playerTexture;
            delete _uiTexture;
            delete _sprite;
            delete _font;
        }

        // Game
        void createIsometricCube(float x, float y, float scale, sf::Texture *texture, sf::IntRect rect, bool isCenterCube);
        void drawTileMap();
        void drawEntities();
        void drawUI();
        void animateEntity(Entity *entity);
        void moveEntity(Entity *entity);
        void entitySelect(Entity *entity, sf::Vector2f *pos);
        void handleEvents();
        bool isMapCube(int x, int y);
        void getMousePosition();
        void setupTiles();
        void setupServerInfo(std::string response);
        void draw();
        void parseServerInfo(std::string response);

        //Thread
        void startClientThread();
        void stopClientThread();
        void setData(std::string newData);
        std::string getData();


        //Client
        bool connectToServer();
        bool sendData(const std::string &data);
        std::string receiveData();
        void threadRecieveData();

        sf::RenderWindow *_window;
        sf::Texture *_cubeTexture;
        sf::Texture *_playerTexture;
        sf::Texture *_uiTexture;
        sf::Event *_event;
        sf::Sprite *_sprite;
        sf::Font *_font;
        sf::Vector2f _mouseGridCoords;
        bool _tileClicked = false;
        sf::Vector2f _lastClickedCoords;
        sf::Vector2f _uiPosition;
        std::vector<Entity> _entities;
        std::vector<std::string> _teamNames;
        int _displayLoop = 1;
        int _timeUnit;
        int _width;
        int _height;
        int _mapWidth;
        int _mapHeight;
        int _uiAnimationPoint = 0;
        double _scale = 0.2;
        double _x_offset = 930.0;
        double _y_offset = 400.0;
        sf::Clock _clock;
        sf::Time _deltaTime;
        sf::Time _frameTime = sf::seconds(1.0f / 60.0f);
        sf::Time _animationTime = sf::seconds(0.5f);
        std::vector<Tile> _tiles;
        std::vector<Tile> _tileMovement;
        std::string _data = "";
        std::mutex _mtx;
        int _nb_calls = 0;
        std::thread _clientThread;
        int clientSocket;
        std::string serverIP;
        int serverPort;
        long _frame = 0;
};


sf::Vector2f getGridCoordinates(float x, float y, double scale, double x_offset, double y_offset);
sf::Vector2f getIsometricPos(float x, float y, float scale, sf::IntRect rect, double x_offset, double y_offset);
void setupDisplay(Display *display, std::string response);