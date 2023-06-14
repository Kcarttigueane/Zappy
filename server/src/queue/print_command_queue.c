/*
** EPITECH PROJECT, 2022
** server
** File description:
** print_command_queue.c
*/

#include "server.h"

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
