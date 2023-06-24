/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** map.h
*/

#ifndef MAP_H_
    #define MAP_H_

    #define OOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY SIBUR_DENSITY
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05

    #define CALC_TOTAL_RESOURCES(total_tiles)                                 \
        {                                                                     \
            (total_tiles) * OOD_DENSITY, (total_tiles)*LINEMATE_DENSITY,      \
                (total_tiles)*DERAUMERE_DENSITY, (total_tiles)*SIBUR_DENSITY, \
                (total_tiles)*MENDIANE_DENSITY, (total_tiles)*PHIRAS_DENSITY, \
                (total_tiles)*THYSTAME_DENSITY                                \
        }

    #define TIMER_INTERVAL 20

    #include "server.h"

    typedef struct tile_s {
        size_t quantity[MAX_NB_RESOURCES];
    } tile_t;

// ! MAP FUNCTIONS !

void print_resources_location(tile_t** map, size_t height, size_t width);
void print_total_resources(tile_t** map, size_t height, size_t width);

tile_t** init_map(size_t width, size_t height);
void shuffle(int* array, size_t n);
void distribute_resources(tile_t** map, int total_resources[], size_t height,
size_t width);

void spawning_resources(server_data_t* data, int* total_resources);
void free_map(tile_t** map, size_t width);

tile_t* get_tile(tile_t** map, int x, int y);

#endif /* !MAP_H_ */
