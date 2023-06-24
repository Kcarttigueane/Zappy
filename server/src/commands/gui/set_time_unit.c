/*
** EPITECH PROJECT, 2022
** server
** File description:
** set_time_unit.c
*/

#include "server.h"

void set_time_unit(game_t* game, client_t* client)
{
    char* command = peek_command(client);

    int new_freq;
    sscanf(command, "sst %i", &new_freq);

    if (new_freq < 2 || new_freq > 1000) {
        append_to_gui_write_buffer(game, SBP_FORMAT);
        return;
    }

    game->freq = new_freq;

    char response[32] = {0};

    sprintf(response, SGT_FORMAT, game->freq);

    append_to_gui_write_buffer(game, response);
}
