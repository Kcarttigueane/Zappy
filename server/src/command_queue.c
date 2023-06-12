/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** command_queue.c
*/

#include "server.h"

void init_command_queue(client_t* client)
{
    client->player->command_queue.front = -1;
    client->player->command_queue.rear = -1;
}

int is_command_queue_empty(client_t* client)
{
    return (client->player->command_queue.front == -1);
}

int is_command_queue_full(client_t* client)
{
    command_queue_t* queue = &client->player->command_queue;

    return ((queue->front == 0 && queue->rear == MAX_COMMANDS_PER_CLIENT - 1) ||
            (queue->front == queue->rear + 1));
}

void enqueue_command(client_t* client, const char* command)
{
    if (is_command_queue_full(client)) {
        printf("Command queue is full. Unable to enqueue command.\n");
        return;
    }
    command_queue_t* queue = &client->player->command_queue;

    if (queue->front == -1)
        queue->front = 0;

    queue->rear = (queue->rear + 1) % MAX_COMMANDS_PER_CLIENT;
    strncpy(queue->commands[queue->rear], command, MAX_COMMANDS_LENGTH);
}

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

void print_command_queue(client_t* client)
{
    command_queue_t* queue = &(client->player->command_queue);

    if (is_command_queue_empty(client)) {
        printf("Empty\n");
    } else {
        printf("Command Queue for Client %d:\n", client->fd);
        int current = queue->front;
        int order = 1;
        printf("Front -> ");
        while (current != queue->rear) {
            printf("%d. %s -> ", order++, queue->commands[current]);
            current = (current + 1) % MAX_COMMANDS_PER_CLIENT;
        }
        printf("%d. %s -> Rear\n", order++, queue->commands[current]);
    }
}
