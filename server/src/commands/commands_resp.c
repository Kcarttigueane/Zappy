/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** commands_resp.c
*/

#include "server.h"

int append_to_player_write_buffer(client_t* client, const char* msg)
{
    if (strlen(client->write_buf) + strlen(msg) + 1 > MAX_W_BUFFER_LENGTH) {
        return FAILURE;
    }

    strncat(client->write_buf, msg,
            MAX_W_BUFFER_LENGTH - strlen(client->write_buf) - 1);

    return SUCCESS;
}

int append_to_gui_write_buffer(game_t *game, char* msg)
{
    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &game->client_list, entries, temp)
    {
        if (client->player->is_graphical) {
            append_to_string(client->write_buf, msg);
        }
    }

    return SUCCESS;
}

void write_and_flush_client_buffer(client_t* client)
{
    size_t i = 0;
    char* full_response = client->write_buf;
    char resp_to_send[MAX_BUFFER] = {0};

    while (full_response[i] != '\0') {
        resp_to_send[i] = full_response[i];
        if (resp_to_send[i] == '\n') {
            resp_to_send[i + 1] = '\0';
            dprintf(client->fd, "%s", resp_to_send);
            memmove(full_response, full_response + i + 1,
                    strlen(full_response + i + 1) + 1);
            i = 0;
            return;
        } else
            i++;
    }
}
