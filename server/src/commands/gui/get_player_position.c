/*
** EPITECH PROJECT, 2022
** server
** File description:
** get_player_position.c
*/

#include "server.h"

void get_player_position(game_t* game, client_t* client)
{
    char* command = peek_command(client);
    player_t* player = get_player_from_command(game, command);

    if (player == NULL)
        return;

    char response[MAX_BUFFER] = {0};

    int y = game->height - player->pos.y - 1;

    sprintf(response, PPO_FORMAT, player->id, player->pos.x, y, player->orientation);

    append_to_gui_write_buffer(game, response);
}

void get_all_player_positions(game_t* game)
{
    char response[MAX_BUFFER] = {0};

    client_t *curr_client, *temp;

    LIST_FOREACH_SAFE(curr_client, &game->client_list, entries, temp)
    {
        if (curr_client->player->state == GRAPHICAL || curr_client->player->state == NONE)
            continue;

        int y = game->height - curr_client->player->pos.y - 1;
        sprintf(response, PNW_FORMAT, curr_client->player->id, curr_client->player->pos.x, y,
                curr_client->player->orientation, curr_client->player->level,
                curr_client->player->team_name);

        append_to_gui_write_buffer(game, response);

        memset(response, 0, MAX_BUFFER);
    }
}
