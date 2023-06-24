/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_all_team_names.c
*/

#include "server.h"

void get_all_team_names(game_t* game, __attribute_maybe_unused__ client_t* client)
{
    char response[MAX_BUFFER] = {0};

    for (size_t i = 0; i < game->team_count; i++) {
        snprintf(response, sizeof(response), TNA_FORMAT, game->team_names[i]);

        append_to_gui_write_buffer(game, response);
    }
}
