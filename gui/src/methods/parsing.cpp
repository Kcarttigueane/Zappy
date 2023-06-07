/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** parsing
*/

#include "../../include/display.hpp"


void Display::setupGame(std::string response)
{
    printf("%s\n", response.c_str());
    std::istringstream iss(response);
    std::string line;

    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::string command;
        lineStream >> command;
        if (command == "msz") {
            int width, height;
            if (lineStream >> width >> height) {
                _mapWidth = width;
                _mapHeight = height;
            }
        } else if (command == "bct") {
            int x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame;
            if (lineStream >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame) {
                Tile tile;
                tile.food = food;
                tile.linemate = linemate;
                tile.deraumere = deraumere;
                tile.sibur = sibur;
                tile.mendiane = mendiane;
                tile.phiras = phiras;
                tile.thystame = thystame;
                _tiles.push_back(tile);
            }
        } else if (command == "tna") {
            std::vector<std::string> names;
            std::string name;
            while (iss >> name)
                names.push_back(name);
            _teamNames = names;
        }
    }

}

void debugTile(Tile tile)
{
    std::cout << "Tile Content:" << std::endl;
    std::cout << "\tFood: " << tile.food << std::endl;
    std::cout << "\tLinemate: " << tile.linemate << std::endl;
    std::cout << "\tDeraumere: " << tile.deraumere << std::endl;
    std::cout << "\tSibur: " << tile.sibur << std::endl;
    std::cout << "\tMendiane: " << tile.mendiane << std::endl;
    std::cout << "\tPhiras: " << tile.phiras << std::endl;
    std::cout << "\tThystame: " << tile.thystame << std::endl;
}
