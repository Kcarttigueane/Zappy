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

void Display::parseServerInfo(std::string response)
{
    std::istringstream iss(response);
    std::string line;
    
    while (std::getline(iss, line)) {
        std::istringstream linestream(line);
        std::string command;
        linestream >> command;
        if (command == "msz") {
            int width, height;
            if (linestream >> width >> height) {
                _mapWidth = width;
                _mapHeight = height;
                for (int i = 0; i < _mapWidth; i++)
                    for (int j = 0; j < _mapHeight; j++) {
                        Tile tile = {0, 0, 0, 0, 0, 0, 0, 0, 0.0};
                        _tiles.push_back(tile);
                    }
            }
        } else if (command == "bct") {
            int x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame;
            if (linestream >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame) {
                Tile tile;
                tile.food = food;
                tile.linemate = linemate;
                tile.deraumere = deraumere;
                tile.sibur = sibur;
                tile.mendiane = mendiane;
                tile.phiras = phiras;
                tile.thystame = thystame;
                _tiles[y * _mapWidth + x] = tile;
                checkTotalResources();
            }
        } else if (command == "sgt") {
            // int time;
            // if (linestream >> time && _serverTime == -1) {
            //     _serverTime = time;

            // }
        } else if (command == "tna") {
            std::vector<std::string> names;
            std::string name;
            while (linestream >> name) {
                _teamNames.push_back(name);
                _teamColors.push_back(getRandomColor(_teamColors));
            }
        }
        if (command == "pnw") {
            int playerNumber, x, y, orientation, lvl;
            std::string teamName;
            if (linestream >> playerNumber >> x >> y >> orientation >> lvl >> teamName) {
                sf::IntRect rect;
                rect.left = 809;
                rect.width = 168;
                rect.height = 207;
                rect.top = 271 + 291;
                Entity player(_playerTexture, playerNumber, x, _mapHeight - y - 1, orientation, lvl, teamName);
                player.setRect(rect);
                for (size_t i = 0; i < _teamNames.size(); i++) {
                    if (teamName == _teamNames[i]) {
                        player._teamNumb = i;
                    }
                }
                _entities.push_back(player);
            }
        } else if (command == "ppo") {
            int playerNumber, x, y, dir;
            if (linestream >> playerNumber >> x >> y >> dir) {
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
            if (linestream >> playerNumber) {
                for (size_t i = 0; i < _entities.size(); i++)
                    if (_entities[i]._playerNumber == playerNumber) {
                        _entities[i]._dead = 1;
                        _entities[i]._playerNumber = -1;
                    }
                if (playerNumber == _highlightedPlayerNumber)
                    _highlightedPlayerNumber = -1;
                if (playerNumber == _selectedPlayerNumber) {
                    _selectedPlayerNumber = 0;
                    _notFirstSelect = 0;
                }
            }

        } else if (command == "pin") {
            int playerNumber, x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame;
            if (linestream >> playerNumber >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame) {
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
            if (linestream >> playerNumber >> lvl) {
                for (size_t i = 0; i < _entities.size(); i++)
                    if (_entities[i]._playerNumber == playerNumber) {
                        _entities[i]._lvl = lvl;
                        break;
                    }
            }
        } else if (command == "pbc") {
            int playerNumber;
            std::string message;
            if (linestream >> playerNumber) {
                std::getline(linestream >> std::ws, message);
                Broadcast broadcast = {playerNumber, message, 300};
                _broadcasts.push_back(broadcast);
            }
            
        } else if (command == "enw") {
            int eggNumber, playerNumber, x, y;
            if (linestream >> eggNumber >> playerNumber >> x >> y) {
                int entityIndex = findEntity(_entities, playerNumber);
                sf::Color color = sf::Color::White;
                if (entityIndex != -1)
                    color = _teamColors[_entities[findEntity(_entities, playerNumber)]._teamNumb];
                Egg egg;
                egg.eggNumber = eggNumber;
                egg.x = x;
                egg.y = _mapHeight - y - 1.0;
                egg.r = color.r;
                egg.g = color.g;
                egg.b = color.b;
                _eggs.push_back(egg);
            }
        } else if (command == "ebo" || command == "edi") {
            int eggNumber;
            if (linestream >> eggNumber)
                for (size_t i = 0; i < _eggs.size(); i++)
                    if (_eggs[i].eggNumber == eggNumber)
                        _eggs[i].display = 0;
        } else if (command == "pic") {
            int x, y, lvl, playerNumber;
            if (linestream >> x >> y >> lvl) {
                while (linestream >> playerNumber) {
                    int index = findEntity(_entities, playerNumber);
                    _entities[index]._incantation = 1;
                    char buffer[20];
                    std::sprintf(buffer, "ppo %d\n", _entities[index]._playerNumber);
                    sendData(buffer);
                }
            }
        } else if (command == "pie") {
            int x, y, result;
            if (linestream >> x >> y >> result) {
                y = _mapHeight - y - 1.0;
                for (size_t i = 0; i < _entities.size(); i++) {
                    int player_x = int(_entities[i]._x + 0.05);
                    int player_y = int(_entities[i]._y + 0.05);
                    if (_entities[i]._incantation && player_x == x && player_y == y)
                        _entities[i]._incantation = 0;
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
