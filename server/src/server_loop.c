/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** server_loop.c
*/

#include "../include/server.h"

volatile sig_atomic_t stop_server = false;

static void reset_set(server_data_t* s, fd_set* set)
{
    FD_ZERO(set);
    FD_SET(s->socket_fd, set);

    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {
        int fd = client->fd;
        if (fd > 0) {
            FD_SET(fd, set);
        }
    }
}

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
                .split_command = NULL,
                .client = client,
            };

            int bytes_read = read(sd, buffer, MAX_BUFFER);
            (bytes_read == 0) ? handle_client_disconnected(s, client)
                              : handle_received_data(&args, buffer);
        }
    }
}

int server_loop(server_data_t* s)
{
    while (!stop_server) {
        reset_set(s, &s->readfds);
        reset_set(s, &s->writefds);

        if (select(FD_SETSIZE, &s->readfds, &s->writefds, NULL, NULL) < 0 &&
            errno != EINTR) {
            return handle_error("Select failed");
        }
        if (stop_server)
            break;

        if (FD_ISSET(s->socket_fd, &s->readfds)) {
            accept_new_connection(s);
        }
        // print_all_clients(&s->game); //** DEBUG
        handle_client_activity(s);
    }

    free_client_list(&s->game);
    return SUCCESS;
}
