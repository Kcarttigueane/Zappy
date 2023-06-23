/*
** EPITECH PROJECT, 2022
** server
** File description:
** end_incantation.c
*/

#include "server.h"

void update_player_level_and_inventory(game_t* game, coord_t* pos)
{
    char response[MAX_BUFFER] = {0};
    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &game->client_list, entries, temp)
    {
        if (client->player->is_graphical)
            continue;
        if (client->player->pos.x == pos->x && client->player->pos.y == pos->y) {
            client->player->level++;
            sprintf(response, "Current level: %ld\n", client->player->level);
            append_to_string(client->write_buf, response);
            memset(response, 0, MAX_BUFFER);
            sprintf(response, PLV_FORMAT, client->player->id, client->player->level);
        }
    }
}

void update_tile_content(game_t* game, coord_t pos, incantation_requirements_t requirements)
{
    tile_t* tile = &game->map[pos.y][pos.x];

    tile->quantity[LINEMATE] -= requirements.linemate;
    tile->quantity[DERAUMERE] -= requirements.deraumere;
    tile->quantity[SIBUR] -= requirements.sibur;
    tile->quantity[MENDIANE] -= requirements.mendiane;
    tile->quantity[PHIRAS] -= requirements.phiras;
    tile->quantity[THYSTAME] -= requirements.thystame;

    char response[MAX_BUFFER] = {0};

    sprintf(response, BCT_FORMAT, pos.x, pos.y, tile->quantity[FOOD], tile->quantity[LINEMATE],
            tile->quantity[DERAUMERE], tile->quantity[SIBUR], tile->quantity[MENDIANE],
            tile->quantity[PHIRAS], tile->quantity[THYSTAME]);

    append_to_gui_write_buffer(game, response);
}

void end_incantation(game_t* game, client_t* client)
{
    (void)game;
    (void)client;

    player_t* player = client->player;

    printf("Ending incantation\n");
    coord_t* p_pos = &client->player->pos;

    if (!check_incantation_requirements(game, player->level - 1, p_pos, player->level)) {
        append_to_string(client->write_buf, KO_FORMAT);
        return;
    }

    update_player_level_and_inventory(game, p_pos);

    update_tile_content(game, *p_pos, INCANTATION_REQUIREMENTS[player->level - 1]);
}
