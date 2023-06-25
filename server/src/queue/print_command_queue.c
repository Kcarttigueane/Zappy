/*
** EPITECH PROJECT, 2022
** server
** File description:
** print_command_queue.c
*/

#include "colors.h"
#include "server.h"

void print_command_queue(client_t* client)
{
    command_queue_t* queue = &(client->player->command_queue);

    if (is_command_queue_empty(client)) {
        printf("Empty\n");
    } else {
        fprintf(stdout, PURPLE "%s" RESET "\n",
                "============  Start DEBUG command queue full ============");
        printf("Command Queue for Client %d:\n", client->fd);
        int current = queue->front;
        int order = 1;
        printf("Front -> ");
        while (current != queue->rear && order <= MAX_COMMANDS_PER_CLIENT) {
            printf("Command order: %d.  name: %s -> ", order++, queue->commands[current]);
            printf("Enqueued at: %.2f seconds\n",
                   (double)queue->completion_time[current] / CLOCKS_PER_SEC);
            current = (current + 1) % MAX_COMMANDS_PER_CLIENT;
        }
        if (order <= MAX_COMMANDS_PER_CLIENT) {
            printf("%d. %s -> Rear ==> Enqueued at: %.2f seconds\n", order++,
                   queue->commands[current],
                   (double)queue->completion_time[current] / CLOCKS_PER_SEC);
        }
        fprintf(stdout, PURPLE "%s" RESET "\n",
                "============  End DEBUG command queue ============");
    }
}
