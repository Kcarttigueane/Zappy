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
        if (client->player->state == GRAPHICAL)
            continue;
        if (client->player->pos.x == pos->x && client->player->pos.y == pos->y) {
            client->player->level++;
            sprintf(response, "Current level: %ld\n", client->player->level);
            append_to_string(client->write_buf, response);
            memset(response, 0, MAX_BUFFER);
            sprintf(response, PLV_FORMAT, client->player->id, client->player->level);
            memset(response, 0, MAX_BUFFER);
        }
    }
}

void update_tile_content(game_t* game, coord_t pos, int index)
{
    incantation_requirements_t requirements = INCANTATION_REQUIREMENTS[index];
    tile_t* tile = &game->map[pos.x][pos.y];

    printf("incantation requirements: %ld %ld %ld %ld %ld %ld\n", requirements.linemate,
           requirements.deraumere, requirements.sibur, requirements.mendiane, requirements.phiras,
           requirements.thystame);

    printf("Tile content before update: %ld %ld %ld %ld %ld %ld %ld\n", tile->quantity[FOOD],
           tile->quantity[LINEMATE], tile->quantity[DERAUMERE], tile->quantity[SIBUR],
           tile->quantity[MENDIANE], tile->quantity[PHIRAS], tile->quantity[THYSTAME]);

    tile->quantity[LINEMATE] -= requirements.linemate;
    tile->quantity[DERAUMERE] -= requirements.deraumere;
    tile->quantity[SIBUR] -= requirements.sibur;
    tile->quantity[MENDIANE] -= requirements.mendiane;
    tile->quantity[PHIRAS] -= requirements.phiras;
    tile->quantity[THYSTAME] -= requirements.thystame;

    printf("Tile content after update: %ld %ld %ld %ld %ld %ld %ld\n", tile->quantity[FOOD],
           tile->quantity[LINEMATE], tile->quantity[DERAUMERE], tile->quantity[SIBUR],
           tile->quantity[MENDIANE], tile->quantity[PHIRAS], tile->quantity[THYSTAME]);

    char response[MAX_BUFFER] = {0};

    int y_cartesian = game->height - pos.y - 1;

    sprintf(response, BCT_FORMAT, pos.x, y_cartesian, tile->quantity[FOOD],
            tile->quantity[LINEMATE], tile->quantity[DERAUMERE], tile->quantity[SIBUR],
            tile->quantity[MENDIANE], tile->quantity[PHIRAS], tile->quantity[THYSTAME]);

    append_to_gui_write_buffer(game, response);
}

void end_incantation(game_t* game, client_t* client)
{
    player_t* player = client->player;

    char gui_response[256] = {0};

    printf("Ending incantation\n");
    coord_t* p_pos = &client->player->pos;

    int index = player->level - 1;

    if (!check_incantation_requirements(game, index, p_pos, player->level)) {
        int y_cartesian = game->height - p_pos->y - 1;
        sprintf(gui_response, PIE_FORMAT, p_pos->x, y_cartesian, 0);
        append_to_gui_write_buffer(game, gui_response);
        append_to_string(client->write_buf, KO_FORMAT);
    } else {
        update_player_level_and_inventory(game, p_pos);
        update_tile_content(game, *p_pos, index);
        int y_cartesian = game->height - p_pos->y - 1;
        sprintf(gui_response, PIE_FORMAT, p_pos->x, y_cartesian, 1);
        append_to_gui_write_buffer(game, gui_response);
        append_to_string(client->write_buf, OK_FORMAT);
    }
}
