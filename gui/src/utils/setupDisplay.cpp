/*
** EPITECH PROJECT, 2023
** gui
** File description:
** setupDisplay
*/

#include "../../include/display.hpp"

void setupDisplay(Display *display, std::string response)
{
    display->setupServerInfo(response);
    display->setupTiles();
    Tile noTile;
    noTile.deraumere = -1;
    display->_playerTile = noTile;
    // Entity player(display->_playerTexture, PLAYER_TYPE);
    // sf::IntRect rect;
    // rect.left = 757;
    // rect.top = 24;
    // rect.width = 192;
    // rect.height = 347;
    // player.setRect(rect);
    // player.setPosition(0, 0);
    // display->_entities.push_back(player);
}