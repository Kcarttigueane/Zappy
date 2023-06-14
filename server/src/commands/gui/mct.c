/*
** EPITECH PROJECT, 2022
** server
** File description:
** mct.c
*/

#include "server.h"

void mct(list_args_t* args)
{
    char response[MAX_BUFFER] = {0};
    size_t height = args->server_data->game.height;
    size_t width = args->server_data->game.width;

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            tile_t* tile = get_tile(args->server_data->game.map, x, y);
            snprintf(response, sizeof(response),
                     "bct %zu %zu %lu %lu %lu %lu %lu %lu %lu\n", x, y,
                     tile->quantity[FOOD], tile->quantity[LINEMATE],
                     tile->quantity[DERAUMERE], tile->quantity[SIBUR],
                     tile->quantity[MENDIANE], tile->quantity[PHIRAS],
                     tile->quantity[THYSTAME]);

            // append_to_write_buffer(args->client, response);
        }
    }
}
