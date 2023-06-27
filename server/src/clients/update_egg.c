/*
** EPITECH PROJECT, 2022
** server
** File description:
** update_egg.c
*/

#include "server.h"

void update_egg_player(game_t* game, client_t* client, char** inputs, egg_t* egg)
{
    client->player->team_name = strdup(inputs[0]);
    client->player->state = PLAYER;
    client->player->level = 1;
    client->player->id = game->next_player_id++;
    printf("New player id: %ld\n", client->player->id);
    client->player->orientation = (rand() % 4) + 1;
    memset(client->player->inventory, 0, sizeof(client->player->inventory));
    client->player->inventory[FOOD] = 10;
    client->player->start_time = clock();
    client->player->is_frozen = false;

    client->player->pos.x = egg->pos.x;
    client->player->pos.y = egg->pos.y;
    client->player->life_units = 10;

    init_command_queue(client);

    int team_index = find_team_index(game, inputs[0]);
    if (team_index == FAILURE)
        return;

    remove_egg_by_id(&game->teams[team_index], egg->id);
    game->teams[team_index].nb_players_connected++;

    enqueue_command(client, "Hatch", game->freq);
}
