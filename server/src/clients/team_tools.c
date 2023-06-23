/*
** EPITECH PROJECT, 2022
** server
** File description:
** team_tools.c
*/

#include "server.h"

int find_team_index(game_t* game, char* team_name)
{
    for (size_t i = 0; i < game->team_count; i++) {
        if (!strcmp(game->team_names[i], team_name))
            return i;
    }
    return FAILURE;
}

bool is_team_name_valid(game_t* game, char** inputs)
{
    for (size_t i = 0; i < game->team_count; i++) {
        if (!strcmp(game->team_names[i], inputs[0]))
            return true;
    }

    printf("Invalid team name\n");

    return false;
}

team_t* find_team_by_name(game_t* game, char* team_name)
{
    for (size_t i = 0; i < game->team_count; i++) {
        if (!strcmp(game->team_names[i], team_name))
            return &game->team[i];
    }
    return NULL;
}
