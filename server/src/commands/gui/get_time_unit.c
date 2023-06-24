/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_time_unit.c
*/

#include "server.h"

void get_time_unit(game_t* game, __attribute_maybe_unused__ client_t* client)
{
    char response[9] = {0};

    sprintf(response, SGT_FORMAT, game->freq);

    append_to_gui_write_buffer(game, response);
}
