/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** take.c
*/

#include "server.h"

void take_update_gui_with_player_action(game_t* game, player_t* player, int object_index, coord_t pos)
{
    tile_t* tile = &game->map[pos.x][pos.y];

    char response[256] = {0};
    sprintf(response, PGT_FORMAT, player->id, object_index);
    append_to_gui_write_buffer(game, response);

    memset(response, 0, 256);
    sprintf(response, PIN_FORMAT, player->id, player->pos.x, player->pos.y, player->inventory[FOOD],
            player->inventory[LINEMATE], player->inventory[DERAUMERE], player->inventory[SIBUR],
            player->inventory[MENDIANE], player->inventory[PHIRAS], player->inventory[THYSTAME]);

    append_to_gui_write_buffer(game, response);

    memset(response, 0, 256);

    sprintf(response, BCT_FORMAT, pos.x, pos.y, tile->quantity[FOOD], tile->quantity[LINEMATE],
            tile->quantity[DERAUMERE], tile->quantity[SIBUR], tile->quantity[MENDIANE],
            tile->quantity[PHIRAS], tile->quantity[THYSTAME]);

    append_to_gui_write_buffer(game, response);
}

void take(game_t* game, client_t* client)
{
    player_t* player = client->player;
    char* command = peek_command(client);

    char** command_args = split_str(command, " ");
    char* object_name = command_args[1];
    printf("object_name: %s\n", object_name);

    if (object_name == NULL) {
        append_to_string(client->write_buf, KO_FORMAT);
        return;
    }

    int object_index = find_object_index(object_name);
    printf("object_index: %d\n", object_index);
    if (object_index == FAILURE) {
        append_to_string(client->write_buf, KO_FORMAT);
        free_word_array(command_args);
        return;
    }

    coord_t pos = player->pos;

    tile_t* tile = &game->map[pos.x][pos.y];

    debug_tile_content(tile, pos);

    if (tile->quantity[object_index] > 0) {
        tile->quantity[object_index]--;

        player->inventory[object_index]++;

        take_update_gui_with_player_action(game, player, object_index, pos);

        append_to_string(client->write_buf, OK_FORMAT);
    } else {
        append_to_string(client->write_buf, KO_FORMAT);
    }
    free_word_array(command_args);
}
