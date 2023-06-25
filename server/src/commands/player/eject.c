/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** eject.c
*/

#include "server.h"

void move_client_based_on_orientation(client_t* client)
{
    switch (client->player->orientation) {
        case NORTH:
            client->player->pos.y -= 1;
            break;
        case SOUTH:
            client->player->pos.y += 1;
            break;
        case EAST:
            client->player->pos.x += 1;
            break;
        case WEST:
            client->player->pos.x -= 1;
            break;
        default:
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
            }
        }
    }
}

void eject(game_t* game, client_t* client)
{
    client_t *cur_client, *temp;

    LIST_FOREACH_SAFE(cur_client, &game->client_list, entries, temp)
    {
        if (cur_client != client && cur_client->player->pos.x == client->player->pos.x &&
            cur_client->player->pos.y == client->player->pos.y) {
            move_client_based_on_orientation(cur_client);
            send_eject_message(cur_client, client->player->orientation);
            send_eject_response_gui(game, cur_client);
        }
    }

    destroy_eggs_on_tile(game, client->player->pos);
}
