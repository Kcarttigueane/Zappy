/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_time_unit.c
*/

#include "server.h"

void get_time_unit(list_args_t* args)
{
    char response[9] = SGT_FORMAT;

    sprintf(response, response, args->server_data->game.freq);

    append_to_gui_write_buffer(args->server_data, response);
}
