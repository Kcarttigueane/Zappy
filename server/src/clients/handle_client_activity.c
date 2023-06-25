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
    char response[1024] = {0};

    if (client->player->state == NONE) {
        FD_CLR(client->fd, &s->readfds);
        close(client->fd);
        printf("None Client disconnected, socket fd is %d\n", client->fd);
        remove_client_by_fd(&s->game, client->fd);
        return;
    }

    if (client->player->state == PLAYER) {
        int team_index = find_team_index(&s->game, client->player->team_name);
        if (team_index == FAILURE)
            return;

        s->game.teams[team_index].nb_players_connected--;
    }

    sprintf(response, PDI_FORMAT, client->player->id);
    append_to_gui_write_buffer(&s->game, response);
    printf("Player %ld died\n", client->player->id);
    memset(client->write_buf, 0, sizeof(client->write_buf));

    FD_CLR(client->fd, &s->readfds);
    close(client->fd);
    printf("P or G Client disconnected, socket fd is %d\n", client->fd);

    remove_client_by_fd(&s->game, client->fd);
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
                    // fprintf(stderr, BLUE "Client %d send message '%s'\n" RESET, client->fd, buffer);
                    buffer[strlen(buffer)] = '\0';
                    parse_client_input(s, client, buffer);
                    break;
            }
        }
    }
}
