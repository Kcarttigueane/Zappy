/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** free_client_list.c
*/

#include "server.h"

void free_client_list(game_t* game)
{
    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &game->client_list, entries, temp)
    {
        LIST_REMOVE(client, entries);
        free(client);
    }
}
