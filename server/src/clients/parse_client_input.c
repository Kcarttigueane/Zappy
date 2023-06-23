/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** parse_client_input.c
*/

#include "server.h"

static bool check_buffer_overflow(client_t* client, char* command_buff)
{
    if (strlen(command_buff) + strlen(client->read_buf) > MAX_W_BUFFER_LENGTH) {
        printf("Buffer overflow\n");
        return true;
    }

    return false;
}

void parse_client_input(server_data_t* s, client_t* client, char* received_buffer)
{
    char command_extracted[256] = {0};

    if (check_buffer_overflow(client, received_buffer))
        return;

    strcat(client->read_buf, received_buffer);

    size_t size = strlen(client->read_buf);

    for (size_t i = 0; i < size; i++) {
        if (i >= sizeof(command_extracted)) {
            printf("Command is too long\n");
            break;
        }

        command_extracted[i] = client->read_buf[i];
        if (client->read_buf[i] == '\n') {
            command_extracted[i] = '\0';

            process_command_order(&s->game, client, command_extracted);

            size_t line_length = i + 1;
            size_t remaining = size - line_length;
            memmove(client->read_buf, client->read_buf + line_length, remaining);
            client->read_buf[remaining] = '\0';

            size = remaining;
            i = 0;
        }
    }
}
