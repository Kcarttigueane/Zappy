/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** map.h
*/

#ifndef MAP_H_
#define MAP_H_

#include "server.h"

typedef struct {
    size_t quantity[MAX_NB_RESOURCES];
} Tile;

// ! MAP FUNCTIONS !

void print_resources_location(Tile** map, size_t height, size_t width);
void print_total_resources(Tile** map, size_t height, size_t width);

void calc_total_resources(int total_tiles, int* total_resources);
Tile** init_map(size_t width, size_t height);
void shuffle(int* array, size_t n);
void distribute_resources(Tile** map, int total_resources[], size_t height,
                          size_t width);

void spawning_resources(server_data_t* data, int* total_resources);
void free_map(Tile** map, size_t width);

#endif /* !MAP_H_ */
