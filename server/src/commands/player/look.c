/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** look.c
*/

#include "server.h"

size_t get_nbr_player_on_tile(server_data_t* s, coord_t pos)
{
    client_t *client, *temp;

    size_t count = 0;

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {
        if (client->player->pos.x == pos.x && client->player->pos.y == pos.y)
            count++;
    }
    return count;
}

char** get_objects_on_tile(server_data_t* s, tile_t* tile, coord_t pos)
{
    size_t nb_players = get_nbr_player_on_tile(s, pos);

    char** objects =
        (char**)calloc(MAX_NB_RESOURCES + nb_players, sizeof(char*));
    if (!objects) {
        perror("Failed to allocate memory for objects");
        return NULL;
    }

    const char* inventory_names[] = {"food",    "linemate", "deraumere",
                                     "sibur",   "mendiane", "phiras",
                                     "thystame"};

    size_t i = 0;

    for (; i < nb_players; ++i)
        objects[i] = strdup("player");

    for (; i < MAX_NB_RESOURCES; ++i) {
        if (tile->quantity[i] > 0) {
            objects[i] = strdup(inventory_names[i]);
            if (!objects[i]) {
                perror("Failed to allocate memory for object name");
                for (int j = 0; j < i; ++j)
                    free(objects[j]);
                free(objects);
                return NULL;
            }
        }
    }
}

void look(list_args_t* args)
{
    server_data_t* s = args->server_data;
    player_t* player = args->client->player;

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    int level = player->level;
    int d = player->orientation - 1;
    int x = player->pos.x, y = player->pos.y;
    size_t width = s->game.width, height = s->game.height;

    // append_to_write_buffer(s, player, "[");

    for (int i = 0; i < level; ++i) {
        for (int j = -i; j <= i; ++j) {
            int tx = (x + j * dx[(d + 3) % 4] + i * dx[d] + width) % width;
            int ty = (y + j * dy[(d + 3) % 4] + i * dy[d] + height) % height;

            tile_t* tile = &s->game.map[ty][tx];
            char** objects = get_objects_on_tile(s, tile, (coord_t){tx, ty});

            // Add each object to the response
            for (int k = 0; objects[k] != NULL; ++k) {
                // append_to_write_buffer(s, player, objects[k]);
                // append_to_write_buffer(s, player, " ");
                free(objects[k]);
            }
            free(objects);

            // append_to_write_buffer(s, player, ",");
        }
    }

    // append_to_write_buffer(s, player, "]\n");
}
