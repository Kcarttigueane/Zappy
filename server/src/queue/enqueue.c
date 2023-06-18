/*
** EPITECH PROJECT, 2022
** server
** File description:
** enqueue.c
*/

#include "server.h"

void enqueue_command(client_t* client, const char* command)
{
    if (is_command_queue_full(client)) {
        printf("Command queue is full. Unable to enqueue command.\n");
        return;
    }
    command_queue_t* queue = &client->player->command_queue;

    if (queue->front == FAILURE)
        queue->front = 0;

    queue->rear = (queue->rear + 1) % MAX_COMMANDS_PER_CLIENT;
    strncpy(queue->commands[queue->rear], command, MAX_COMMANDS_LENGTH);
    printf("Enqueued command: |%s|\n", queue->commands[queue->rear]);
}
