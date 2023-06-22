/*
** EPITECH PROJECT, 2022
** server
** File description:
** enqueue.c
*/

#include "colors.h"
#include "server.h"

void print_command_enqueue(client_t* client, const char* command, int freq)
{
    int action_time = 0;
    command_queue_t* queue = &client->player->command_queue;

    for (int i = 0; i < PLAYER_COMMANDS_SIZE; i++) {
        if (!strcmp(command, PLAYER_COMMANDS[i].name)) {
            action_time = PLAYER_COMMANDS[i].action_time;
            break;
        }
    }

    double duration = (double)action_time / freq;

    fprintf(stdout, PURPLE "%s" RESET "\n",
    "============  Start DEBUG command queue ============");
    printf("Enqueueing command: %s for client %d\n", command, client->fd);
    printf("Duration: %f\n", duration);
    double completion_time_sec =
        (double)queue->completion_time[queue->rear] / CLOCKS_PER_SEC;
    printf("Completion time: %.2f seconds\n", completion_time_sec);

    fprintf(stdout, PURPLE "%s" RESET "\n",
    "============  End DEBUG command queue ============");
}

void enqueue_command(client_t* client, const char* command, int freq)
{
    int action_time = 0;
    command_queue_t* queue = &client->player->command_queue;

    if (is_command_queue_empty(client)) {
        queue->front = 0;
        queue->rear = 0;
    } else {
        if (is_command_queue_full(client)) {
            printf("Command queue is full. Unable to enqueue command.\n");
            return;
        }
        queue->rear = (queue->rear + 1) % MAX_COMMANDS_PER_CLIENT;
    }

    for (int i = 0; i < PLAYER_COMMANDS_SIZE; i++) {
        if (!strcmp(command, PLAYER_COMMANDS[i].name)) {
            action_time = PLAYER_COMMANDS[i].action_time;
            break;
        }
    }

    printf("action time: %d\n", action_time);

    double duration = (double)action_time / freq;

    if (is_command_queue_full(client)) {
        printf("Command queue is full. Unable to enqueue command.\n");
        return;
    }

    printf("Enqueueing command: %s for client %d\n", command, client->fd);
    strncpy(queue->commands[queue->rear], command, MAX_COMMANDS_LENGTH);
    printf("Enqueueing command: %s for client %d\n", command, client->fd);
    queue->completion_time[queue->rear] = clock() + (CLOCKS_PER_SEC * duration);
    print_command_enqueue(client, command, freq);

    printf("rear: %d\n", queue->rear);
    printf("front: %d\n", queue->front);
}
