/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** display
*/

#include "../../include/display.hpp"


void Display::draw()
{
    _window->clear(sf::Color(0, 50, 70));
    drawTileMap();
    drawEgg();
    drawEntities();
    drawBroadcast();
    drawSlider();
    drawUI();
    drawsideUI();
    drawWin();
    _window->display();
}

void Display::drawTileMap()
{
    sf::IntRect rect;
    rect.left = 183;
    rect.top = 42;
    rect.height = ASSET_HEIGHT;
    rect.width = ASSET_WIDHT;

    _cubeSprite->setScale(sf::Vector2f(_scale, _scale));

    for (int i = -EXTRA_TILES; i < EXTRA_TILES + _mapWidth; i++) {
        for (int j = -EXTRA_TILES; j < EXTRA_TILES + _mapHeight; j++) {
            createIsometricCube(i, j, _scale, rect, isMapCube(i, j));
            _window->draw(*_cubeSprite);
        }
    }
}

bool Display::isMapCube(int x, int y)
{
    return x >= 0 && x < _mapWidth && y >= 0 && y < _mapHeight;
}

#define WAVE_FREQ 0.02
#define TIME_INCREMENT 3.9
#define OFFSET_SCALE 100
#define DENOMINATOR 1.2

sf::Color color_multi(sf::Color color, double scalar)
{
    return sf::Color(color.r * scalar, color.g * scalar, color.b * scalar);
}

void Display::createIsometricCube(float x, float y, float scale, sf::IntRect rect, bool isCenterCube)
{
    sf::Vector2f pos = getIsometricPos(x, y, scale, rect, _x_offset, _y_offset);
    int oddeven = (int(std::abs(x)) + int(std::abs(y))) % 2;
    sf::Color colors[2][2] = {{sf::Color(0, 84, 118), sf::Color(0, 84, 118)}, {sf::Color(124, 252, 0, 255), sf::Color(50, 205, 0, 255)}};
    float color_offset = 1;
    
    if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y) && isCenterCube) {
        pos.y -= 30 * _scale;
        _cubeSprite->setColor(sf::Color::Yellow);
    }
    if (!isCenterCube) {
        Tile tile = _tileMovement[(int(y) + EXTRA_TILES) * (EXTRA_TILES * 2 + 1) + (int(x) + EXTRA_TILES)];
        float t = _frame * TIME_INCREMENT;
        tile.offset = sin((x / DENOMINATOR) + WAVE_FREQ * t) + cos((y / DENOMINATOR) + WAVE_FREQ * t);
        color_offset = std::min(((-tile.offset + 2.0) / 2.0) * 0.15 + 0.8, 1.0);
        tile.offset *= OFFSET_SCALE;
        pos.y += (tile.offset * _scale) + 20;
    }   
    _cubeSprite->setColor(color_multi(colors[int(isCenterCube)][oddeven], color_offset));
    if (int(x) == int(_mouseGridCoords.x) && int(y) == int(_mouseGridCoords.y) && isCenterCube) {
        pos.y -= 30 * _scale;
        _cubeSprite->setColor(sf::Color::Yellow);
    }
    _cubeSprite->setPosition(pos);
}

void Display::drawUI()
{
    sf::Text text;
    text.setFont(*_font);

    if (_highlightedPlayerNumbers.size() != 0) {
        std::string lvl;
        std::string totalLvl = "";
        int entityIndex;
        for (size_t i = 0; i < _highlightedPlayerNumbers.size(); i++) {
            entityIndex = findEntity(_entities, _highlightedPlayerNumbers[i]);
            lvl = std::to_string(_entities[entityIndex]._lvl);
            totalLvl += lvl + " ";
        }
        text.setString(totalLvl);
        text.setFillColor(sf::Color::Red);
        text.setCharacterSize(100);
        sf::Vector2f selectedPlayerPos = _entities[entityIndex].getPosition();
        sf::IntRect rect;
        rect.left = 183;
        rect.top = 42;
        rect.height = ASSET_HEIGHT;
        rect.width = ASSET_WIDHT;
        sf::Vector2f isometricPos = getIsometricPos(selectedPlayerPos.x, selectedPlayerPos.y, _scale, rect, _x_offset, _y_offset);
        float x_offset = ((totalLvl.length() / 2) - 1) * 100;
        isometricPos.x += (140.f - x_offset) * _scale;
        isometricPos.y -= 300.f * _scale;
        text.setScale(sf::Vector2f(_scale, _scale));
        text.setPosition(isometricPos);
        _window->draw(text);
    }
    //Tile ui
    _uiSprite->setPosition(_uiPosition);
    if (_uiAnimationPoint && _uiPosition.y > 800)
        _uiPosition.y -= 10;
    if (!_uiAnimationPoint && _uiPosition.y < 1080)
        _uiPosition.y += 10;;
    _window->draw(*_uiSprite);

    char buffer[100];
    Tile tile = _tiles[(_mapHeight - int(_lastClickedCoords.y) - 1) * _mapWidth + int(_lastClickedCoords.x)];
    std::sprintf(buffer, "    %d     %d     %d     %d     %d     %d     %d", tile.food, tile.linemate, tile.deraumere, tile.sibur, tile.mendiane, tile.phiras, tile.thystame);
    text.setScale(1, 1);
    text.setString(buffer);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(40);
    text.setPosition(sf::Vector2f(_uiPosition.x, _uiPosition.y + 70));
    _window->draw(text);

    //Player UI
    if (_uiPlayerPoint && _uiPlayerPosition.y < 50)
        _uiPlayerPosition.y += 10;
    if (!_uiPlayerPoint && _uiPlayerPosition.y > -200)
        _uiPlayerPosition.y -= 10;
    _uiSprite->setPosition(_uiPlayerPosition);
    _window->draw(*_uiSprite);

    if (_notFirstSelect) {
        int entityIndex = findEntity(_entities, _selectedPlayerNumber);
        tile = _entities[entityIndex]._inventory;
        std::sprintf(buffer, "    %s%s%s%s%s%s%s", getIntFormatedString(tile.food, 5).c_str(), getIntFormatedString(tile.linemate, 5).c_str(), getIntFormatedString(tile.deraumere, 5).c_str(), getIntFormatedString(tile.sibur, 5).c_str(), getIntFormatedString(tile.mendiane, 5).c_str(), getIntFormatedString(tile.phiras, 5).c_str(), getIntFormatedString(tile.thystame, 5).c_str());
        // std::sprintf(buffer, "    %d     %d     %d     %d     %d     %d     %d", tile.food, tile.linemate, tile.deraumere, tile.sibur, tile.mendiane, tile.phiras, tile.thystame);
        text.setString(buffer);
        text.setPosition(sf::Vector2f(_uiPlayerPosition.x, _uiPlayerPosition.y + 70));
        if (_frame % 15 == 0) {
            std::sprintf(buffer, "pin %d\n", _selectedPlayerNumber);
            sendData(buffer);
        }
        _window->draw(text);
    }
}


void Display::drawBroadcast()
{
    size_t size = _broadcasts.size();
    sf::Text text;
    text.setFont(*_font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(60);
    text.setScale(_scale, _scale);

    for (size_t i = 0; i < size; i++) {
        Broadcast broadcast = _broadcasts[i];
        if (broadcast.frames <= 0)
            continue;
        _broadcasts[i].frames--;
        int entityIndex = findEntity(_entities, broadcast.playerNumber);
        sf::Vector2f selectedPlayerPos = _entities[entityIndex].getPosition();
        sf::IntRect rect;
        rect.left = 183;
        rect.top = 42;
        rect.height = ASSET_HEIGHT;
        rect.width = ASSET_WIDHT;
        sf::Vector2f isometricPos = getIsometricPos(selectedPlayerPos.x, selectedPlayerPos.y, _scale, rect, _x_offset, _y_offset);
        isometricPos.x += 200 * _scale;
        isometricPos.y -= 590 * _scale;
        _speechSprite->setPosition(isometricPos);
        int offset = int(broadcast.message.length()) - 12;
        double x_scale_push = std::max(0.0, double(offset)) * 0.1 * _scale;
        _speechSprite->setScale(sf::Vector2f(_scale + x_scale_push, _scale));
        isometricPos.x += 250 * (_scale + x_scale_push);
        isometricPos.y += 180 * _scale;
        text.setPosition(isometricPos);
        text.setString(broadcast.message);
        _speechSprite->setColor(sf::Color(255, 255, 255, 120));
        _window->draw(*_speechSprite);
        _window->draw(text);
    }
}


void Display::drawEgg()
{
    size_t size = _eggs.size();
    _eggSprite->setScale(_scale * 0.7, _scale * 0.7);
    sf::IntRect rect;
    rect.left = 183;
    rect.top = 42;
    rect.height = ASSET_HEIGHT;
    rect.width = ASSET_WIDHT;
    
    for (size_t i = 0; i < size; i++) {
        Egg egg = _eggs[i];
        if (!egg.display)
            continue;
        sf::Vector2f isometricPos = getIsometricPos(egg.x, egg.y, _scale, rect, _x_offset, _y_offset);
        isometricPos.x += 120 * _scale;
        isometricPos.y -= 0 * _scale;
        if (egg.x == int(_mouseGridCoords.x) && egg.y == int(_mouseGridCoords.y)) {
            isometricPos.y -= 50 * _scale;
        }
        _eggSprite->setColor(sf::Color(egg.r, egg.g, egg.b, 255));
        _eggSprite->setPosition(isometricPos);
        _window->draw(*_eggSprite);
    }
}

void Display::drawSlider()
{
    _window->draw(_sliderBackground);
    _window->draw(_sliderFill);
    _window->draw(_sliderHandle);
    sf::Text text;
    text.setFont(*_font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(15);
    if (_sliderDrag) {
        sf::Vector2f handlePos = _sliderHandle.getPosition();
        handlePos.y -= 30.f;
        text.setPosition(handlePos);
        std::string val = std::to_string(_serverTime);
        text.setString(val);
        _window->draw(text);
    }
    text.setPosition(SLIDER_OFFSET + 15.0, 430.f);
    text.setString("Server Time");
    _window->draw(text);
}

void Display::drawsideUI()
{
    sf::IntRect rects[2] = {sf::IntRect(0, 0, 320, 1080), sf::IntRect(320, 0, 320, 1080)};
    _sideUISprite->setTextureRect(rects[_sideUIState]);
    _sideUISprite->setPosition(sf::Vector2f(_sideUI_x, 0));
    _window->draw(*_sideUISprite);

    sf::Text text;
    text.setFont(*_font);
    text.setCharacterSize(13);
    text.setPosition(float(_sideUI_x) + 60.f, 210.f);
    text.setFillColor(sf::Color::Black);
    text.setString("Map Info");
    _window->draw(text);
    text.setCharacterSize(13);
    text.setPosition(float(_sideUI_x) + 20.f, 240.f);
    char buffer[200];
    std::sprintf(buffer, "    W: %d\n\n    H: %d\n\n\n\nTotal Resources:\n\n  Food      %d\n\n  Linemate  %d\n\n  Deraumere %d\n\n  Sibur     %d\n\n  Mendiane  %d\n\n  Phiras    %d\n\n  Thystame  %d"
    , _mapWidth, _mapHeight, _totalFood, _totalLinemate, _totalDeraumere, _totalSibur, _totalMendiane, _totalPhiras, _totalThystame);
    text.setString(buffer);
    _window->draw(text);


    if (int(_teamColors.size()) >= _selectedTeam + 1) {
        text.setFillColor(_teamColors[_selectedTeam]);
        text.setPosition(float(_sideUI_x) + 20.f, 550.f);
        std::sprintf(buffer, "  Team %s", _teamNames[_selectedTeam].c_str());
        text.setString(buffer);
        _window->draw(text);
        text.setFillColor(sf::Color::Black);
        text.setPosition(float(_sideUI_x) + 20.f, 580.f);
        std::sprintf(buffer, "Total players: %d\n\n  Lvl 1: %d\n\n  Lvl 2: %d\n\n  Lvl 3: %d\n\n  Lvl 4: %d\n\n  Lvl 5: %d\n\n  Lvl 6: %d\n\n  Lvl 7: %d\n\n  Lvl 8: %d\n\n\n<-Toggle Teams->", _teamTotalPlayers, _teamlvl[0], _teamlvl[1], _teamlvl[2], _teamlvl[3], _teamlvl[4], _teamlvl[5], _teamlvl[6], _teamlvl[7]);
        text.setString(buffer);
        _window->draw(text);
    }
    //\n\nTotal players: %d\n\n  Lvl 1: %d\n\n  Lvl 2: %d\n\n  Lvl 3: %d\n\n  Lvl 4: %d\n\n  Lvl 5: %d\n\n  Lvl 6: %d\n\n  Lvl 7: %d\n\n  Lvl 8: %d\n\n\n<-Toggle Teams->
    if (_sideUIState == 0 && _sideUI_x > -245) {
        _sideUI_x -= 10;
        if (_sideUI_x < -245)
            _sideUI_x = -245;
    }
    if (_sideUIState == 1 && _sideUI_x < 0) {
        _sideUI_x += 10;
        if (_sideUI_x > 0)
            _sideUI_x = 0;
    }
}


void Display::drawWin()
{
    if (_win) {
        sf::RectangleShape rect(sf::Vector2f(1920.f, 1080.f));
        rect.setFillColor(sf::Color(0, 0, 0, _winAlpha));
        rect.setPosition(0, 0);
        _window->draw(rect);
        sf::Text text;
        text.setFont(*_font);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(50);
        text.setPosition(sf::Vector2f(600.f, 400.f));
        char buffer[50];
        std::sprintf(buffer, "%s's Team Wins!", _winningTeam.c_str());
        text.setString(buffer);
        _window->draw(text);
        if (_winAlpha < 150)
            _winAlpha += 5;
        if (_winAlpha > 150)
            _winAlpha = 150;
    }
}
