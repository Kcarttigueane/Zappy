/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** accept_new_client.c
*/

#include "server.h"

int initialize_players(server_data_t* s, client_t* client)
{
    client->player = (player_t*)calloc(1, sizeof(player_t));

    if (!client->player)
        return handle_failure("Failed to allocate memory for new player");

    printf("New client connected with id %i\n", client->fd);

    client->player->is_graphical = false;
    client->player->id = s->game.next_player_id++;
    client->player->pos.x = rand() % s->game.width;
    client->player->pos.y = rand() % s->game.height;
    client->player->orientation = NORTH;
    client->player->level = 1;
    memset(client->player->inventory, 0, sizeof(client->player->inventory));
    client->player->life_units = 10;

    client->player->state = NONE;
    init_command_queue(client);

    return SUCCESS;
}

void initialize_client(server_data_t* s, client_t* new_client,
                       struct sockaddr_in address, int new_socket)
{
    new_client->fd = new_socket;
    new_client->address = address;
    new_client->player = NULL;
    memset(new_client->write_buf, 0, MAX_W_BUFFER_LENGTH);
    memset(new_client->read_buf, 0, MAX_BUFFER);

    initialize_players(s, new_client);
    add_client(&s->game, new_client);
}

void accept_new_connection(server_data_t* s)
{
    client_t* new_client = (client_t*)calloc(1, sizeof(client_t));

    if (!new_client) {
        perror("Failed to allocate memory for new client");
        return;
    }

    int new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((new_socket = accept(s->socket_fd, (struct sockaddr*)&address,
                             (socklen_t*)&addrlen)) < 0) {
        handle_error("Accept failed");
    }
    dprintf(new_socket, "WELCOME\n");

    initialize_client(s, new_client, address, new_socket);
}
