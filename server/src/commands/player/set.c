/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** set.c
*/

#include "server.h"

void set(list_args_t* args)
{
    game_t* game = &args->server_data->game;
    player_t* player = args->player;

    char* object_name = split_str(args->command, " ")[1];

    if (object_name == NULL) {
        append_to_string(args->client->write_buf, KO_FORMAT);
        return;
    }

    int object_index = find_object_index(object_name);
    if (object_index == FAILURE) {
        append_to_string(args->client->write_buf, KO_FORMAT);
        return;
    }

    if (player->inventory[object_index] <= 0) {
        append_to_string(args->client->write_buf, KO_FORMAT);
        return;
    }

    coord_t pos = player->pos;

    player->inventory[object_index]--;

    game->map[pos.x][pos.y].quantity[object_index]++;

    char response[256] = {0};
    sprintf(response, PDR_FORMAT, player->id, object_index);
    append_to_gui_write_buffer(args->server_data, response);

    memset(response, 0, 256);
    sprintf(response, PIN_FORMAT, player->id, player->pos.x, player->pos.y,
            player->inventory[FOOD], player->inventory[LINEMATE],
            player->inventory[DERAUMERE], player->inventory[SIBUR],
            player->inventory[MENDIANE], player->inventory[PHIRAS],
            player->inventory[THYSTAME]);

    append_to_gui_write_buffer(args->server_data, response);

    memset(response, 0, 256);

    sprintf(response, BCT_FORMAT, pos.x, pos.y,
            game->map[pos.x][pos.y].quantity[FOOD],
            game->map[pos.x][pos.y].quantity[LINEMATE],
            game->map[pos.x][pos.y].quantity[DERAUMERE],
            game->map[pos.x][pos.y].quantity[SIBUR],
            game->map[pos.x][pos.y].quantity[MENDIANE],
            game->map[pos.x][pos.y].quantity[PHIRAS],
            game->map[pos.x][pos.y].quantity[THYSTAME]);

    append_to_gui_write_buffer(args->server_data, response);

    append_to_string(args->client->write_buf, OK_FORMAT);
}
