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

clock_t get_last_command_completion_time(client_t* client)
{
    if (is_command_queue_empty(client)) {
        printf("Command queue is empty. Unable to get completion time.\n");
        return -1;
    }

    command_queue_t* queue = &client->player->command_queue;
    return queue->completion_time[queue->front];
}

char* peek_command(client_t* client)
{
    if (is_command_queue_empty(client) == true) {
        printf("Command queue is empty. Unable to peek command.\n");
        return NULL;
    }

    command_queue_t* queue = &client->player->command_queue;

    return queue->commands[queue->front];
}
