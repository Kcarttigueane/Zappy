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

    // I need to append to the client ok or ko
    // I need to append to the graphical part the new position of the player
}
