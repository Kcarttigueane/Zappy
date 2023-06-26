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
        clock_t completion_time[MAX_NB_COMMANDS];
        int front;
        int rear;
    } command_queue_t;

/**
 * @brief Removes the command at the front of the client's command queue.
 *
 * @param client The client whose command is to be dequeued.
 */
void dequeue_command(client_t* client);

/**
 * @brief Prints the details of a command that is being added to the queue.
 *
 * @param client The client for which the command is being enqueued.
 * @param command The command that is being enqueued.
 * @param freq The frequency with which the command is executed.
 */
void print_command_enqueue(client_t* client, char* command, int freq, int action_time);

/**
 * @brief Adds a new command to the client's command queue.
 *
 * @param client The client for which the command is being enqueued.
 * @param command The command that is being enqueued.
 * @param freq The frequency with which the command is executed.
 */
void enqueue_command(client_t* client, char* command, int freq);

/**
 * @brief Prints the current state of the command queue for a given client.
 *
 * @param client The client whose command queue is to be printed.
 */
void print_command_queue(client_t* client);

/**
 * @brief Initializes the command queue for a given client.
 *
 * @param client The client whose command queue is to be initialized.
 */
void init_command_queue(client_t* client);

/**
 * @brief Checks if the command queue for a given client is empty.
 *
 * @param client The client whose command queue is to be checked.
 * @return Returns true if the command queue is empty, false otherwise.
 */
bool is_command_queue_empty(client_t* client);

/**
 * @brief Checks if the command queue for a given client is full.
 *
 * @param client The client whose command queue is to be checked.
 * @return Returns true if the command queue is full, false otherwise.
 */
bool is_command_queue_full(client_t* client);

/**
 * @brief Retrieves the command at the front of the command queue without removing it.
 *
 * @param client Pointer to the client structure.
 *
 * @return char* Returns the command at the front of the queue. If the queue is empty, returns NULL.
 */
char* peek_command(client_t* client);

/**
 * @brief Returns the completion time of the last command in the client's command queue.
 *
 * @param client The client whose command queue's last command completion time is to be retrieved.
 *
 * @return Returns the clock_t value representing the completion time of the last command.
 *         If the queue is empty, returns -1.
 */
clock_t get_last_command_completion_time(client_t* client);

#endif /* !QUEUE_H_ */
