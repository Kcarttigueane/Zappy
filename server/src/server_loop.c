/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** server_loop.c
*/

#include "../include/server.h"

volatile sig_atomic_t stop_server = false;

static void add_client_socket_to_set(/* clients_t* clients, */
                                     server_data_t* s)
{
    // for (size_t i = 0; i < MAX_CLIENTS; i++) {
    //     int sd = clients[i].socket_fd;
    //     if (sd > 0)
    //         FD_SET(sd, &s->readfds);
    // }
}

static int get_max_socket_descriptor(
    /* clients_t* clients, */ int server_socket)
{
    // int max_socket_descriptor = server_socket;

    // for (size_t i = 0; i < MAX_CLIENTS; i++) {
    //     int sd = clients[i].socket_fd;

    //     if (sd > 0 && sd > max_socket_descriptor)
    //         max_socket_descriptor = sd;
    // }
    // return (max_socket_descriptor + 1);
}

// void init_teams(server_data_t* s)
// {
//     for (size_t i = 0; i < MAX_NB_PLAYERS; i++) {
//         memset(&s->game.teams[i], 0, sizeof(team_t));
//         s->game.teams[i].name = s->game.team_names[i];
//         s->game.teams[i].max_players = s->game.clients_nb;
//         s->game.teams[i].players = calloc(MAX_NB_PLAYERS, sizeof(player_t*));
//         init_players(s->game.teams[i].players, s->game.teams[i].name);
//     }
// }

void reset_set(server_data_t* s, fd_set* set)
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

// static void clear_disconnected_client(clients_t* client)
// {
//     client->socket_fd = 0;
//     client->is_logged = false;

//     client->current_user_uuid[0] = '\0';
//     client->current_team_uuid[0] = '\0';
//     client->current_channel_uuid[0] = '\0';
//     client->current_thread_uuid[0] = '\0';

//     client->use_args_count = FAILURE;
// }

// static void handle_client_disconnected(int socket_fd, clients_t* client)
// {
//     close(socket_fd);
//     clear_disconnected_client(client);
//     printf("Client disconnected, socket fd is %d\n", socket_fd);
// }

// static void handle_received_data(list_args_t* args, char* buffer)
// {
//     buffer[strlen(buffer)] = '\0';
//     parse_client_input(args, buffer);
// }

// void handle_client_activity(clients_t* clients, server_data_t* s,
//                             database_t* db)
// {
//     char buffer[BUFFER_SIZE] = {0};

//     for (int i = 0; i < MAX_CLIENTS; i++) {
//         int sd = clients[i].socket_fd;

//         if (FD_ISSET(sd, &s->readfds)) {
//             list_args_t args = {.server_data = s,
//                                 .split_command = NULL,
//                                 .client = &clients[i],
//                                 .db = db,
//                                 .clients = clients};
//             int bytes_read = read(sd, buffer, BUFFER_SIZE);
//             (bytes_read == 0) ? handle_client_disconnected(sd, &clients[i])
//                               : handle_received_data(&args, buffer);
//         }
//     }
// }

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
        print_all_clients(&s->game);
        // handle_client_activity(clients, s, db);
    }

    free_client_list(&s->game);
    return SUCCESS;
}
