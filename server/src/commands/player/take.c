/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** take.c
*/

#include "server.h"

int find_object_index(char* object_name)
{
    const char* inventory_names[] = {"food",    "linemate", "deraumere",
                                     "sibur",   "mendiane", "phiras",
                                     "thystame"};

    int object_index = FAILURE;
    for (int i = 0; i < MAX_NB_RESOURCES; i++) {
        if (strcmp(inventory_names[i], object_name) == 0) {
            object_index = i;
            break;
        }
    }

    return object_index;
}

void take_object(list_args_t* args)
{
    char* command_str =
        args->client->player->command_queue
            .commands[args->client->player->command_queue.front];

    client_t* client = args->client;
    game_t* game = &args->server_data->game;

    char *object_name = split_str(command_str, ' ')[1];

    if (object_name == NULL) {
        // add_message_to_write_buffer(client, "ko\n");
        return;
    }

    int object_index = find_object_index(object_name);
    if (object_index == FAILURE) {
        // add_message_to_write_buffer(client, "ko\n");
        return;
    }

    coord_t pos = client->player->pos;

    if (game->map[pos.x][pos.y].quantity[object_index] > 0) {
        game->map[pos.x][pos.y].quantity[object_index]--;

        client->player->inventory[object_index]++;

        // add_message_to_write_buffer(client, "ok\n");
    } else {
        // add_message_to_write_buffer(client, "ko\n");
    }
}
