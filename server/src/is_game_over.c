/*
** EPITECH PROJECT, 2022
** server
** File description:
** is_game_over.c
*/

#include "server.h"

bool is_game_over(server_data_t* s)
{
    game_t* game = &s->game;
    char response[MAX_BUFFER] = {0};

    for (size_t i = 0; i < s->game.team_count; i++) {
        int players_at_max_level = 0;
        client_t *client, *temp;

        LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
        {
            if (client->player->team_name != NULL &&
                !strcmp(client->player->team_name, game->team_names[i])) {
                if (client->player->level >= MAX_LEVEL) {
                    ++players_at_max_level;
                }
            }
        }

        if (players_at_max_level >= WINNING_PLAYERS) {
            sprintf(response, SEG_FORMAT, game->team_names[i]);
            append_to_gui_write_buffer(s, response);
            return true;
        }
        players_at_max_level = 0;
    }

    return false;
}
