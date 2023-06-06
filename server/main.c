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

    if (!parse_arguments(argc, argv, data) != 0)
        return handle_error("Invalid arguments\n");

    if (setup_signal_handler() == ERROR)
        return ERROR;

    //     if (initialize_server(&server_data) == ERROR)
    //         return handle_error("Server initialization failed");

    printf("Server initialized\n");
    printf("Port: %d\n", data->PORT);
    printf("Width: %ld\n", data->game.width);
    printf("Height: %ld\n", data->game.height);
    printf("Team count: %ld\n", data->game.team_count);
    printf("Clients per team: %ld\n", data->game.clients_nb);
    printf("Frequency: %ld\n", data->game.freq);
    printf("Team names: ");
    for (size_t i = 0; i < data->game.team_count; i++) {
        printf("%s%s%s", colors[i], data->game.team_names[i], RESET);
        if (i < data->game.team_count - 1)
            printf(", ");
    }

    //     // server_loop(&server_data);
    for (size_t i = 0; i < data->game.team_count; i++) {
        free(data->game.team_names[i]);
    }
    free(data->game.team_names);

    return SUCCESS;
}
