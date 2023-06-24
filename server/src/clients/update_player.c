/*
** EPITECH PROJECT, 2022
** server
** File description:
** update_player.c
*/

#include "server.h"

void update_player(game_t* game, client_t* client, char** inputs)
{
    // TODO : This should be checked to avoid duplication of data

    client->player->team_name = strdup(inputs[0]);
    client->player->state = ACTIVE;
    client->player->level = 1;
    client->player->orientation = (rand() % 4) + 1;
    client->player->inventory[FOOD] = 9;
    client->player->is_graphical = false;
    client->player->start_time = clock();
    client->player->is_frozen = false;

    int team_index = find_team_index(game, inputs[0]);
    if (team_index == FAILURE)
        return;

    game->team[team_index].nb_players_connected++;
}
