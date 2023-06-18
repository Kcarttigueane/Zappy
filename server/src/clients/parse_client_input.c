/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** parse_client_input.c
*/

#include "server.h"

void update_player(list_args_t* args, char** inputs)
{
    args->client->player->team = calloc(1, sizeof(team_t));
    args->client->player->team->name = strdup(inputs[0]);
    args->client->player->team->max_players =
        args->server_data->game.clients_nb;
    args->client->player->team->nb_players_connected = 1;
    args->client->player->team->nb_eggs = 0;
    args->client->player->state = ACTIVE;
    args->client->player->level = 1;
    args->client->player->orientation = NORTH;
    args->client->player->inventory[FOOD] = 9;
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
        printf("New player connected\n");
        update_player(args, inputs);

        char response[1024] = {0};
        size_t new_id = args->client->player->id--;

        sprintf(response, PNW_FORMAT, args->client->player->id,
                args->client->player->pos.x, args->client->player->pos.y,
                args->client->player->orientation, args->client->player->level,
                args->client->player->team->name);

        append_to_gui_write_buffer(args->server_data, response);
        memset(response, 0, 1024);
    }
}

void handle_client_command(list_args_t* args, char** inputs, char* input_buffer)
{
    if (args->client->player->is_graphical) {
        for (size_t i = 0; i < GRAPHICAL_COMMANDS_SIZE; i++) {
            if (!strcasecmp(inputs[0], GRAPHICAL_COMMANDS[i].name)) {
                printf("[G] ->Enqueueing command: |%s|\n",
                       GRAPHICAL_COMMANDS[i].name);
                enqueue_command(args->client, input_buffer);
                return;
            }
        }
    } else {
        for (size_t i = 0; i < PLAYER_COMMANDS_SIZE; i++) {
            if (!strcasecmp(inputs[0], PLAYER_COMMANDS[i].name)) {
                printf("[P] ->Enqueueing command: |%s|\n",
                       PLAYER_COMMANDS[i].name);
                enqueue_command(args->client, input_buffer);
                return;
            }
        }
    }
}

void parse_client_input(list_args_t* args, char* input_buffer)
{
    char** split_command = split_str(input_buffer, " ");

    debug_word_array(split_command);

    if (!split_command)
        return;

    if (args->client->player->state == NONE)
        handle_first_client_msg(args, split_command);
    else
        handle_client_command(args, split_command, input_buffer);

    free_word_array(split_command);
}
