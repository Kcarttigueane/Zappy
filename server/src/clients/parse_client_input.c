/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** parse_client_input.c
*/

#include "server.h"

int find_team_index(list_args_t* args, char* team_name)
{
    for (size_t i = 0; i < args->server_data->game.team_count; i++) {
        if (!strcmp(args->server_data->game.team_names[i], team_name))
            return i;
    }
    return FAILURE;
}

void update_player(list_args_t* args, char** inputs)
{
    args->client->player->team_name = strdup(inputs[0]);
    args->client->player->state = ACTIVE;
    args->client->player->level = 1;
    args->client->player->orientation = NORTH;
    args->client->player->inventory[FOOD] = 9;
    args->client->player->is_graphical = false;

    int team_index = find_team_index(args, inputs[0]);
    if (team_index == FAILURE)
        return;

    args->server_data->game.team[team_index].nb_players_connected++;
}

bool is_team_name_valid(list_args_t* args, char** inputs)
{
    for (size_t i = 0; i < args->server_data->game.team_count; i++) {
        if (!strcmp(args->server_data->game.team_names[i], inputs[0]))
            return true;
    }
    return false;
}

void update_egg_player(list_args_t* args, char** inputs, egg_t* egg)
{
    args->client->player->team_name = strdup(inputs[0]);
    args->client->player->state = ACTIVE;
    args->client->player->level = 1;
    args->client->player->orientation = NORTH;
    args->client->player->inventory[FOOD] = 9;
    args->client->player->is_graphical = false;

    int team_index = find_team_index(args, inputs[0]);
    if (team_index == FAILURE)
        return;

    remove_egg_by_id(&args->server_data->game.team[team_index], egg->id);
    args->server_data->game.team[team_index].nb_players_connected++;
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
        // ! ! ! check for egg and all
        team_t* team = find_team_by_name(args->server_data, inputs[0]);
        if (team->nb_players_connected >= team->max_players) {
            printf("Team is full\n");
            // disconnect_client(args);
            return;
        }
        if (!is_egg_list_empty(team)) {
            printf("Egg available\n");
            egg_t* egg = random_select_egg(team);
            update_egg_player(args, inputs, egg);

            char response[256] = {0};

            sprintf(response, EBO_FORMAT, egg->id);
            append_to_gui_write_buffer(args->server_data, response);
            return;
        } else {
            update_player(args, inputs);
        }
        char response[1024] = {0};
        size_t new_id = args->client->player->id--;
        sprintf(response, PNW_FORMAT, args->client->player->id,
                args->client->player->pos.x, args->client->player->pos.y,
                args->client->player->orientation, args->client->player->level,
                args->client->player->team_name);

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
