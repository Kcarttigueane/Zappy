/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** main.cpp
*/

#include <cstdlib>
#include "include/gui.hpp"

#define USAGE_MESSAGE "USAGE: ./zappy_ai port machine\n" \
                      "\tport is the port number\n" \
                      "\tmachine is the name of the machine; localhost by default\n"

int main(int argc, char* argv[])
{
    if (argc == 2 && !strcmp("-h", argv[1])) {
        printf(USAGE_MESSAGE);
        return EXIT_SUCCESS;
    }

    srand(time(NULL));
    Display display(1920, 1080, "Zappy");
    display._deltaTime = display._clock.restart();
    display.setupMenu();

    if (argc != 3) {
        display.handleMenu();
    } else {
        display._menuIpString = argv[1];
        display._menuPortString = argv[2];
        display.handleMenu();
    }
    if (display._quit)
        return EXIT_SUCCESS;
    //set up display
    setupDisplay(&display, display._serverResponse);

    // display loop
    display.startClientThread();
    gameLoop(&display);
    display.stopClientThread();
    return EXIT_SUCCESS;
}
