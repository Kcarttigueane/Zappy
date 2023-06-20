/*
** EPITECH PROJECT, 2022
** server
** File description:
** error_handling.h
*/

#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include "server.h"

/**
 *  @brief Validates and sets server port.
 *
 *  Validates the provided port value (it should be between 1024 and 65535).
 *  If validation fails, the default port (DEFAULT_PORT) is used.
 *
 *  @param arg The provided port value as a string.
 *  @param s Pointer to the server_data_t struct where the port will be set.
 */
void validate_and_set_port(char* arg, server_data_t* s);

/**
 *  @brief Validates and sets game width.
 *
 *  Validates the provided game width (it should be between 10 and 30).
 *  If validation fails, the default width (DEFAULT_WIDTH) is used.
 *
 *  @param arg The provided width value as a string.
 *  @param s Pointer to the server_data_t struct where the width will be set.
 */
void validate_and_set_width(char* arg, server_data_t* s);

/**
 *  @brief Validates and sets game height.
 *
 *  Validates the provided game height (it should be between 10 and 30).
 *  If validation fails, the default height (DEFAULT_HEIGHT) is used.
 *
 *  @param arg The provided height value as a string.
 *  @param s Pointer to the server_data_t struct where the height will be set.
 */
void validate_and_set_height(char* arg, server_data_t* s);

/**
 *  @brief Validates and sets number of clients.
 *
 *  Validates the provided number of clients (it should be greater than 0).
 *  If validation fails,
 *  the default number of clients (DEFAULT_CLIENTS_NB) is used.
 *
 *  @param arg The provided number of clients as a string.
 *  @param s Pointer to the server_data_t struct where the number of clients
 *           will be set.
 */
void validate_and_set_clients_nb(char* arg, server_data_t* s);

/**
 *  @brief Validates and sets game frequency.
 *
 *  Validates the provided frequency (it should be between 2 and 10000).
 *  If validation fails, the default frequency (DEFAULT_FREQ) is used.
 *
 *  @param arg The provided frequency value as a string.
 *  @param s Pointer to the server_data_t struct where the frequency
 *  will be set.
 */
void validate_and_set_freq(char* arg, server_data_t* s);

/**
 * @brief Parses command-line arguments and initializes the
 * server data structure.
 *
 * This function iterates over the command-line arguments,
 * validates them, and if valid, sets them in the server data
 * structure.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @param s The server data structure to be initialized.
 * @return int Returns SUCCESS if the arguments are valid and
 * the server data structure is successfully initialized, and
 * FAILURE otherwise.
 */
int parse_arguments(int argc, char** argv, server_data_t* s);

#endif /* !ERROR_HANDLING_H */
