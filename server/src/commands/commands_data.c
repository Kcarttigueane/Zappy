/*
** EPITECH PROJECT, 2022
** server
** File description:
** commands_data.c
*/

#include "server.h"
#include "utils.h"

const command_t GRAPHICAL_COMMANDS[] = {
    {"msz", get_map_size, "Define the map size."},
    {"bct", get_tile_content, "Provide the content of a tile."},
    {"mct", get_all_tiles_content, "Provide the content of the whole map."},
    {"tna", get_all_team_names, "Name all the teams."},
    {"ppo", get_player_position, "Provide a player’s position."},
    {"plv", get_player_level, "Provide a player’s level."},
    {"pin", get_player_inventory, "Provide a player’s inventory."},
    {"sgt", get_time_unit, "Request the time unit."},
    {"sst", set_time_unit, "Set the time unit."},
};

const command_t PLAYER_COMMANDS[] = {
    {"Forward", forward, "Move forward"},
    {"Right", right, "Turn right"},
    {"Left", left, "Turn left"},
    {"Look", look, "Look around"},
    {"Inventory", inventory, "Inventory"},
    {"Broadcast", broadcast, "Broadcast message"},
    {"Connect_nbr", connect_nbr, "Number of free slots"},
    {"Fork", fork_player, "Fork"},
    {"Eject", eject, "Eject player"},
    {"Take", take, "Take object"},
    {"Set", set, "Set object"},
    {"Incantation", incantation, "Incantation"},
    {"Hatch", hatch, "Hatch"},
    {"fake_end", fake_end, "fake_end"},
};

const size_t GRAPHICAL_COMMANDS_SIZE = ARRAY_SIZE(GRAPHICAL_COMMANDS);
const size_t PLAYER_COMMANDS_SIZE = ARRAY_SIZE(PLAYER_COMMANDS);
