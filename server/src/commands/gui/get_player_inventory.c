/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_player_inventory.c
*/

#include "server.h"

void get_player_inventory(list_args_t* args)
{
    player_t* player = args->client->player;

    char response[MAX_BUFFER] = {0};

    sprintf(response, PIN_FORMAT, player->id, player->pos.x, player->pos.y,
            player->inventory[FOOD], player->inventory[LINEMATE],
            player->inventory[DERAUMERE], player->inventory[SIBUR],
            player->inventory[MENDIANE], player->inventory[PHIRAS],
            player->inventory[THYSTAME]);

    append_to_gui_write_buffer(args->server_data, response);
}
