/*
** EPITECH PROJECT, 2022
** server
** File description:
** set_time_unit.c
*/

#include "server.h"

void set_time_unit(list_args_t* args)
{
    char* command_str =
        args->client->player->command_queue
            .commands[args->client->player->command_queue.front];

    int new_freq;
    sscanf(command_str, "sst %i", &new_freq);

    if (new_freq < 2 || new_freq > 1000) {
        append_to_gui_write_buffer(args->server_data, SBP_FORMAT);
        return;
    }

    args->server_data->game.freq = new_freq;

    char response[32] = {0};

    sprintf(response, SGT_FORMAT, args->server_data->game.freq);
    append_to_gui_write_buffer(args->server_data, response);
}
