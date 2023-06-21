/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** fork_player.c
*/

#include "server.h"

team_t* find_team_by_name(server_data_t* data, char* team_name)
{
    for (size_t i = 0; i < data->game.team_count; i++) {
        if (!strcmp(data->game.team_names[i], team_name))
            return &data->game.team[i];
    }
    return NULL;
}

void fork_player(list_args_t* args)
{
    printf("fork_player\n");

    player_t* player = args->client->player;

    char response[256] = {0};

    sprintf(response, PFK_FORMAT, player->id);

    append_to_gui_write_buffer(args->server_data, response);

    team_t* team = find_team_by_name(args->server_data, player->team_name);

    if (!team)
        return;

    egg_t* egg = create_and_add_egg(team, player->pos);

    if (!egg)
        return;

    char response2[256] = {0};

    sprintf(response2, ENW_FORMAT, egg->id, player->id, player->pos.x,
            player->pos.y);

    append_to_gui_write_buffer(args->server_data, response2);

    append_to_string(args->client->write_buf, OK_FORMAT);

    team->max_players += 1;

    printf("New egg created with id %ld\n", player->id);
}
