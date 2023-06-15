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

const char* inventory_names[] = {"food",     "linemate", "deraumere", "sibur",
                                 "mendiane", "phiras",   "thystame"};

int main(int argc, char** argv)
{
    srand(time(NULL));

    if (!are_program_args_valid(argc, argv))
        return ERROR;

    server_data_t* data = (server_data_t*)calloc(1, sizeof(server_data_t));

    if (parse_arguments(argc, argv, data) != 0)
        return handle_error("main() :Invalid arguments\n");

    if (setup_signal_handler() == ERROR)
        return handle_error("main() :Signal handler setup failed\n");

    data->game.next_player_id = 15;
    data->game.map = init_map(data->game.width, data->game.height);

    LIST_INIT(&data->game.client_list);

    if (initialize_server(data) == ERROR)
        return handle_error("Server initialization failed");

    server_loop(data);

    free_teams_names(data);
    free_map(data->game.map, data->game.width);
    free(data);
    return SUCCESS;
}
