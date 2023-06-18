/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_player_inventory.c
*/

#include "server.h"

void get_player_inventory(list_args_t* args)
{
    char* command_str =
        args->client->player->command_queue
            .commands[args->client->player->command_queue.front];

    char **splits = split_str(command_str, " ");

    if (get_size_word_array(splits) != 2) {
        append_to_gui_write_buffer(args->server_data, SBP_FORMAT);
        return;
    }

    int id = atoi(splits[1]);
    printf("id: %d\n", id);

    player_t* player = find_player_by_id(args->server_data, id);

    if (player == NULL) {
        append_to_gui_write_buffer(args->server_data, SBP_FORMAT);
        return;
    }

    free_word_array(splits);

    char response[MAX_BUFFER] = {0};

    sprintf(response, PIN_FORMAT, player->id, player->pos.x, player->pos.y,
            player->inventory[FOOD], player->inventory[LINEMATE],
            player->inventory[DERAUMERE], player->inventory[SIBUR],
            player->inventory[MENDIANE], player->inventory[PHIRAS],
            player->inventory[THYSTAME]);

    append_to_gui_write_buffer(args->server_data, response);
}
