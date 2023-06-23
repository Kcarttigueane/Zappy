/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** connect_nbr.c
*/

#include "server.h"

void connect_nbr(game_t* game, client_t* client)
{
    char response[24] = {0};
    char* team_name = client->player->team_name;

    team_t* team = find_team_by_name(game, team_name);

    if (!team)
        return;

    sprintf(response, "%ld\n", team->max_players - team->nb_players_connected);

    append_to_string(client->write_buf, response);
}
