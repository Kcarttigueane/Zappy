/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** main.cpp
*/

#include <cstdlib>
#include "include/client.hpp"
#include "include/gui.hpp"

void handle_client(Client client)
{
    if (client.connectToServer()) {
        std::string response = client.receiveData();
        if (!response.empty())
            std::cout << "Server response: " << response << std::endl;
        std::string message = "GRAPHIC\n";
        if (client.sendData(message)) {
            std::string response = client.receiveData();
            if (!response.empty()) {
                std::cout << "Server response: " << response << std::endl;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "Usage: ./client <server_ip> <server_port>" << std::endl;
        return 1;
    }
    std::string serverIP = argv[1];
    int serverPort = std::stoi(argv[2]);
    Client client(serverIP, serverPort);
    handle_client(client);
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
