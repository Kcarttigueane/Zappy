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

void send_responses(server_data_t* s)
{
    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {
        if (strlen(client->write_buf) > 0) {
            write_and_flush_client_buffer(client);
        }
    }
}

int server_loop(server_data_t* s)
{
    int total_tiles = s->game.width * s->game.height;
    int total_resources[MAX_NB_RESOURCES] = CALC_TOTAL_RESOURCES(total_tiles);

    time_t start, current;

    time(&start);

    while (!stop_server) {
        time(&current);

        reset_set(s, &s->readfds);
        reset_set(s, &s->writefds);

        if (select(FD_SETSIZE, &s->readfds, &s->writefds, NULL, NULL) < 0 &&
            errno != EINTR) {
            return handle_error("Select failed");
        }
        if (stop_server)
            break;

        if (FD_ISSET(s->socket_fd, &s->readfds))
            accept_new_connection(s);

        handle_client_activity(s);

        int elapsed_time = difftime(current, start);

        if (elapsed_time >= TIMER_INTERVAL) {
            spawning_resources(s, total_resources);
            print_total_resources(s->game.map, s->game.height, s->game.width);
            time(&start);
        }
        execute_commands(s);
        send_responses(s);
    }

    free_client_list(&s->game);
    return SUCCESS;
}
