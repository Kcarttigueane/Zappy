/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** inventory.c
*/

#include "server.h"

void inventory(list_args_t* args)
{
    client_t* client = args->client;
    size_t* player_inventory = client->player->inventory;

    char inventory_str[MAX_BUFFER] = "[";

    for (int i = 0; i < MAX_NB_RESOURCES; i++) {
        char object_quantity[100] = {0};

        sprintf(object_quantity, "%s %ld,", inventory_names[i],
                player_inventory[i]);

        strcat(inventory_str, object_quantity);
    }

    inventory_str[strlen(inventory_str) - 1] = ']';

    // add_message_to_write_buffer(client, inventory_str);
}
