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

int is_command_queue_empty(client_t* client)
{
    return (client->player->command_queue.front == FAILURE);
}

int is_command_queue_full(client_t* client)
{
    command_queue_t* queue = &client->player->command_queue;

    return ((queue->front == 0 && queue->rear == MAX_COMMANDS_PER_CLIENT - 1) ||
            (queue->front == queue->rear + 1));
}
