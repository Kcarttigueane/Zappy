/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** parsing
*/

#include "../../include/display.hpp"


void Display::setupServerInfo(std::string response)
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


void Display::parseServerInfo(std::string res)
{
    std::istringstream iss(res);
    std::string command;
    iss >> command;
    if (command == "pnw") {
        int playerNumber, x, y, orientation, lvl;
        std::string teamName;
        if (iss >> playerNumber >> x >> y >> orientation >> lvl >> teamName) {
            sf::IntRect rect;
            rect.left = 809;
            rect.width = 168;
            rect.height = 207;
            rect.top = 271 + 291;
            Entity player(_playerTexture, playerNumber, x, _mapHeight - y, orientation, lvl, teamName);
            player.setRect(rect);
            _entities.push_back(player);
        }
    } else if (command == "ppo") {
        int playerNumber, x, y, dir;
        if (iss >> playerNumber >> x >> y >> dir) {
            for (size_t i = 0; i < _entities.size(); i++) {
                if (_entities[i]._playerNumber == playerNumber) {
                    _entities[i]._move = 1;
                    _entities[i]._objX = float(x);
                    _entities[i]._objY = float(_mapHeight) - float(y);
                    _entities[i]._direction = dir;
                }
            }
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
