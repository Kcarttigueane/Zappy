/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** main.cpp
*/

#include <cstdlib>
#include "include/gui.hpp"
#include "include/client.hpp"

std::string handle_client(Client client)
{
    if (client.connectToServer()) {
        std::string response = client.receiveData();
        if (!response.empty())
            std::cout << response << std::endl;
        std::string message = "GRAPHIC\n";
        if (client.sendData(message)) {
            std::string response = client.receiveData();
            if (!response.empty()) {
                return response;
            }
        }
    }
    return nullptr;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "Usage: ./client <server_ip> <server_port>" << std::endl;
        return 1;
    }
    // Handle Client
    std::string serverIP = argv[1];
    int serverPort = std::stoi(argv[2]);
    Client client(serverIP, serverPort);
    std::string response = handle_client(client);

    //set up display
    Display display(1920, 1080, "Zappy");
    display.setupServerInfo(response);
    display.setupTiles();
    Entity player(display._playerTexture, PLAYER_TYPE);
    sf::IntRect rect;
    rect.left = 757;
    rect.top = 24;
    rect.width = 192;
    rect.height = 347;
    player.setRect(rect);
    player.setPosition(0, 0);
    display._entities.push_back(player);

    // display loop
    while (display._displayLoop) {
        display._deltaTime = display._clock.restart();
        display.handleEvents();
        display.draw();
        sf::Time elapsedTime = display._clock.getElapsedTime();
        if (elapsedTime < display._frameTime)
            sf::sleep(display._frameTime - elapsedTime);
        // std::string response = client.receiveData();
        // if (!response.empty()) {
        //     printf("%s\n", response.c_str());
        // }
    }
    return EXIT_SUCCESS;
}
