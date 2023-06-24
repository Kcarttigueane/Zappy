/*
** EPITECH PROJECT, 2022
** server
** File description:
** handle_client_activity.c
*/

#include "colors.h"
#include "server.h"

static void handle_client_disconnection(server_data_t* s, client_t* client)
{
    // TODO : check if this is correct or not
    FD_CLR(client->fd, &s->readfds);
    close(client->fd);
    printf("Client disconnected, socket fd is %d\n", client->fd);

    LIST_REMOVE(client, entries);
    free(client);
}

void handle_client_activity(server_data_t* s)
{
    char buffer[MAX_BUFFER] = {0};

    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {
        int sd = client->fd;

        if (FD_ISSET(sd, &s->readfds)) {
            ssize_t bytes_read = read(sd, buffer, MAX_BUFFER);
            switch (bytes_read) {
                case -1:
                    perror("read");
                    exit(EXIT_FAILURE);
                case 0:
                    handle_client_disconnection(s, client);
                    break;
                default:
                    fprintf(stderr, BLUE "Client %d send the message '%s'\n" RESET, client->fd,
                            buffer);
                    buffer[strlen(buffer)] = '\0';
                    parse_client_input(s, client, buffer);
                    break;
            }
        }
    }
}
