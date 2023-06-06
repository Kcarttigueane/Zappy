/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** print_total_map_resources.c
*/

#include "colors.h"
#include "lib.h"
#include "server.h"

void print_total_map_resources(Tile** map, size_t height, size_t width)
{
    int total_food = 0;
    int total_linemate = 0;
    int total_deraumere = 0;
    int total_sibur = 0;
    int total_mendiane = 0;
    int total_phiras = 0;
    int total_thystame = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // total_food += map[x][y].resources.food;
            // total_linemate += map[x][y].resources.linemate;
            // total_deraumere += map[x][y].resources.deraumere;
            // total_sibur += map[x][y].resources.sibur;
            // total_mendiane += map[x][y].resources.mendiane;
            // total_phiras += map[x][y].resources.phiras;
            // total_thystame += map[x][y].resources.thystame;
        }
    }

    printf(RED "Food: %d\n" RESET, total_food);
    printf(WHITE "Linemate: %d\n" RESET, total_linemate);
    printf(CYAN "Deraumere: %d\n" RESET, total_deraumere);
    printf(GREEN "Sibur: %d\n" RESET, total_sibur);
    printf(YELLOW "Mendiane: %d\n" RESET, total_mendiane);
    printf(BLUE "Phiras: %d\n" RESET, total_phiras);
    printf(PURPLE "Thystame: %d\n" RESET, total_thystame);
}
