/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** plv.c
*/

#include "server.h"

void plv(__attribute_maybe_unused__ list_args_t* args)
{
    player_t* player = args->client->player;

    char response[MAX_BUFFER] = {0};

    sprintf(response, "plv %lu %lu\n", player->id, player->level);

    append_to_write_buffer(args->client, response);
}
