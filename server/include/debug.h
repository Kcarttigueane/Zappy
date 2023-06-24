/*
** EPITECH PROJECT, 2022
** server
** File description:
** debug.h
*/

#ifndef DEBUG_H
    #define DEBUG_H

    #include "map.h"
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

/**
 * @brief Debug function that prints the content of a given tile.
 *
 * This function outputs the quantity of each item in a tile to the stdout.
 * Items include food, linemate, deraumere, sibur, mendiane, phiras, thystame.
 *
 * The debug information is wrapped between two lines of text for clarity.
 *
 * @param tile Pointer to the tile structure that contains the
 * quantity of each item.
 *
 * @note This is a debug function, meant to be used during the development phase
 *       and not meant for use in production code.
 */
void debug_tile_content(tile_t* tile);

#endif /* !DEBUG_H */
