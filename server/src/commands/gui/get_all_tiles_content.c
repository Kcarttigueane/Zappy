/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_all_tiles_content.c
*/

#include "server.h"

void get_all_tiles_content(list_args_t* args)
{
    char response[MAX_BUFFER] = {0};
    size_t height = args->server_data->game.height;
    size_t width = args->server_data->game.width;

    for (int y = 0; (size_t)y < height; y++) {
        for (int x = 0; (size_t)x < width; x++) {
            tile_t* tile = get_tile(args->server_data->game.map, x, y);
            snprintf(response, sizeof(response), BCT_FORMAT, x, y,
                     tile->quantity[FOOD], tile->quantity[LINEMATE],
                     tile->quantity[DERAUMERE], tile->quantity[SIBUR],
                     tile->quantity[MENDIANE], tile->quantity[PHIRAS],
                     tile->quantity[THYSTAME]);

            append_to_gui_write_buffer(args->server_data, response);
            memset(response, 0, sizeof(response));
        }
    }
}
