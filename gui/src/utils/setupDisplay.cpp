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
}