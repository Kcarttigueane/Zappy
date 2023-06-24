/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** tiles_map.c
*/

#include "server.h"

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


void spawning_resources(server_data_t* data, int* total_resources)
{
    printf("Spawning resources\n");

    distribute_resources(data->game.map, total_resources,
                         data->game.height, data->game.width);

    // print_total_resources(data->game.map, data->game.height, data->game.width);
}


void free_map(tile_t** map, size_t width)
{
    for (size_t i = 0; i < width; i++) {
        free(map[i]);
    }
    free(map);
}
