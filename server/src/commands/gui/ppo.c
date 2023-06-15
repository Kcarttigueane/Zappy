/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** ppo.c
*/

#include "server.h"

void ppo(list_args_t* args)
{
    player_t* player = args->client->player;

    char response[MAX_BUFFER] = {0};

    sprintf(response, "ppo %lu %i %i %d\n", player->id, player->pos.x,
            player->pos.y, player->orientation);

    // append_to_write_buffer(args->client, response);
}
