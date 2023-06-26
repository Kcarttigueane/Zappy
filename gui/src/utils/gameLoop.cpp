/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gameLoop
*/

#include "../../include/gui.hpp"

void gameLoop(Display* display)
{
    std::string old_data;

    while (display->_displayLoop) {
        std::string serverData = display->getData();
        if (serverData != old_data) {
            old_data = serverData;
            std::cout << RED << serverData << RESET << std::endl;
            display->parseServerInfo(serverData);
        }
        display->_deltaTime = display->_clock.restart();
        display->handleEvents();
        display->draw();
        sf::Time elapsedTime = display->_clock.getElapsedTime();
        if (elapsedTime < display->_frameTime)
            sf::sleep(display->_frameTime - elapsedTime);
        display->_frame++;
    }
    display->sendData("BAD_COMMAND\n");
}
