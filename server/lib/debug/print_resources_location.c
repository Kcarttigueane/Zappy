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

void print_total_resources(Tile** map, size_t height, size_t width)
{
    size_t total_food = 0;
    size_t total_linemate = 0;
    size_t total_deraumere = 0;
    size_t total_sibur = 0;
    size_t total_mendiane = 0;
    size_t total_phiras = 0;
    size_t total_thystame = 0;

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            total_food += map[i][j].quantity[0];
            total_linemate += map[i][j].quantity[1];
            total_deraumere += map[i][j].quantity[2];
            total_sibur += map[i][j].quantity[3];
            total_mendiane += map[i][j].quantity[4];
            total_phiras += map[i][j].quantity[5];
            total_thystame += map[i][j].quantity[6];
        }
    }

    printf("Total resources:\n");
    printf("food: %zu\n", total_food);
    printf("linemate: %zu\n", total_linemate);
    printf("deraumere: %zu\n", total_deraumere);
    printf("sibur: %zu\n", total_sibur);
    printf("mendiane: %zu\n", total_mendiane);
    printf("phiras: %zu\n", total_phiras);
    printf("thystame: %zu\n", total_thystame);
}
