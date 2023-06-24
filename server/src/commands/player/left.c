/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** left.c
*/

#include "server.h"

void left(game_t* game, client_t* client)
{
    player_t* player = client->player;

    player->orientation--;
    if (player->orientation < NORTH)
        player->orientation = WEST;

    append_to_string(client->write_buf, OK_FORMAT);

    char response[24] = {0};

    sprintf(response, PPO_FORMAT, player->id, player->pos.x, player->pos.y, player->orientation);

    append_to_gui_write_buffer(game, response);
}
