/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** fork_player.c
*/

#include "server.h"

void fork_player(game_t* game, client_t* client)
{
    printf("fork_player\n");

    player_t* player = client->player;

    char response[256] = {0};

    sprintf(response, PFK_FORMAT, player->id);

    append_to_gui_write_buffer(game, response);

    team_t* team = find_team_by_name(game, player->team_name);

    if (!team)
        return;

    egg_t* egg = create_and_add_egg(team, player->pos);

    if (!egg)
        return;

    char response2[256] = {0};

    sprintf(response2, ENW_FORMAT, egg->id, player->id, player->pos.x, player->pos.y);

    append_to_gui_write_buffer(game, response2);

    append_to_string(client->write_buf, OK_FORMAT);

    team->max_players += 1;

    printf("New egg created with id %ld\n", player->id);
}

void end_fork(game_t* game, client_t* client)
{

}
