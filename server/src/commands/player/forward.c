/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** forward.c
*/

#include "server.h"

void forward(game_t* game, client_t* client)
{
    player_t* player = client->player;
    size_t width = game->width;
    size_t height = game->height;

    switch (player->orientation) {
        case NORTH:
            player->pos.y--;
            if (player->pos.y < 0)
                player->pos.y = height - 1;
            break;
        case SOUTH:
            player->pos.y++;
            if (player->pos.y >= (int)height)
                player->pos.y = 0;
            break;
        case WEST:
            player->pos.x--;
            if (player->pos.x < 0)
                player->pos.x = width - 1;
            break;
        case EAST:
            player->pos.x++;
            if (player->pos.x >= (int)width)
                player->pos.x = 0;
            break;
    }

    append_to_string(client->write_buf, OK_FORMAT);

    char response[24] = {0};

    int y_carte = (height - 1) - player->pos.y;

    sprintf(response, PPO_FORMAT, player->id, player->pos.x, y_carte, player->orientation);

    append_to_gui_write_buffer(game, response);
}
