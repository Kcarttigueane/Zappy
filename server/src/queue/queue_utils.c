/*
** EPITECH PROJECT, 2022
** server
** File description:
** queue_utils.c
*/

#include "server.h"

void init_command_queue(client_t* client)
{
    client->player->command_queue.front = -1;
    client->player->command_queue.rear = -1;
}

bool is_command_queue_empty(client_t* client)
{
    command_queue_t* queue = &(client->player->command_queue);

    return (queue->front == -1);
}

bool is_command_queue_full(client_t* client)
{
    command_queue_t* queue = &(client->player->command_queue);

    return ((queue->rear + 1) % MAX_COMMANDS_PER_CLIENT == queue->front);
}
