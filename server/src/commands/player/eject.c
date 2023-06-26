/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** eject.c
*/

#include "server.h"

void move_client_based_on_orientation(client_t* client, game_t* game, orientation_t orientation)
{
    player_t* player = client->player;
    size_t width = game->width;
    size_t height = game->height;

    switch (orientation) {
        case NORTH:
            player->pos.y++;
            if (player->pos.y >= (int)height)
                player->pos.y = 0;
            break;
        case SOUTH:
            player->pos.y--;
            if (player->pos.y < 0)
                player->pos.y = height - 1;
            break;
        case WEST:
            player->pos.x--;
            if (player->pos.x < 0)
                player->pos.x = width - 1;
            break;
        case EAST:
            player->pos.x++;
            if (player->pos.x >= (int)width)
                player->pos.x = 0;
            break;
    }
}

void send_eject_message(client_t* client, int direction)
{
    char message[64] = {0};
    sprintf(message, "eject: %d\n", direction);
    append_to_string(client->write_buf, message);
    memset(message, 0, sizeof(message));
}

void send_eject_response_gui(game_t* game, client_t* client)
{
    char gui_message[64] = {0};
    sprintf(gui_message, PEX_FORMAT, client->player->id);
    append_to_gui_write_buffer(game, gui_message);
    memset(gui_message, 0, sizeof(gui_message));
    sprintf(gui_message, PPO_FORMAT, client->player->id, client->player->pos.x,
            client->player->pos.y, client->player->orientation);
    append_to_gui_write_buffer(game, gui_message);
}

void destroy_eggs_on_tile(game_t* game, coord_t tile_pos)
{
    char gui_message[64] = {0};

    for (size_t i = 0; i < game->team_count; i++) {
        team_t* team = &game->teams[i];

        egg_t *e, *temp;

        LIST_FOREACH_SAFE(e, &team->egg_list, entries, temp)
        {
            if (e->pos.x == tile_pos.x && e->pos.y == tile_pos.y) {
                sprintf(gui_message, EDI_FORMAT, e->id);
                append_to_gui_write_buffer(game, gui_message);
                memset(gui_message, 0, sizeof(gui_message));
                LIST_REMOVE(e, entries);
                free(e);
                team->max_players--;
            }
        }
    }
}

void eject(game_t* game, client_t* client)
{
    client_t *p_to_move, *temp;

    LIST_FOREACH_SAFE(p_to_move, &game->client_list, entries, temp)
    {
        if (p_to_move->player->id != client->player->id &&
            p_to_move->player->pos.x == client->player->pos.x &&
            p_to_move->player->pos.y == client->player->pos.y) {
            move_client_based_on_orientation(p_to_move, game, client->player->orientation);
            send_eject_message(p_to_move, client->player->orientation);
            send_eject_response_gui(game, p_to_move);
        }
    }

    destroy_eggs_on_tile(game, client->player->pos);
}
