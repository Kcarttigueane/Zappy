/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_player_level.c
*/

#include "server.h"

void get_player_level(list_args_t* args)
{
    player_t* player = get_player_from_command(args);

    if (player == NULL) {
        return;
    }
    char response[MAX_BUFFER] = {0};

    sprintf(response, PLV_FORMAT, player->id, player->level);

    append_to_gui_write_buffer(args->server_data, response);
}
