/*
** EPITECH PROJECT, 2022
** server
** File description:
** debug_tile_content.c
*/

#include "colors.h"
#include "server.h"

void debug_tile_content(tile_t* tile, coord_t pos)
{
    fprintf(stdout, GREEN "%s" RESET "\n", "============  Start DEBUG tile content ============");

    printf("X: %d\n", pos.x);
    printf("FOOD: %zu\n", tile->quantity[FOOD]);
    printf("LINEMATE: %zu\n", tile->quantity[LINEMATE]);
    printf("DERAUMERE: %zu\n", tile->quantity[DERAUMERE]);
    printf("SIBUR: %zu\n", tile->quantity[SIBUR]);
    printf("MENDIANE: %zu\n", tile->quantity[MENDIANE]);
    printf("PHIRAS: %zu\n", tile->quantity[PHIRAS]);
    printf("THYSTAME: %zu\n", tile->quantity[THYSTAME]);

    fprintf(stdout, GREEN "%s" RESET "\n", "=============  End DEBUG tile content =============\n");
}
