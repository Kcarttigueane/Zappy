/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_player_position.c
*/

#include "server.h"

void get_player_position(list_args_t* args)
{
    player_t* player = get_player_from_command(args);

    if (player == NULL)
        return;

    char response[MAX_BUFFER] = {0};

    sprintf(response, PPO_FORMAT, player->id, player->pos.x, player->pos.y,
    player->orientation);

    append_to_gui_write_buffer(args->server_data, response);
}

void get_all_player_positions(list_args_t* args)
{
    char response[MAX_BUFFER] = {0};

    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &args->server_data->game.client_list, entries,
    temp) {
        if (client->player->is_graphical)
            continue;

        sprintf(response, PNW_FORMAT, client->player->id, client->player->pos.x,
        client->player->pos.y, client->player->orientation,
        client->player->level, client->player->team_name);

        append_to_gui_write_buffer(args->server_data, response);

        memset(response, 0, MAX_BUFFER);
    }
}
