/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** sgt.c
*/

#include "server.h"

void sgt(list_args_t* args)
{
    char response[9] = "sgt %ld\n";

    sprintf(response, response, args->server_data->game.freq);

    append_to_write_buffer(args->client, response);
}
