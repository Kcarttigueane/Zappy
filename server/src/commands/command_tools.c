/*
** EPITECH PROJECT, 2022
** server
** File description:
** command_tools.c
*/

#include "server.h"

int find_player_command_index(char* command_name)
{
    for (size_t i = 0; i < PLAYER_COMMANDS_SIZE; i++) {
        if (!strcasecmp(command_name, PLAYER_COMMANDS[i].name)) {
            return i;
        }
    }

    printf("Command not found: %s\n", command_name);
    return FAILURE;
}

int find_graphical_command_index(char* command_name)
{
    for (size_t i = 0; i < GRAPHICAL_COMMANDS_SIZE; i++) {
        if (!strcasecmp(command_name, GRAPHICAL_COMMANDS[i].name)) {
            return i;
        }
    }

    printf("Command not found: %s\n", command_name);
    return FAILURE;
}

int find_object_index(char* object_name)
{
    int object_index = FAILURE;

    for (int i = 0; i < MAX_NB_RESOURCES; i++) {
        if (!strcasecmp(inventory_names[i], object_name)) {
            object_index = i;
            break;
        }
    }

    return object_index;
}
