/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** start_incantation.c
*/

#include "server.h"

bool check_incantation_requirements(game_t* game, int index, coord_t* pos,
                                    size_t player_level_to_match)
{
    incantation_requirements_t requirements = INCANTATION_REQUIREMENTS[index];

    printf("pos: %d %d\n", pos->x, pos->y);

    tile_t* tile = &game->map[pos->y][pos->x];

    printf("tile linemante: %ld\n", tile->quantity[LINEMATE]);

    size_t num_players_same_level = 0;

    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &game->client_list, entries, temp)
    {
        if (client->player->is_graphical)
            continue;
        if (client->player->pos.x == pos->x &&
            client->player->pos.y == pos->y) {
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

void start_incantation(list_args_t* args)
{
    printf("start_incantation\n");
    coord_t* p_pos = &args->client->player->pos;

    if (!check_incantation_requirements(&args->server_data->game,
                                        args->client->player->level - 1, p_pos,
                                        args->client->player->level)) {
        append_to_string(args->client->write_buf, KO_FORMAT);
        return;
    }

    // The requirements are met, freeze the player and start the incantation
    client_t *client, *temp;
    char gui_response[256] = {0};
    sprintf(gui_response, "pic %d %d %ld ", p_pos->x, p_pos->y,
            args->client->player->level);

    append_to_gui_write_buffer(args->server_data, gui_response);

    LIST_FOREACH_SAFE(client, &args->server_data->game.client_list, entries,
                      temp)
    {
        if (client->player->is_graphical)
            continue;
        if (client->player->pos.x == p_pos->x &&
            client->player->pos.y == p_pos->y) {
            client->player->is_frozen = true;
            append_to_string(client->write_buf, "Elevation underway\n");
            memset(gui_response, 0, 256);
            sprintf(gui_response, "%ld ", client->player->id);
        }
    }

    append_to_gui_write_buffer(args->server_data, gui_response);

    append_to_gui_write_buffer(args->server_data, "\n");

    enqueue_command(args->client, "End_of_incantation",
                    args->server_data->game.freq);
}

void update_player_level_and_inventory(game_t* game, coord_t* pos)
{
    char response[MAX_BUFFER] = {0};
    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &game->client_list, entries, temp)
    {
        if (client->player->is_graphical)
            continue;
        if (client->player->pos.x == pos->x &&
            client->player->pos.y == pos->y) {
            client->player->level++;
            sprintf(response, "Current level: %ld\n", client->player->level);
            append_to_string(client->write_buf, response);
            memset(response, 0, MAX_BUFFER);
            sprintf(response, PLV_FORMAT, client->player->id,
                    client->player->level);
        }
    }
}

void update_tile_content(list_args_t* args, coord_t pos,
                         incantation_requirements_t requirements)
{
    tile_t* tile = &args->server_data->game.map[pos.y][pos.x];

    tile->quantity[LINEMATE] -= requirements.linemate;
    tile->quantity[DERAUMERE] -= requirements.deraumere;
    tile->quantity[SIBUR] -= requirements.sibur;
    tile->quantity[MENDIANE] -= requirements.mendiane;
    tile->quantity[PHIRAS] -= requirements.phiras;
    tile->quantity[THYSTAME] -= requirements.thystame;

    char response[MAX_BUFFER] = {0};

    sprintf(response, BCT_FORMAT, pos.x, pos.y, tile->quantity[FOOD],
            tile->quantity[LINEMATE], tile->quantity[DERAUMERE],
            tile->quantity[SIBUR], tile->quantity[MENDIANE],
            tile->quantity[PHIRAS], tile->quantity[THYSTAME]);

    append_to_gui_write_buffer(args->server_data, response);
}

void end_incantation(list_args_t* args)
{
    printf("Ending incantation\n");
    coord_t* p_pos = &args->client->player->pos;

    if (!check_incantation_requirements(&args->server_data->game,
                                        args->client->player->level - 1, p_pos,
                                        args->client->player->level)) {
        append_to_string(args->client->write_buf, KO_FORMAT);
        return;
    }

    update_player_level_and_inventory(&args->server_data->game, p_pos);

    update_tile_content(
        args, *p_pos,
        INCANTATION_REQUIREMENTS[args->client->player->level - 1]);
}
