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

    // I need to append to the client ok or ko
    // I need to append to the graphical part the new position of the player
}
