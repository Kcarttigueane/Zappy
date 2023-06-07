/*
** EPITECH PROJECT, 2023
** server
** File description:
** main.c
*/

#include "./include/server.h"
#include "colors.h"

const char* colors[] = {RED,  CYAN,   GRAY, GREEN, YELLOW,
                        BLUE, PURPLE, CYAN, WHITE};

int main(int argc, char** argv)
{
    srand(time(NULL));

    if (!are_program_args_valid(argc, argv))
        return ERROR;

    server_data_t* data = (server_data_t*)calloc(1, sizeof(server_data_t));

    if (parse_arguments(argc, argv, data) != 0)
        return handle_error("main() :Invalid arguments\n");

    if (setup_signal_handler() == ERROR)
        return ERROR;

    //     if (initialize_server(&server_data) == ERROR)
    //         return handle_error("Server initialization failed");

    //     // server_loop(&server_data);

    free_teams_names(data);

    return SUCCESS;
}
