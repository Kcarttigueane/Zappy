/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** fork_player.c
*/

#include "server.h"

void fork_player(__attribute_maybe_unused__ list_args_t* args)
{
    printf("fork_player\n");

    player_t* player = args->client->player;

    client_t* new_client = (client_t*)calloc(1, sizeof(client_t));

    if (!new_client)
        return;

    memset(new_client->write_buf, 0, MAX_W_BUFFER_LENGTH);
    memset(new_client->read_buf, 0, MAX_BUFFER);
    new_client->player = NULL;

    new_client->player = (player_t*)calloc(1, sizeof(player_t));

    if (!new_client->player)
        return;

    new_client->player->is_graphical = false;
    new_client->player->id = args->server_data->game.next_player_id++;
    new_client->player->pos.x = player->pos.x;
    new_client->player->pos.y = player->pos.y;
    new_client->player->orientation = NORTH;
    new_client->player->level = 1;
    memset(new_client->player->inventory, 0,
           sizeof(new_client->player->inventory));
    new_client->player->life_units = 10;
    // new_client->player->last_eat_time; // TODO : set this to current time I guess
    new_client->player->state = EGG;

    init_command_queue(new_client);
    add_client(&args->server_data->game, new_client);

    char response[256] = {0};

    sprintf(response, PFK_FORMAT, player->id);

    append_to_gui_write_buffer(args->server_data, response);

    printf("New egg created with id %ld\n", new_client->player->id);
}
