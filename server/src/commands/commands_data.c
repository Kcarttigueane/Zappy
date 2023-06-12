/*
** EPITECH PROJECT, 2022
** MyTeams
** Fil:
** commands_data.c
*/

#include "../../include/server.h"
#include "../../include/utils.h"

const command_t GRAPHICAL_COMMANDS[] = {
    {"msz", msz, "Define the map size.", 2},
    {"bct", bct, "Provide the content of a tile.", 9},
    {"tna", tna, "Name all the teams.", 1},
    {"pnw", pnw, "Connect a new player.", 6},
    {"ppo", ppo, "Provide a player’s position.", 4},
    {"plv", plv, "Provide a player’s level.", 2},
    {"pin", pin, "Provide a player’s inventory.", 10},
    {"pex", pex, "Handle expulsion of a player.", 1},
    {"pbc", pbc, "Handle a broadcast message from a player.", 2},
    {"pic", pic, "Start an incantation.",
     4},  // Note: You may need to adjust the number of arguments depending on how you handle this command
    {"pie", pie, "End an incantation.", 3},
    {"pfk", pfk, "Lay an egg.", 1},
    {"pdr", pdr, "Drop a resource.", 2},
    {"pgt", pgt, "Collect a resource.", 2},
    {"pdi", pdi, "Handle the death of a player.", 1},
    {"enw", enw, "Lay an egg by a player.", 4},
    {"ebo", ebo, "Connect a player to an egg.", 1},
    {"edi", edi, "Handle the death of an egg.", 1},
    {"sgt", sgt, "Request the time unit.", 1},
    {"sst", sst, "Modify the time unit.", 1},
    {"seg", seg, "End the game.", 1},
    {"smg", smg, "Send a message from the server.", 1},
    {"suc", suc, "Handle an unknown command.", 0},
    {"sbp", sbp, "Handle a command with a bad parameter.", 0}};

const command_t PLAYER_COMMANDS[] = {
    {"Forward", forward, "Move forward", 0},
    {"Right", right, "Turn right", 0},
    {"Left", left, "Turn left", 0},
    {"Look", look, "Look around", 0},
    {"Inventory", inventory, "Inventory", 0},
    {"Broadcast", broadcast, "Broadcast message", 1},
    {"Connect_nbr", connect_nbr, "Number of free slots", 0},
    {"Fork", fork_player, "Fork", 0},
    {"Eject", eject, "Eject player", 0},
    {"Take", take, "Take object", 1},
    {"Set", set, "Set object", 1},
    {"Incantation", incantation, "Incantation", 0},
    {"Hatch", hatch, "Hatch", 0},
    {"fake_end", fake_end, "fake_end", 0},
    {NULL, NULL, NULL, 0}};

const size_t GRAPHICAL_COMMANDS_SIZE = ARRAY_SIZE(GRAPHICAL_COMMANDS);
const size_t PLAYER_COMMANDS_SIZE = ARRAY_SIZE(PLAYER_COMMANDS);
