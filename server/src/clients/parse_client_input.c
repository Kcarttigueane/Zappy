/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** parse_client_input.c
*/

#include "server.h"

void update_player(list_args_t* args, char** inputs)
{
    args->client->player->team->name = strdup(inputs[0]);
    args->client->player->team->max_players =
        args->server_data->game.clients_nb;
    args->client->player->team->nb_players_connected = 1;
    args->client->player->team->nb_eggs = 0;
    args->client->player->state = ACTIVE;
    args->client->player->level = 1;
    args->client->player->pos.x = args->server_data->game.width;
    args->client->player->pos.y = args->server_data->game.height;
    args->client->player->orientation = NORTH;
    args->client->player->inventory[FOOD] = 10;
    args->client->player->is_graphical = false;
}

bool is_team_name_valid(list_args_t* args, char** inputs)
{
    for (size_t i = 0; i < args->server_data->game.team_count; i++) {
        if (!strcmp(args->server_data->game.team_names[i], inputs[0]))
            return true;
    }
    return false;
}

void handle_first_client_msg(list_args_t* args, char** inputs)
{
    if (!strcmp(inputs[0], "GRAPHIC")) {
        args->client->player->is_graphical = true;
        args->client->player->state = ACTIVE;
        // msz(args);
        // sgt(args);
        // mct(args);
        // tna(args);
        // pnw(args);
    } else {
        if (!is_team_name_valid(args, inputs)) {
            printf("Invalid team name\n");
            return;
        }
        update_player(args, inputs);
    }
}

void handle_client_command(list_args_t* args, char** inputs)
{
    if (args->client->player->is_graphical) {
        for (size_t i = 0; i < GRAPHICAL_COMMANDS_SIZE; i++) {
            if (!strcasecmp(inputs[0], GRAPHICAL_COMMANDS[i].name)) {
                enqueue_command(args->client, GRAPHICAL_COMMANDS[i].name);
                return;
            }
        }
    } else
        for (size_t i = 0; i < PLAYER_COMMANDS_SIZE; i++) {
            if (!strcasecmp(inputs[0], PLAYER_COMMANDS[i].name)) {
                enqueue_command(args->client, PLAYER_COMMANDS[i].name);
                return;
            }
        }
}

void parse_client_input(list_args_t* args, char* input_buffer)
{
    char** split_command = split_str(input_buffer, "\n");

    debug_word_array(split_command);

    if (!split_command)
        return;

    if (args->client->player->state == NONE)
        handle_first_client_msg(args, split_command);
    else
        handle_client_command(args, split_command);

    free_word_array(split_command);
}
