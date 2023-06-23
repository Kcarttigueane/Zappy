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

static void send_resp(list_args_t* args, int x, int y)
{
    char response[MAX_BUFFER] = {0};

    tile_t* tile = &args->server_data->game.map[y][x];

    sprintf(response, BCT_FORMAT, x, y, tile->quantity[FOOD],
            tile->quantity[LINEMATE], tile->quantity[DERAUMERE],
            tile->quantity[SIBUR], tile->quantity[MENDIANE],
            tile->quantity[PHIRAS], tile->quantity[THYSTAME]);

    append_to_gui_write_buffer(args->server_data, response);
}

void get_tile_content(list_args_t* args)
{
    int x, y = -1;
    sscanf(args->command, "bct %i %i", &x, &y);

    size_t height = args->server_data->game.height;
    size_t width = args->server_data->game.width;

    if (!is_valid_tile(x, y, height, width)) {
        append_to_gui_write_buffer(args->server_data, SBP_FORMAT);
        return;
    }

    send_resp(args, x, y);
}
