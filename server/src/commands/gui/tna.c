/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** tna.c
*/

#include "server.h"

void tna(list_args_t* args)
{
    char response[MAX_BUFFER] = {0};

    for (size_t i = 0; i < args->server_data->game.team_count; i++) {
        snprintf(response, sizeof(response), "tna %s\n",
                 args->server_data->game.team_names[i]);
        // append_to_write_buffer(args->client, response);
    }
}
