/*
** EPITECH PROJECT, 2022
** server
** File description:
** handle_client_activity.c
*/

#include "server.h"

static void handle_client_disconnected(
    server_data_t* s,
    client_t* client)  // TODO : check if this is correct or not
{
    FD_CLR(client->fd, &s->readfds);
    close(client->fd);
    printf("Client disconnected, socket fd is %d\n", client->fd);

    LIST_REMOVE(client, entries);
    free(client);
}

static void handle_received_data(list_args_t* args, char* buffer)
{
    buffer[strlen(buffer)] = '\0';
    parse_client_input(args, buffer);
}

void handle_client_activity(server_data_t* s)
{
    char buffer[MAX_BUFFER] = {0};

    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {
        int sd = client->fd;

        if (FD_ISSET(sd, &s->readfds)) {
            printf("Client %d sent a message\n", sd);
            list_args_t args = {
                .server_data = s,
                .client = client,
            };

            int bytes_read = read(sd, buffer, MAX_BUFFER);
            (bytes_read == 0) ? handle_client_disconnected(s, client)
                              : handle_received_data(&args, buffer);
        }
    }
}
