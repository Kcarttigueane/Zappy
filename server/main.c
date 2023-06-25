/*
** EPITECH PROJECT, 2023
** server
** File description:
** main.c
*/

#include "./include/server.h"
#include "colors.h"

const char* colors[] = {
    RED, CYAN, GRAY, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE,
};

const char* inventory_names[] = {
    "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame",
};

void init_teams(server_data_t* s)
{
    s->game.teams = (team_t*)calloc(s->game.team_count, sizeof(team_t));

    for (size_t i = 0; i < s->game.team_count; i++) {
        s->game.teams[i].name = strdup(s->game.team_names[i]);
        s->game.teams[i].max_players = s->game.clients_nb;
        LIST_INIT(&s->game.teams[i].egg_list);
    }
}

void free_teams(server_data_t* s)
{
    for (size_t i = 0; i < s->game.team_count; i++) {
        free(s->game.teams[i].name);
    }
    free(s->game.teams);
}

void free_game(server_data_t* s)
{
    free_egg_lists(&s->game);
    free_client_list(&s->game);
    free_teams(s);
    free_tiles_map(s->game.map, s->game.width);
    free(s->game.team_names);
    free(s);
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    server_data_t* server_data = (server_data_t*)calloc(1, sizeof(server_data_t));

    if (parse_arguments(argc, argv, server_data) == FAILURE)
        return handle_error("main() : Invalid arguments\n");

    if (setup_signal_handler() == ERROR)
        return handle_error("main() :Signal handler setup failed\n");

    server_data->game.next_player_id = 15;
    server_data->game.map = init_map(server_data->game.width, server_data->game.height);

    init_teams(server_data);

    LIST_INIT(&server_data->game.client_list);

    if (initialize_server(server_data) == ERROR)
        return handle_error("Server initialization failed");

    server_loop(server_data);
    free_game(server_data);
    return SUCCESS;
}
