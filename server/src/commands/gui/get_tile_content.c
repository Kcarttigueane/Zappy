/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_tile_content.c
*/

#include "server.h"

static bool is_valid_tile(int x, int y, size_t height, size_t width)
{
    return x >= 0 && (size_t)x < width && y >= 0 && (size_t)y < height;
}

static void send_resp(game_t* game, int x, int y)
{
    char response[MAX_BUFFER] = {0};

    tile_t* tile = &game->map[y][x];

    sprintf(response, BCT_FORMAT, x, y, tile->quantity[FOOD], tile->quantity[LINEMATE],
            tile->quantity[DERAUMERE], tile->quantity[SIBUR], tile->quantity[MENDIANE],
            tile->quantity[PHIRAS], tile->quantity[THYSTAME]);

    append_to_gui_write_buffer(game, response);
}

void get_tile_content(game_t* game, client_t* client)
{
    int x, y = -1;
    char* command = peek_command(client);

    sscanf(command, "bct %i %i", &x, &y);

    size_t height = game->height;
    size_t width = game->width;

    if (!is_valid_tile(x, y, height, width)) {
        append_to_gui_write_buffer(game, SBP_FORMAT);
        return;
    }

    send_resp(game, x, y);
}
