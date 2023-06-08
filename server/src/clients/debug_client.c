/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** debug_client.c
*/

#include "server.h"

void print_client_info(client_t* client)
{
    printf("Client fd: %d\n", client->fd);
    printf("Client write buffer: %s\n", client->write_buf);
    printf("Client read buffer: %s\n", client->read_buf);
    printf("Client player level: %ld\n", client->player->level);
}

void print_all_clients(game_t* game)
{
    client_t *client, *temp;

    printf("Clients in the game:\n");
    LIST_FOREACH_SAFE(client, &game->client_list, entries, temp)
    {
        print_client_info(client);
    }
}
