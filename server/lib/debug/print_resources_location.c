/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** print_resources_location.c
*/

#include "colors.h"
#include "server.h"

void print_resources_location(Tile** map, size_t height, size_t width)
{
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            printf("Tile pos [");
            printf(WHITE "%zu, %zu" RESET, i, j);
            printf("]  ");
            for (int k = 0; k < MAX_NB_RESOURCES; k++) {
                printf("%sq%d: %s%zu%s  ", colors[k], k, colors[k],
                       map[i][j].quantity[k], RESET);
            }
            printf("\n");
        }
    }
}
