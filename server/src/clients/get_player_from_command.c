/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_player_from_command.c
*/

#include "server.h"

player_t* get_player_from_command(list_args_t* args)
{
    char* command_str =
        args->client->player->command_queue
            .commands[args->client->player->command_queue.front];

    char** splits = split_str(command_str, " ");

    if (get_size_word_array(splits) != 2) {
        append_to_gui_write_buffer(args->server_data, SBP_FORMAT);
        free_word_array(splits);
        return NULL;
    }

    int id = atoi(splits[1]);
    printf("id: %d\n", id);

    player_t* player = find_player_by_id(args->server_data, id);

    if (player == NULL) {
        append_to_gui_write_buffer(args->server_data, SBP_FORMAT);
    }

    free_word_array(splits);

    return player;
}
