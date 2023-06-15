/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** bct.c
*/

#include "server.h"

tile_t* get_tile(tile_t** map, int x, int y)
{
    return &(map[y][x]);
}

void bct(list_args_t* args)
{
    char* command_str =
        args->client->player->command_queue
            .commands[args->client->player->command_queue.front];

    size_t x, y;
    sscanf(command_str, "bct %lu %lu", &x, &y);

    if (x < 0 || x >= args->server_data->game.width || y < 0 ||
        y >= args->server_data->game.height) {
        // append_to_write_buffer(args->client, "sbp\n");
        return;
    }

    tile_t* tile = get_tile(args->server_data->game.map, x, y);

    char response[MAX_BUFFER] = {0};
    sprintf(response, "bct %lu %lu %lu %lu %lu %lu %lu %lu %lu\n", x, y,
            tile->quantity[FOOD], tile->quantity[LINEMATE],
            tile->quantity[DERAUMERE], tile->quantity[SIBUR],
            tile->quantity[MENDIANE], tile->quantity[PHIRAS],
            tile->quantity[THYSTAME]);

    // append_to_write_buffer(args->client, response);
}
