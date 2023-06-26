/*
** EPITECH PROJECT, 2022
** server
** File description:
** start_incantation.c
*/

#include "server.h"

void start_incantation(game_t* game, client_t* client)
{
    coord_t* p_pos = &client->player->pos;
    int requirement_index = client->player->level - 1;

    if (!check_incantation_requirements(game, requirement_index, p_pos, client->player->level)) {
        append_to_string(client->write_buf, KO_FORMAT);
        return;
    }

    // The requirements are met, freeze the player and start the incantation
    client_t *curr_client, *temp;

    char gui_response[256] = {0};
    sprintf(gui_response, "pic %d %d %ld ", p_pos->x, p_pos->y, client->player->level);

    append_to_gui_write_buffer(game, gui_response);

    LIST_FOREACH_SAFE(curr_client, &game->client_list, entries, temp)
    {
        if (curr_client->player->state == GRAPHICAL)
            continue;
        if (curr_client->player->pos.x == p_pos->x && curr_client->player->pos.y == p_pos->y) {
            curr_client->player->is_frozen = true;
            append_to_string(client->write_buf, "Elevation underway\n");
            memset(gui_response, 0, 256);
            sprintf(gui_response, "%ld ", client->player->id);
        }
    }

    append_to_gui_write_buffer(game, gui_response);

    append_to_gui_write_buffer(game, "\n");

    enqueue_command(client, "End_of_incantation", game->freq);
}
