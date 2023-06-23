/*
** EPITECH PROJECT, 2022
** server
** File description:
** incantation_prerequesites.c
*/

#include "server.h"

bool check_incantation_requirements(game_t* game, int index, coord_t* pos,
                                    size_t player_level_to_match)
{
    incantation_requirements_t requirements = INCANTATION_REQUIREMENTS[index];

    printf("pos: %d %d\n", pos->x, pos->y);

    tile_t* tile = &game->map[pos->y][pos->x];

    printf("tile linemate: %ld\n", tile->quantity[LINEMATE]);

    size_t num_players_same_level = 0;

    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &game->client_list, entries, temp)
    {
        if (client->player->is_graphical)
            continue;
        if (client->player->pos.x == pos->x && client->player->pos.y == pos->y) {
            if (client->player->level == player_level_to_match) {
                num_players_same_level++;
            }
        }
    }

    if (num_players_same_level < requirements.num_players) {
        printf("num_players_same_level: %ld\n", num_players_same_level);
        return false;
    }

    // tile_t* tile = &game->map[pos->y][pos->x];

    size_t total_qty[MAX_NB_RESOURCES] = {0};

    debug_tile_content(tile);

    for (size_t i; i < MAX_NB_RESOURCES; i++) {
        total_qty[i] = tile->quantity[i];
    }

    printf("total_qty[LINEMATE]: %ld\n", total_qty[LINEMATE]);
    printf("total_qty[DERAUMERE]: %ld\n", total_qty[DERAUMERE]);
    printf("total_qty[SIBUR]: %ld\n", total_qty[SIBUR]);
    printf("total_qty[MENDIANE]: %ld\n", total_qty[MENDIANE]);
    printf("total_qty[PHIRAS]: %ld\n", total_qty[PHIRAS]);
    printf("total_qty[THYSTAME]: %ld\n", total_qty[THYSTAME]);

    if (total_qty[LINEMATE] < requirements.linemate) {
        printf("Not enough resources\n");
        return false;
    }

    return true;
}
