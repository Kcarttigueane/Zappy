/*
** EPITECH PROJECT, 2022
** server
** File description:
** commands_data.c
*/

#include "server.h"
#include "utils.h"

const command_t GRAPHICAL_COMMANDS[] = {
    {"msz", get_map_size, "Define the map size.", 0},
    {"bct", get_tile_content, "Provide the content of a tile.", 0},
    {"mct", get_all_tiles_content, "Provide the content of the whole map.", 0},
    {"tna", get_all_team_names, "Name all the teams.", 0},
    {"ppo", get_player_position, "Provide a player’s position.", 0},
    {"plv", get_player_level, "Provide a player’s level.", 0},
    {"pin", get_player_inventory, "Provide a player’s inventory.", 0},
    {"sgt", get_time_unit, "Request the time unit.", 0},
    {"sst", set_time_unit, "Set the time unit.", 0},
    {"BAD_COMMAND", NULL, "Bad command", 0},
};

const command_t PLAYER_COMMANDS[] = {
    {"Forward", forward, "Move forward", 7},
    {"Right", right, "Turn right", 7},
    {"Left", left, "Turn left", 7},
    {"Look", look, "Look around", 7},
    {"Inventory", inventory, "Inventory", 1},
    {"Broadcast", broadcast, "Broadcast message", 7},
    {"Connect_nbr", connect_nbr, "Number of free slots", 0},
    {"Fork", fork_player, "Fork", 0},
    {"End_fork", end_fork, "End of a fork", 42},
    {"Eject", eject, "Eject player", 7},
    {"Take", take, "Take object", 7},
    {"Set", set, "Set object", 7},
    {"Incantation", start_incantation, "Start of incantation", 0},
    {"End_of_incantation", end_incantation, "End of incantation", 300},
    {"Hatch", hatch, "Hatch", 0},
};

const size_t GRAPHICAL_COMMANDS_SIZE = ARRAY_SIZE(GRAPHICAL_COMMANDS);
const size_t PLAYER_COMMANDS_SIZE = ARRAY_SIZE(PLAYER_COMMANDS);
