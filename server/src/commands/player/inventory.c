/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** inventory.c
*/

#include "server.h"

void inventory(list_args_t* args)
{
    player_t* player = args->client->player;
    client_t* client = args->client;

    char response[1024] = {0};

    sprintf(response, INVENTORY_FORMAT, player->inventory[FOOD],
            player->inventory[LINEMATE], player->inventory[DERAUMERE],
            player->inventory[SIBUR], player->inventory[MENDIANE],
            player->inventory[PHIRAS], player->inventory[THYSTAME]);

    printf("response: %s\n", response);
    append_to_string(client->write_buf, response);
}
