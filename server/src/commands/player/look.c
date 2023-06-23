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

int get_nb_element_on_tile(tile_t* tile)
{
    int nb = 0;

    for (size_t i = 0; i < MAX_NB_RESOURCES; ++i)
        nb += tile->quantity[i];

    return nb;
}

char** get_objects_on_tile(server_data_t* s, tile_t* tile, coord_t pos)
{
    size_t nb_players = get_nbr_player_on_tile(s, pos);

    int nb_objects = get_nb_element_on_tile(tile) + nb_players;

    char** objects = (char**)calloc(nb_objects, sizeof(char*));

    if (!objects) {
        perror("Failed to allocate memory for objects");
        return NULL;
    }

    size_t i = 0;

    for (; i < nb_players; ++i) {
        objects[i] = strdup("player");
    }

    for (size_t j = 0; j < MAX_NB_RESOURCES; j++) {
        if (tile->quantity[j] > 0) {
            printf("inventory_name: %s\n", inventory_names[j]);
            for (size_t k = 0; k < tile->quantity[j]; ++k, ++i) {
                objects[i] = strdup(inventory_names[j]);
                if (!objects[i]) {
                    perror("Failed to allocate memory for object name");
                    for (size_t j = 0; j < i; ++j)
                        free(objects[j]);
                    free(objects);
                    return NULL;
                }
            }
        }
    }

    debug_word_array(objects);

    return objects;
}

void look(list_args_t* args)
{
    server_data_t* s = args->server_data;
    player_t* player = args->client->player;

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    size_t level = 2;
    int d = player->orientation - 1;
    int x = player->pos.x, y = player->pos.y;
    size_t width = s->game.width, height = s->game.height;

    append_to_string(args->client->write_buf, "[");

    for (int i = 0; i <= (int)level; ++i) {
        for (int j = -i; j <= i; ++j) {
            int tx = (x + j * dx[(d + 3) % 4] + i * dx[d] + width) % width;
            int ty = (y + j * dy[(d + 3) % 4] + i * dy[d] + height) % height;

            printf("tx: %d, ty: %d\n", tx, ty);

            tile_t* tile = &s->game.map[ty][tx];
            debug_tile_content(tile);
            char** objects = get_objects_on_tile(s, tile, (coord_t){tx, ty});

            for (int k = 0; objects[k] != NULL; ++k) {
                append_to_string(args->client->write_buf, objects[k]);
                append_to_string(args->client->write_buf, " ");
                free(objects[k]);
            }
            free(objects);

            append_to_string(args->client->write_buf, ",");
        }
    }
    append_to_string(args->client->write_buf, "]\n");
}
