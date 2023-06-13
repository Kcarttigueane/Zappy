/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** msz.c
*/

#include "server.h"

void msz(list_args_t* args)
{
    char response[MAX_BUFFER] = {0};

    snprintf(response, sizeof(response), "msz %zu %zu\n",
             args->server_data->game.width, args->server_data->game.height);

    append_to_write_buffer(args->client, response);
}
