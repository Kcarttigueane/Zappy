/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** forward.c
*/

#include "server.h"

void forward(list_args_t* args)
{
    player_t* player = args->client->player;
    int board_width = args->server_data->game.width;
    int board_height = args->server_data->game.height;

    switch (player->orientation) {
        case NORTH:
            player->pos.y--;
            if (player->pos.y < 0)
                player->pos.y = board_height - 1;
            break;
        case SOUTH:
            player->pos.y++;
            if (player->pos.y >= board_height)
                player->pos.y = 0;
            break;
        case WEST:
            player->pos.x--;
            if (player->pos.x < 0)
                player->pos.x = board_width - 1;
            break;
        case EAST:
            player->pos.x++;
            if (player->pos.x >= board_width)
                player->pos.x = 0;
            break;
    }

    append_to_string(args->client->write_buf, OK_FORMAT);

    char response[24] = {0};

    sprintf(response, PPO_FORMAT, player->id, player->pos.x, player->pos.y,
            player->orientation);

    append_to_gui_write_buffer(args->server_data, response);
}
