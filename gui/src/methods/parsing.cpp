/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** parsing
*/

#include "../../include/display.hpp"

bool in_range(int a, int b, int dif)
{
    return (a > b - (dif / 2) && a < b + (dif / 2));
}

sf::Color getRandomColor(std::vector<sf::Color> colors)
{
    size_t size = 0;
    int too_close = 1;
    sf::Color color(rand() % 255 + 100, rand() % 255 + 100, rand() % 255 + 100, 255);
    int stop = 0;

    while (too_close && stop < 100) {
        too_close = 0;
        color = sf::Color(rand() % 255 + 100, rand() % 255 + 100, rand() % 255 + 100, 255);
        for (size_t i = 0; i < size; i++)
            if (in_range(color.r, colors[i].r, 50) && in_range(color.r, colors[i].r, 50) && in_range(color.r, colors[i].r, 50))
                too_close = 1;
        stop++;
    }
    return color;
}

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
            while (iss >> name) {
                names.push_back(name);
                _teamColors.push_back(getRandomColor(_teamColors));
            }
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
            Entity player(_playerTexture, playerNumber, x, _mapHeight - y - 1, orientation, lvl, teamName);
            player.setRect(rect);
            for (size_t i = 0; i < _teamNames.size(); i++) {
                if (teamName == _teamNames[i])
                    player._teamNumb = i;
            }
            _entities.push_back(player);
        }
    } else if (command == "ppo") {
        int playerNumber, x, y, dir;
        if (iss >> playerNumber >> x >> y >> dir) {
            for (size_t i = 0; i < _entities.size(); i++) {
                if (_entities[i]._playerNumber == playerNumber) {
                    _entities[i]._move = 1;
                    _entities[i]._objX = float(x);
                    _entities[i]._objY = float(_mapHeight) - float(y) - 1.0;
                    _entities[i]._direction = dir;
                }
            }
        }
    } else if (command == "pdi") {
        int playerNumber;
        if (iss >> playerNumber)
            for (size_t i = 0; i < _entities.size(); i++)
                if (_entities[i]._playerNumber == playerNumber)
                    _entities[i]._dead = 1;
    } else if (command == "pin") {
        int playerNumber, x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame;
        if (iss >> playerNumber >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame) {
            Tile tile;
            tile.food = food;
            tile.linemate = linemate;
            tile.deraumere = deraumere;
            tile.sibur = sibur;
            tile.mendiane = mendiane;
            tile.phiras = phiras;
            tile.thystame = thystame;
            _entities[findEntity(_entities, playerNumber)]._inventory = tile;
            char buffer[50];
            std::sprintf(buffer, "plv %d\n", playerNumber);
            sendData(buffer);
        }
    } else if (command == "plv") {
        int playerNumber, lvl;
        if (iss >> playerNumber >> lvl) {
            for (size_t i = 0; i < _entities.size(); i++)
                if (_entities[i]._playerNumber == playerNumber) {
                    _entities[i]._lvl = lvl;
                    break;
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
