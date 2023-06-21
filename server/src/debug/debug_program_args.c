/*
** EPITECH PROJECT, 2022
** server
** File description:
** debug_program_args.c
*/

#include "colors.h"
#include "server.h"

void debug_program_args(server_data_t* s)
{
    fprintf(stdout, YELLOW "%s" RESET "\n",
    "============  Start DEBUG program args ============");

    printf("PORT: %d\n", s->PORT);
    printf("WIDTH: %zu\n", s->game.width);
    printf("HEIGHT: %zu\n", s->game.height);
    printf("CLIENTS_NB: %zu\n", s->game.clients_nb);
    printf("FREQ: %zu\n", s->game.freq);
    printf("TEAM_COUNT: %zu\n", s->game.team_count);

    for (size_t i = 0; i < s->game.team_count; i++)
        printf("TEAM_NAME: %s\n", s->game.team_names[i]);

    fprintf(stdout, YELLOW "%s" RESET "\n",
    "=============  End DEBUG program args =============\n");
}
