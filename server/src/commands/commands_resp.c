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

    return 0;
}

int append_to_gui_write_buffer(server_data_t* s, const char* msg)
{
    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {
        if (client->player->is_graphical) {
            if (append_to_player_write_buffer(client, msg) == FAILURE) {
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}

void write_and_flush_client_buffer(client_t* client)
{
    ssize_t bytes_written =
        write(client->fd, client->write_buf, strlen(client->write_buf));

    if (bytes_written > 0) {
        size_t remaining_bytes = strlen(client->write_buf) - bytes_written;

        if (remaining_bytes > 0) {
            memmove(client->write_buf, client->write_buf + bytes_written,
                    remaining_bytes);
        }

        client->write_buf[remaining_bytes] = '\0';
    } else if (bytes_written == FAILURE) {
        perror("write");
    }
}