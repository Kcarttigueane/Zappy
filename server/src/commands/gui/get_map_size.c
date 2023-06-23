/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_map_size.c
*/

#include "server.h"

void get_map_size(game_t* game, __attribute_maybe_unused__ client_t* client)
{
    char response[MAX_BUFFER] = {0};

    snprintf(response, sizeof(response), MSZ_FORMAT, game->width, game->height);

    append_to_gui_write_buffer(game, response);
}
