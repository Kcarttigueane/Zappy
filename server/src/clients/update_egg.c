/*
** EPITECH PROJECT, 2022
** server
** File description:
** update_egg.c
*/

#include "server.h"

void update_egg_player(game_t* game, client_t* client, char** inputs, egg_t* egg)
{
    // TODO : This should be checked to avoid duplication of data

    client->player->team_name = strdup(inputs[0]);
    client->player->state = ACTIVE;
    client->player->level = 1;
    client->player->orientation = NORTH;
    client->player->inventory[FOOD] = 9;
    client->player->is_graphical = false;

    int team_index = find_team_index(game, inputs[0]);
    if (team_index == FAILURE)
        return;

    remove_egg_by_id(&game->team[team_index], egg->id);
    game->team[team_index].nb_players_connected++;
}
