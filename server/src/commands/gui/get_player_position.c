/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_player_position.c
*/

#include "server.h"

void get_player_position(list_args_t* args)
{
    player_t* player = args->client->player;

    char response[MAX_BUFFER] = {0};

    sprintf(response, PPO_FORMAT, player->id, player->pos.x, player->pos.y,
            player->orientation);

    append_to_gui_write_buffer(args->server_data, response);
}
