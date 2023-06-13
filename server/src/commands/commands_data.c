/*
** EPITECH PROJECT, 2022
** MyTeams
** Fil:
** commands_data.c
*/

#include "server.h"
#include "utils.h"

const command_t GRAPHICAL_COMMANDS[] = {
    {"msz", msz, "Define the map size."},
    {"bct", bct, "Provide the content of a tile."},
    {"mct", mct, "Provide the content of the whole map."},
    {"tna", tna, "Name all the teams."},
    {"ppo", ppo, "Provide a player’s position."},
    {"plv", plv, "Provide a player’s level."},
    {"pin", pin, "Provide a player’s inventory."},
    {"sgt", sgt, "Request the time unit."},
    {"sst", sst, "Set the time unit."},
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
