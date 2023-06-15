/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_all_team_names.c
*/

#include "server.h"

void get_all_team_names(list_args_t* args)
{
    char response[MAX_BUFFER] = {0};

    for (size_t i = 0; i < args->server_data->game.team_count; i++) {
        snprintf(response, sizeof(response), TNA_FORMAT,
                 args->server_data->game.team_names[i]);

        append_to_gui_write_buffer(args->server_data, response);
    }
}
