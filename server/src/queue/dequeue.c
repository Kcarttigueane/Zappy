/*
** EPITECH PROJECT, 2022
** server
** File description:
** dequeue.c
*/

#include "server.h"

void dequeue_command(client_t* client)
{
    if (is_command_queue_empty(client)) {
        printf("Command queue is empty. Unable to dequeue command.\n");
        return;
    }
    command_queue_t* queue = &client->player->command_queue;

    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front = (queue->front + 1) % MAX_COMMANDS_PER_CLIENT;
}
