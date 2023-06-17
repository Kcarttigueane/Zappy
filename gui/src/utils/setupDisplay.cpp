/*
** EPITECH PROJECT, 2023
** gui
** File description:
** setupDisplay
*/

#include "../../include/display.hpp"

void setupDisplay(Display *display, std::string response)
{
    printf("%s\n", response.c_str());
    display->parseServerInfo(response);
    display->setupTiles();
}