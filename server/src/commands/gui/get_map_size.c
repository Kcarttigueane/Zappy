/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_map_size.c
*/

#include "server.h"

void get_map_size(list_args_t* args)
{
    char response[MAX_BUFFER] = {0};

    snprintf(response, sizeof(response), MSZ_FORMAT,
             args->server_data->game.width, args->server_data->game.height);

    append_to_gui_write_buffer(args->server_data, response);
}
