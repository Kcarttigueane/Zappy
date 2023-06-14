/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** pin.c
*/

#include "server.h"

void pin(list_args_t* args)
{
    player_t* player = args->client->player;

    char response[MAX_BUFFER] = {0};

    sprintf(response, "pin %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu\n",
            player->id, player->pos.x, player->pos.y, player->inventory[FOOD],
            player->inventory[FOOD], player->inventory[LINEMATE],
            player->inventory[DERAUMERE], player->inventory[SIBUR],
            player->inventory[MENDIANE], player->inventory[PHIRAS],
            player->inventory[THYSTAME]);

    append_to_write_buffer(args->client, response);
}
