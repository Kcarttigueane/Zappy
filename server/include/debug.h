/*
** EPITECH PROJECT, 2022
** server
** File description:
** debug.h
*/

#ifndef DEBUG_H
    #define DEBUG_H

    #include "server.h"

/**
 * @brief Prints the program arguments for debugging purposes.
 *
 * This function prints the program arguments stored in the `server_data_t`
 * structure. It displays the PORT, WIDTH, HEIGHT, CLIENTS_NB, FREQ, TEAM_COUNT,
 * and TEAM_NAME values of the `game` field.
 *
 * @param s Pointer to the server_data_t structure.
 */
void debug_program_args(server_data_t* s);

#endif /* !DEBUG_H */
