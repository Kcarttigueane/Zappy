/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** connect_nbr.c
*/

#include "server.h"

void connect_nbr(list_args_t* args)
{
    char response[24] = {0};
    char *team_name = args->client->player->team_name;

    team_t* team = find_team_by_name(args->server_data, team_name);

    if (!team)
        return;

    sprintf(response, "%ld\n", team->max_players - team->nb_players_connected);

    append_to_string(args->client->write_buf, response);
}
