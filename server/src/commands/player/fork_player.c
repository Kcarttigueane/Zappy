/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** fork_player.c
*/

#include "server.h"

void fork_player(game_t* game, client_t* client)
{
    printf("Start forking\n");

    player_t* player = client->player;

    char response[256] = {0};
    sprintf(response, PFK_FORMAT, player->id);
    append_to_gui_write_buffer(game, response);

    team_t* team = find_team_by_name(game, player->team_name);
    if (!team)
        return;

    size_t new_id = game->next_egg_id;

    egg_t* egg = create_and_add_egg(team, player->pos, new_id);
    if (!egg)
        return;

    enqueue_command(client, "End_fork", game->freq);
}

void end_fork(game_t* game, client_t* client)
{
    printf("End forking\n");

    player_t* player = client->player;

    team_t* team = find_team_by_name(game, player->team_name);
    if (!team)
        return;

    egg_t* egg = find_egg_by_id(team, game->next_egg_id);

    if (!egg) {
        printf("Egg not found\n");
        return;
    }

    game->next_egg_id += 1;
    team->max_players += 1;

    char response[256] = {0};

    sprintf(response, ENW_FORMAT, egg->id, player->id, player->pos.x, player->pos.y);
    append_to_gui_write_buffer(game, response);

    append_to_string(client->write_buf, OK_FORMAT);
    printf("New egg created with id %ld\n", egg->id);
}
