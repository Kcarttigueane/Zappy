/*
** EPITECH PROJECT, 2022
** server
** File description:
** debug_map.c
*/

#include "colors.h"
#include "server.h"

void print_resources_location(tile_t** map, size_t width, size_t height)
{
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            printf(WHITE "%zu, %zu" RESET, i, j);
            printf("]  ");
            for (int k = 0; k < MAX_NB_RESOURCES; k++) {
                printf("%sq%d: %s%zu%s  ", colors[k], k, colors[k],
                       map[i][(height - 1) - j].quantity[k], RESET);
            }
            printf("\n");
        }
    }
}

void calculate_resource_totals(tile_t* tile, size_t* totals)
{
    for (size_t k = 0; k < 7; k++) {
        totals[k] += tile->quantity[k];
    }
}

void print_total_resources(tile_t** map, size_t height, size_t width)
{
    size_t total_resources[7] = {0};

    for (size_t i = 0; i < width; i++)
        for (size_t j = 0; j < height; j++)
            calculate_resource_totals(&map[i][j], total_resources);

    printf("Total resources:\n");
    for (size_t k = 0; k < 7; k++) {
        printf("%s: %zu\n", inventory_names[k], total_resources[k]);
    }
}
