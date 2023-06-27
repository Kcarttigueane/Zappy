/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** right.c
*/

#include "server.h"

void right(game_t* game, client_t* client)
{
    player_t* player = client->player;

    player->orientation++;
    if (player->orientation > WEST)
        player->orientation = NORTH;

    append_to_string(client->write_buf, OK_FORMAT);

    char response[24] = {0};

    int y_cartesian = game->height - player->pos.y - 1;

    sprintf(response, PPO_FORMAT, player->id, player->pos.x, y_cartesian, player->orientation);

    append_to_gui_write_buffer(game, response);
}
