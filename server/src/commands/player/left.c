/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** left.c
*/

#include "server.h"

void left(list_args_t* args)
{
    player_t* player = args->client->player;

    player->orientation--;
    if (player->orientation < NORTH)
        player->orientation = WEST;

    append_to_string(args->client->write_buf, OK_FORMAT);

    char response[24] = {0};

    sprintf(response, PPO_FORMAT, player->id, player->pos.x, player->pos.y,
            player->orientation);

    append_to_gui_write_buffer(args->server_data, response);
}
