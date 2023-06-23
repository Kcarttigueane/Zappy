/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_player_from_command.c
*/

#include "server.h"

player_t* get_player_from_command(game_t* game, char* command)
{
    char** splits = split_str(command, " ");

    if (get_size_word_array(splits) != 2) {
        append_to_gui_write_buffer(game, SBP_FORMAT);
        free_word_array(splits);
        return NULL;
    }

    int id = atoi(splits[1]);
    printf("id: %d\n", id);

    player_t* player = find_player_by_id(game, id);

    if (player == NULL) {
        append_to_gui_write_buffer(game, SBP_FORMAT);
    }

    free_word_array(splits);

    return player;
}
