/*
** EPITECH PROJECT, 2022
** server
** File description:
** command_tools.c
*/

#include "server.h"

size_t find_player_command_index(char* command_name)
{
    for (size_t i = 0; i < PLAYER_COMMANDS_SIZE; i++) {
        if (!strcasecmp(command_name, PLAYER_COMMANDS[i].name)) {
            return i;
        }
    }
    return FAILURE;
}

size_t find_graphical_command_index(char* command_name)
{
    for (size_t i = 0; i < GRAPHICAL_COMMANDS_SIZE; i++) {
        if (!strcasecmp(command_name, GRAPHICAL_COMMANDS[i].name)) {
            return i;
        }
    }
    return FAILURE;
}
