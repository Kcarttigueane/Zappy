/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_player_inventory.c
*/

#include "server.h"

void get_player_inventory(game_t* game, client_t* client)
{
    char* command = peek_command(client);
    player_t* player = get_player_from_command(game, command);

    if (player == NULL) {
        return;
    }

    char response[MAX_BUFFER] = {0};

    sprintf(response, PIN_FORMAT, player->id, player->pos.x, player->pos.y, player->inventory[FOOD],
            player->inventory[LINEMATE], player->inventory[DERAUMERE], player->inventory[SIBUR],
            player->inventory[MENDIANE], player->inventory[PHIRAS], player->inventory[THYSTAME]);

    append_to_gui_write_buffer(game, response);
}
