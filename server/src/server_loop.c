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

static void send_responses(server_data_t* s)
{
    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {
        if (FD_ISSET(client->fd, &s->writefds)) {
            if (strlen(client->write_buf) > 0) {
                write_and_flush_client_buffer(client);
            }
        }
    }
}

void update_life(player_t* player, int freq)
{
    int life_unit_duration = (double)126.0 / freq;
    clock_t current_time = clock();
    double elapsed_time = (double)(current_time - player->start_time) / CLOCKS_PER_SEC;

    if (elapsed_time >= life_unit_duration) {
        printf("Player %ld lost 1 life unit\n", player->id);
        player->life_units -= 1;
        player->start_time = current_time;
    }
}

void player_lifetime(server_data_t* s)
{
    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {
        if (client->player && !client->player->is_graphical && client->player->state == ACTIVE) {
            update_life(client->player, s->game.freq);

            if (client->player->inventory[FOOD] > 0) {
                client->player->inventory[FOOD] -= 1;
                client->player->life_units += 1;
                printf("Player %ld ate 1 food\n", client->player->id);
            }

            if (client->player->life_units <= 0) {
                printf("Player %ld died\n", client->player->id);
            }
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

        if (select(FD_SETSIZE, &s->readfds, &s->writefds, NULL, NULL) < 0 && errno != EINTR) {
            return handle_error("Select failed");
        }

        if (stop_server)
            break;

        if (is_game_over(s)) {
            stop_server = true;
            break;
        }

        if (FD_ISSET(s->socket_fd, &s->readfds))
            accept_new_connection(s);

        handle_client_activity(s);

        int elapsed_time = difftime(current, start);

        if (elapsed_time >= TIMER_INTERVAL) {
            spawning_resources(s, total_resources);
            time(&start);
        }
        execute_commands(s);
        send_responses(s);
        player_lifetime(s);
    }

    free_client_list(&s->game);
    return SUCCESS;
}
