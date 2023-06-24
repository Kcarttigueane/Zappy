/*
** EPITECH PROJECT, 2022
** server
** File description:
** update_normal_player.c
*/

#include "server.h"

void update_normal_player(game_t* game, client_t* client, char** inputs)
{
    // TODO : This should be checked to avoid duplication of data

    client->player->team_name = strdup(inputs[0]);
    client->player->state = PLAYER;
    client->player->level = 1;
    client->player->id = game->next_player_id++;
    client->player->orientation = (rand() % 4) + 1;
    memset(client->player->inventory, 0, sizeof(client->player->inventory));
    client->player->inventory[FOOD] = 10;
    client->player->start_time = clock();
    client->player->is_frozen = false;
    client->player->pos.x = rand() % game->width;
    client->player->pos.y = rand() % game->height;
    client->player->life_units = 10;

    init_command_queue(client);

    int team_index = find_team_index(game, inputs[0]);
    if (team_index == FAILURE)
        return;

    game->team[team_index].nb_players_connected++;
}
