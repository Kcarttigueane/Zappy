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
#define SLIDER_OFFSET 1640.0
#define EXTRA_TILES 30
#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black */
#define RED "\033[1;31m"   /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
#define WHITE "\033[37m"   /* White */

class Display {
  public:
    Display(int width_res, int height_res, std::string title)
    {
        _width = width_res;
        _height = height_res;
        _window = new sf::RenderWindow(sf::VideoMode(_width, _height), title);
        _cubeTexture = new sf::Texture;
        _playerTexture = new sf::Texture;
        _uiTexture = new sf::Texture;
        _speechTexture = new sf::Texture;
        _titleTexture = new sf::Texture;
        _eggTexture = new sf::Texture;
        _sideUITexture = new sf::Texture;
        _sprite = new sf::Sprite;
        _cubeSprite = new sf::Sprite;
        _uiSprite = new sf::Sprite;
        _speechSprite = new sf::Sprite;
        _eggSprite = new sf::Sprite;
        _sideUISprite = new sf::Sprite;
        _titleSprite = new sf::Sprite;
        _font = new sf::Font;
        _event = new sf::Event;
        _playerTexture->loadFromFile("./assets/players_scaled.png");
        _eggTexture->loadFromFile("./assets/egg_scaled.png");
        _sideUITexture->loadFromFile("./assets/side_ui.png");
        _cubeTexture->loadFromFile("./assets/white_inv_cube.png");
        _uiTexture->loadFromFile("./assets/custompanel.png");
        _speechTexture->loadFromFile("./assets/speech.png");
        _titleTexture->loadFromFile("./assets/ZAPPY.png");
        _cubeSprite->setTexture(*_cubeTexture);
        _eggSprite->setTexture(*_eggTexture);
        _uiSprite->setTexture(*_uiTexture);
        _titleSprite->setTexture(*_titleTexture);
        _speechSprite->setTexture(*_speechTexture);
        _sideUISprite->setTexture(*_sideUITexture);
        _uiPosition = sf::Vector2f(100, 1080);
        _uiPlayerPosition = sf::Vector2f(100, -200);
        _font->loadFromFile("./assets/font.ttf");
        _cubeSprite->setTextureRect(sf::IntRect(183, 42, ASSET_WIDHT, ASSET_HEIGHT));
        _uiSprite->setTextureRect(
            sf::IntRect(0, 0, _uiTexture->getSize().x, _uiTexture->getSize().y));
        _uiSprite->setScale(0.773, 1.f);
        _uiSprite->setColor(sf::Color::White);
        _speechSprite->setTextureRect(sf::IntRect(0, 0, 1012, 558));
        _speechSprite->setColor(sf::Color(255, 255, 255, 200));
        _eggSprite->setTextureRect(sf::IntRect(0, 0, 289, 253));
        _titleSprite->setPosition(sf::Vector2f(750, 60));
        _titleSprite->setTextureRect(sf::IntRect(0, 0, 415, 146));
        _titleSprite->setScale(sf::Vector2f(1.0, 1.0));
    }

    ~Display()
    {
        delete _window;
        delete _cubeTexture;
        delete _eggTexture;
        delete _playerTexture;
        delete _uiTexture;
        delete _titleTexture;
        delete _speechTexture;
        delete _sideUITexture;
        delete _cubeSprite;
        delete _eggSprite;
        delete _uiSprite;
        delete _titleSprite;
        delete _speechSprite;
        delete _sideUISprite;
        delete _sprite;
        delete _font;
    }

    // Game
    void createIsometricCube(float x, float y, float scale, sf::IntRect rect, bool isCenterCube);
    void drawTileMap();
    void drawEntities();
    void drawUI();
    void drawSlider();
    void drawsideUI();
    void drawWin();
    void drawBroadcast();
    void drawEgg();
    void animateEntity(Entity* entity);
    void moveEntity(Entity* entity);
    void teleportEntity(Entity* entity);
    void entitySelect(Entity* entity, sf::Vector2f* pos);
    void entityIncantation(Entity* entity);
    void handleEvents();
    bool isMapCube(int x, int y);
    void getMousePosition();
    void setupTiles();
    void draw();
    void parseServerInfo(std::string response);

    void checkTotalResources();
    void checkTotalLvls();

    void handleMenu();
    void drawMenu();
    void handleMenuEvents();
    void setupMenu();

    std::string handleClient();
    sf::Color getRandomColor();

    //Thread
    void startClientThread();
    void stopClientThread();
    void setData(std::string newData);
    std::string getData();

    //Client
    bool connectToServer();
    bool sendData(const std::string& data);
    std::string receiveData();
    void threadRecieveData();

    sf::RenderWindow* _window;
    sf::Texture* _cubeTexture;
    sf::Texture* _playerTexture;
    sf::Texture* _uiTexture;
    sf::Texture* _eggTexture;
    sf::Texture* _titleTexture;
    sf::Texture* _speechTexture;
    sf::Texture* _sideUITexture;
    sf::Event* _event;
    sf::Sprite* _speechSprite;
    sf::Sprite* _sprite;
    sf::Sprite* _cubeSprite;
    sf::Sprite* _uiSprite;
    sf::Sprite* _eggSprite;
    sf::Sprite* _sideUISprite;
    sf::Sprite* _titleSprite;
    sf::Font* _font;
    sf::Vector2f _mouseGridCoords;
    bool _tileClicked = false;
    sf::Vector2f _lastClickedCoords;
    sf::Vector2f _uiPosition;
    sf::Vector2f _uiPlayerPosition;
    std::vector<Entity> _entities;
    std::vector<std::string> _teamNames;
    std::vector<sf::Color> _teamColors;
    std::vector<int> _usedColorIndexes;
    int _win = 0;
    int _winAlpha = 0;
    std::string _winningTeam;
    int _displayLoop = 1;
    int _quit = 0;
    int _menuLoop = 1;
    int _timeUnit;
    int _width;
    int _height;
    int _mapWidth;
    int _mapHeight;
    int _uiAnimationPoint = 0;
    int _uiPlayerPoint = 0;
    double _scale = 0.2;
    double _x_offset = 930.0;
    double _y_offset = 400.0;
    sf::Clock _clock;
    sf::Time _deltaTime;
    sf::Time _frameTime = sf::seconds(1.0f / 60.0f);
    sf::Time _animationTime = sf::seconds(0.5f);
    std::vector<Tile> _tiles;
    std::vector<Tile> _tileMovement;
    int _notFirstSelect = 0;
    int _selectedPlayerNumber = 0;
    int _highlightedPlayerNumber = -1;
    std::vector<int> _highlightedPlayerNumbers;
    std::string _data = "";
    int _thread_seen = -1;
    std::mutex _mtx;
    int _nb_calls = 0;
    std::thread _clientThread;
    int clientSocket;
    std::string serverIP;
    int serverPort;
    int _serverTime = 20;
    int _oldServerTime = 20;
    long _frame = 0;
    std::vector<Broadcast> _broadcasts;
    std::vector<Egg> _eggs;

    //Menu
    sf::RectangleShape _inputBoxIP;
    sf::RectangleShape _inputBoxPort;
    sf::RectangleShape _playButton;
    std::string _menuIpString = "";
    std::string _menuPortString = "";
    int _clickedBox = -1;
    std::string _serverResponse = "";
    int _errorServer = 0;

    //UI
    sf::RectangleShape _sliderBackground;
    sf::RectangleShape _sliderFill;
    sf::CircleShape _sliderHandle;
    bool _sliderDrag = false;
    int _sideUIState = 0;
    int _sideUI_x = -245;
    int _totalFood = 0;
    int _totalLinemate = 0;
    int _totalDeraumere = 0;
    int _totalSibur = 0;
    int _totalMendiane = 0;
    int _totalPhiras = 0;
    int _totalThystame = 0;
    int _selectedTeam = 0;
    int _teamTotalPlayers = 0;
    int _teamlvl[8] = {0, 0, 0, 0, 0, 0, 0, 0};
};

sf::Vector2f getGridCoordinates(float x, float y, double scale, double x_offset, double y_offset);
sf::Vector2f getIsometricPos(float x, float y, float scale, sf::IntRect rect, double x_offset,
                             double y_offset);
void setupDisplay(Display* display, std::string response);
std::string getIntFormatedString(int nb, int spaces);
