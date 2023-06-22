/*
** EPITECH PROJECT, 2022
** server
** File description:
** client_tools.c
*/

#include "server.h"

player_t* find_player_by_id(server_data_t* s, int id)
{
    client_t* client;

    LIST_FOREACH(client, &s->game.client_list, entries)
    {
        if (client->player->id == (size_t)id) {
            return client->player;
        }
    }
    return NULL;
}

void add_client(game_t* game, client_t* client)
{
    LIST_INSERT_HEAD(&game->client_list, client, entries);
}

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

void free_player(player_t* player)
{
    free(player);
}

void free_client_list(game_t* game)
{
    printf("Freeing client list\n");
    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &game->client_list, entries, temp)
    {
        LIST_REMOVE(client, entries);
        free_player(client->player);
        free(client);
    }
}
