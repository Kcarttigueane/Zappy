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
