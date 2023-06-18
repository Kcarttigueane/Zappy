/*
** EPITECH PROJECT, 2022
** server
** File description:
** find_player_by_id.c
*/

#include "server.h"

player_t* find_player_by_id(server_data_t* s, int id)
{
    client_t* client;

    LIST_FOREACH(client, &s->game.client_list, entries)
    {
        if (client->player->id == id) {
            return client->player;
        }
    }
    return NULL;
}
