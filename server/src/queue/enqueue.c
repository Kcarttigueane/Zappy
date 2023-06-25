/*
** EPITECH PROJECT, 2022
** server
** File description:
** enqueue.c
*/

#include "colors.h"
#include "server.h"

void print_command_enqueue(client_t* client, char* command, int freq, int action_time)
{
    command_queue_t* queue = &client->player->command_queue;
    double duration = (double)action_time / freq;

    fprintf(stdout, PURPLE "%s" RESET "\n", "============  Start DEBUG command queue ============");
    printf("action time: %d\n", action_time);
    printf("Enqueueing command: %s for client %d\n", command, client->fd);
    printf("Duration: %f\n", duration);
    double completion_time_sec = (double)queue->completion_time[queue->rear] / CLOCKS_PER_SEC;
    printf("Completion time: %.2f seconds\n", completion_time_sec);

    fprintf(stdout, PURPLE "%s" RESET "\n", "============  End DEBUG command queue ============");
}

static int get_action_time(char* command)
{
    char** split_command = split_str(command, " ");

    if (!split_command)
        return 0;

    char* command_name = split_command[0];

    for (size_t i = 0; i < PLAYER_COMMANDS_SIZE; i++) {
        if (!strcmp(command_name, PLAYER_COMMANDS[i].name)) {
            free_word_array(split_command);
            return PLAYER_COMMANDS[i].action_time;
        }
    }

    free_word_array(split_command);
    return 0;
}

void enqueue_command(client_t* client, char* command, int freq)
{
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

    int action_time = get_action_time(command);

    double duration = (double)action_time / freq;

    if (is_command_queue_full(client)) {
        printf("Command queue is full. Unable to enqueue command.\n");
        return;
    }

    strncpy(queue->commands[queue->rear], command, MAX_COMMANDS_LENGTH);
    queue->completion_time[queue->rear] = clock() + (CLOCKS_PER_SEC * duration);
    print_command_enqueue(client, command, freq, action_time);
}
