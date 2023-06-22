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

    char** splits = split_str(command_str, " ");

    if (get_size_word_array(splits) != 2) {
        append_to_gui_write_buffer(args->server_data, SBP_FORMAT);
        free_word_array(splits);
        return;
    }

    size_t new_freq = strtoul(splits[1], NULL, 10);

    if (new_freq < 2 || new_freq > 10000) {
        append_to_gui_write_buffer(args->server_data, SBP_FORMAT);
        return;
    }

    args->server_data->game.freq = new_freq;

    printf("New time unit: %zu\n", args->server_data->game.freq);

    char response[32] = {0};

    sprintf(response, SGT_FORMAT, args->server_data->game.freq);

    append_to_gui_write_buffer(args->server_data, response);

    free_word_array(splits);
}
