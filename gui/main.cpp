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

    Entity player(display._playerTexture, PLAYER_TYPE);
    sf::IntRect rect;
    rect.left = 757;
    rect.top = 24;
    rect.width = 192;
    rect.height = 347;
    player.setRect(rect);
    player.setPosition(0, 0);
    display._entities.push_back(player);

    while (display._displayLoop) {
        display.deltaTime = display.clock.restart();
        display.handleEvents();
        display.draw();
        sf::Time elapsedTime = display.clock.getElapsedTime();
        if (elapsedTime < display.frameTime)
            sf::sleep(display.frameTime - elapsedTime);
    }
    return EXIT_SUCCESS;
}
