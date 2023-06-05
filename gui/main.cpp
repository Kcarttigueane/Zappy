/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** main.cpp
*/

#include <cstdlib>
#include "include/gui.hpp"

int main(int argc, char* argv[])
{
    Display display(1920, 1080, "Zappy");

    while (display._displayLoop) {
        display.handleEvents();
        display.draw();
    }
    return EXIT_SUCCESS;
}
