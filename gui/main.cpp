/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** main.cpp
*/

#include <cstdlib>
#include "include/gui.hpp"

std::string handle_client(Display *client)
{
    if (client->connectToServer()) {
        std::string response = client->receiveData();
        if (!response.empty())
            std::cout << response << std::endl;
        std::string message = "GRAPHIC\n";
        if (client->sendData(message)) {
            std::string response = client->receiveData();
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
    Display display(1920, 1080, "Zappy");

    // Handle Client
    std::string serverIP = argv[1];
    int serverPort = std::stoi(argv[2]);
    display.serverIP = serverIP;
    display.serverPort = serverPort;
    std::string response = handle_client(&display);

    //set up display
    setupDisplay(&display, response);

    display._deltaTime = display._clock.restart();
    // display loop
    display.startClientThread();
    gameLoop(&display);
    display.stopClientThread();
    return EXIT_SUCCESS;
}
