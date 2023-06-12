/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** tiles_map.c
*/

#include "server.h"

#define OOD 0.5
#define LINEMATE 0.3
#define DERAUMERE 0.15
#define SIBUR 0.1
#define MENDIANE 0.1
#define PHIRAS 0.08
#define THYSTAME 0.05

void calc_total_resources(int total_tiles, int* total_resources)
{
    total_resources[0] = total_tiles * OOD;
    total_resources[1] = total_tiles * LINEMATE;
    total_resources[2] = total_tiles * DERAUMERE;
    total_resources[3] = total_tiles * SIBUR;
    total_resources[4] = total_tiles * MENDIANE;
    total_resources[5] = total_tiles * PHIRAS;
    total_resources[6] = total_tiles * THYSTAME;
}

tile_t** init_map(size_t width, size_t height)
{
    tile_t** map = malloc(width * sizeof(tile_t*));

    for (size_t i = 0; i < width; i++) {
        map[i] = malloc(height * sizeof(tile_t));
        for (size_t j = 0; j < height; j++) {
            for (int k = 0; k < MAX_NB_RESOURCES; k++) {
                map[i][j].quantity[k] = 0;
            }
        }
    }

    return map;
}

void shuffle(int* array, size_t n)
{
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void distribute_resources(tile_t** map, int total_resources[], size_t height,
                          size_t width)
{
    size_t total_tiles = width * height;
    int* tiles = malloc(total_tiles * sizeof(int));

    for (size_t i = 0; i < total_tiles; i++) {
        tiles[i] = i;
    }

    for (int resource = 0; resource < MAX_NB_RESOURCES; resource++) {
        shuffle(tiles, total_tiles);
        for (int i = 0; i < total_resources[resource]; i++) {
            int tile_index = tiles[i % total_tiles];
            int x = tile_index / height;
            int y = tile_index % height;
            map[x][y].quantity[resource]++;
        }
    }

    free(tiles);
}

void spawning_resources(server_data_t* data, int* total_resources)
{
    printf("Spawning resources\n");

    distribute_resources(data->game.map, total_resources, data->game.height,
                         data->game.width);

    print_total_resources(data->game.map, data->game.height, data->game.width);
}

void free_map(tile_t** map, size_t width)
{
    for (size_t i = 0; i < width; i++) {
        free(map[i]);
    }
    free(map);
}
