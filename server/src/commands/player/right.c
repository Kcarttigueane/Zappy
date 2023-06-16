/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** right.c
*/

#include "server.h"

void right(list_args_t* args)
{
    player_t* player = args->client->player;

    player->orientation++;
    if (player->orientation > WEST)
        player->orientation = NORTH;

    append_to_string(args->client->write_buf, OK_FORMAT);

    char response[24] = {0};

    sprintf(response, PPO_FORMAT, player->id, player->pos.x, player->pos.y,
            player->orientation);

    append_to_gui_write_buffer(args->server_data, response);
}
