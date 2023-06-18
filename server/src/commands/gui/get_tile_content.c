/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_tile_content.c
*/

#include "server.h"

tile_t* get_tile(tile_t** map, int x, int y)
{
    return &(map[y][x]);
}

void get_tile_content(list_args_t* args)
{
    char* command_str =
        args->client->player->command_queue
            .commands[args->client->player->command_queue.front];

    int x, y;
    sscanf(command_str, "bct %i %i", &x, &y);

    if (x < 0 || (size_t)x >= args->server_data->game.width || y < 0 ||
        (size_t)y >= args->server_data->game.height) {
        append_to_gui_write_buffer(args->server_data, SBP_FORMAT);
        return;
    }
    tile_t* tile = get_tile(args->server_data->game.map, x, y);

    char response[MAX_BUFFER] = {0};

    sprintf(response, BCT_FORMAT, x, y, tile->quantity[FOOD],
            tile->quantity[LINEMATE], tile->quantity[DERAUMERE],
            tile->quantity[SIBUR], tile->quantity[MENDIANE],
            tile->quantity[PHIRAS], tile->quantity[THYSTAME]);

    append_to_gui_write_buffer(args->server_data, response);
}
