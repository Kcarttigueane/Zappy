/*
** EPITECH PROJECT, 2023
** server
** File description:
** main.c
*/

#include "./include/server.h"

int main(int argc, char const* argv[])
{
    if (!are_program_args_valid(argc, argv))
        return ERROR;

    if (setup_signal_handler() == ERROR)
        return ERROR;

    server_data_t server_data = {
        .PORT = atoi(argv[1]),
        .socket_fd = 0,
        .readfds = {{0}},
    };

    if (initialize_server(&server_data) == ERROR)
        return handle_error("Server initialization failed");

    return 0;
}
