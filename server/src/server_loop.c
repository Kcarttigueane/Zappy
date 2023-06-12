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
                .client = client,
            };

            int bytes_read = read(sd, buffer, MAX_BUFFER);
            (bytes_read == 0) ? handle_client_disconnected(s, client)
                              : handle_received_data(&args, buffer);
        }
    }
}

void executed_commands(server_data_t* s)
{
    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp) {}
}

size_t find_player_command_index(char* command_name)
{
    for (size_t i = 0; i < PLAYER_COMMANDS_SIZE; i++) {
        if (strcmp(command_name, PLAYER_COMMANDS[i].name) == 0) {
            return i;
        }
    }
    return FAILURE;
}

void execute_commands(server_data_t* s)
{
    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {
        if (!is_command_queue_empty(client)) {

                size_t index = find_player_command_index(
                    client->player->command_queue
                        .commands[client->player->command_queue.front]);

                if (index == (size_t)FAILURE) {
                    printf("Player : Command not found\n");
                    dequeue_command(client);
                    continue;
                }

                PLAYER_COMMANDS[index].function();
                dequeue_command(client);
        }
        if (!client->player->is_graphical) {
            //
        }
    }
}

int server_loop(server_data_t* s)
{
    int total_tiles = s->game.width * s->game.height;
    int total_resources[MAX_NB_RESOURCES] = CALC_TOTAL_RESOURCES(total_tiles);

    time_t start, current;

    //     // Get the current time as the start time
    time(&start);

    while (!stop_server) {
        time(&current);  // Get the current time

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
        // print_all_clients(&s->game); // DEBUG
        handle_client_activity(s);

        int elapsed_time = difftime(current, start);

        if (elapsed_time >= TIMER_INTERVAL) {
            spawning_resources(s, total_resources);
            print_total_resources(s->game.map, s->game.height, s->game.width);
            time(&start);
        }
        execute_commands(s);
        // send responses to the available clients
    }

    free_client_list(&s->game);
    return SUCCESS;
}
