/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_all_tiles_content.c
*/

#include "server.h"

void get_all_tiles_content(game_t* game, __attribute_maybe_unused__ client_t* client)
{
    char response[MAX_BUFFER] = {0};

    size_t height = game->height;
    size_t width = game->width;

    for (int y = 0; (size_t)y < height; y++) {
        for (int x = 0; (size_t)x < width; x++) {
            tile_t* tile = &game->map[y][x];
            snprintf(response, sizeof(response), BCT_FORMAT, x, y, tile->quantity[FOOD],
                     tile->quantity[LINEMATE], tile->quantity[DERAUMERE], tile->quantity[SIBUR],
                     tile->quantity[MENDIANE], tile->quantity[PHIRAS], tile->quantity[THYSTAME]);

            append_to_gui_write_buffer(game, response);
            memset(response, 0, sizeof(response));
        }
    }
}
