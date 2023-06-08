/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** remove_client.c
*/

#include "server.h"

void remove_client_by_fd(game_t* game, int fd)
{
    client_t* client;

    LIST_FOREACH(client, &game->client_list, entries)
    {
        if (client->fd == fd) {
            LIST_REMOVE(client, entries);
            free(client);
            return;
        }
    }
}
