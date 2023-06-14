/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** set.c
*/

#include "server.h"

void set(list_args_t* args)
{
    char* command_str =
        args->client->player->command_queue
            .commands[args->client->player->command_queue.front];

    client_t* client = args->client;
    game_t* game = &args->server_data->game;

    char* object_name = split_str(command_str, " ")[1];

    if (object_name == NULL) {
        // add_message_to_write_buffer(client, "ko\n");
        return;
    }

    int object_index = find_object_index(object_name);
    if (object_index == FAILURE) {
        // add_message_to_write_buffer(client, "ko\n");
        return;
    }

    if (client->player->inventory[object_index] <= 0) {
        // add_message_to_write_buffer(client, "ko\n");
        return;
    }

    coord_t pos = client->player->pos;

    client->player->inventory[object_index]--;

    game->map[pos.x][pos.y].quantity[object_index]++;

    // add_message_to_write_buffer(client, "ok\n");
}
