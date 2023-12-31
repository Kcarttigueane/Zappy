/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-kevin.carttigueane
** File description:
** resources_functions
*/

#include "server.h"

void add_current_resources(tile_t** map, int current_resources[], size_t i, size_t j)
{
    for (int resource = 0; resource < MAX_NB_RESOURCES; resource++)
        current_resources[resource] += map[i][j].quantity[resource];
}

void calculate_current_resources(tile_t** map, int current_resources[], size_t height, size_t width)
{
    memset(current_resources, 0, MAX_NB_RESOURCES * sizeof(int));

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            add_current_resources(map, current_resources, i, j);
        }
    }
}

void spawning_resources(game_t *game, int total_resources[], size_t height, size_t width)
{
    printf("Spawning resources...\n");

    int current_resources[MAX_NB_RESOURCES];
    size_t total_tiles = width * height;
    int* tiles = malloc(total_tiles * sizeof(int));
    calculate_current_resources(game->map, current_resources, height, width);
    tile_t **map = game->map;

    for (size_t i = 0; i < total_tiles; i++)
        tiles[i] = i;

    for (size_t i = 0; i < total_tiles; i++) {
        size_t j = i + rand() % (total_tiles - i);
        int t = tiles[j];
        tiles[j] = tiles[i];
        tiles[i] = t;
    }

    for (int resource = 0; resource < MAX_NB_RESOURCES; resource++) {
        size_t resource_to_spawn = total_resources[resource] - current_resources[resource];

        for (size_t i = 0; i < resource_to_spawn; i++) {
            int tile_index = tiles[i % total_tiles];
            int x = tile_index / height;
            int y = tile_index % height;
            map[x][y].quantity[resource]++;
        }
    }

    get_all_tiles_content(game, NULL);
    free(tiles);
}

