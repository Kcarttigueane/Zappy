/*
** EPITECH PROJECT, 2022
** server
** File description:
** incantation_prerequisites.c
*/

#include "server.h"

int check_nb_players_same_level(game_t* game, coord_t* pos, size_t plv_to_match)
{
    size_t num_players_same_level = 0;

    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &game->client_list, entries, temp)
    {
        if (client->player->state == GRAPHICAL)
            continue;
        if (client->player->pos.x == pos->x && client->player->pos.y == pos->y) {
            if (client->player->level == plv_to_match) {
                num_players_same_level++;
            }
        }
    }

    return num_players_same_level;
}

bool check_incantation_requirements(game_t* game, int index, coord_t* pos, size_t plv_to_match)
{
    incantation_requirements_t requirements = INCANTATION_REQUIREMENTS[index];

    printf("pos: %d %d\n", pos->x, pos->y);

    tile_t* tile = &game->map[pos->x][pos->y];

    size_t num_players_same_level = check_nb_players_same_level(game, pos, plv_to_match);

    if (num_players_same_level < requirements.num_players) {
        printf("Not enough players of the same level for the incantation\n");
        printf("num_players_same_level: %ld\n", num_players_same_level);
        return false;
    }

    size_t total_qty[MAX_NB_RESOURCES] = {0};

    debug_tile_content(tile, *pos);

    for (size_t i = 0; i < MAX_NB_RESOURCES; i++) {
        total_qty[i] = tile->quantity[i];
    }

    printf("total_qty[LINEMATE]: %ld\n", total_qty[LINEMATE]);
    printf("total_qty[DERAUMERE]: %ld\n", total_qty[DERAUMERE]);
    printf("total_qty[SIBUR]: %ld\n", total_qty[SIBUR]);
    printf("total_qty[MENDIANE]: %ld\n", total_qty[MENDIANE]);
    printf("total_qty[PHIRAS]: %ld\n", total_qty[PHIRAS]);
    printf("total_qty[THYSTAME]: %ld\n", total_qty[THYSTAME]);

    if (total_qty[LINEMATE] < requirements.linemate ||
        total_qty[DERAUMERE] < requirements.deraumere || total_qty[SIBUR] < requirements.sibur ||
        total_qty[MENDIANE] < requirements.mendiane || total_qty[PHIRAS] < requirements.phiras ||
        total_qty[THYSTAME] < requirements.thystame) {
        printf("Not enough resources for the incantation\n");
        return false;
    }
    return true;
}
