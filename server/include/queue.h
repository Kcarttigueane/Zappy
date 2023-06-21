/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** queue.h
*/

#ifndef QUEUE_H_
    #define QUEUE_H_

    #include "player.h"
    #include "server.h"

    typedef struct command_queue_s {
        char commands[MAX_NB_COMMANDS][MAX_COMMANDS_LENGTH];
        int front;
        int rear;
    } command_queue_t;

void init_command_queue(client_t* client);
int is_command_queue_empty(client_t* client);
int is_command_queue_full(client_t* client);
void enqueue_command(client_t* client, const char* command);
void dequeue_command(client_t* client);
void print_command_queue(client_t* client);

#endif /* !QUEUE_H_ */
