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
    args->client->player->inventory[LINEMATE] = 1;

    args->client->player->is_graphical = false;
    args->client->player->start_time = clock();
    args->client->player->is_frozen = false;

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
    args->client->player->is_frozen = false;

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
        args->client->player->is_frozen = false;
        get_map_size(args);
        get_time_unit(args);
        get_all_tiles_content(args);
        get_all_team_names(args);
        get_all_player_positions(args);
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
                enqueue_command(args->client, input_buffer,
                                args->server_data->game.freq);
                return;
            }
        }
    } else {
        for (size_t i = 0; i < PLAYER_COMMANDS_SIZE; i++) {
            if (!strcasecmp(inputs[0], PLAYER_COMMANDS[i].name)) {
                enqueue_command(args->client, input_buffer,
                                args->server_data->game.freq);
                return;
            }
        }
    }
}

static void process_command_buffer(list_args_t* args, char* command_buff)
{
    char** split_command = split_str(command_buff, " ");

    if (!split_command)
        return;

    if (args->client->player->state == NONE)
        handle_first_client_msg(args, split_command);
    else
        handle_client_command(args, split_command, command_buff);
}

void parse_client_input(list_args_t* args, char* received_buff)
{
    char command_extracted[256] = {0};

    if (strlen(args->client->read_buf) + strlen(received_buff) <
        MAX_W_BUFFER_LENGTH) {
        strcat(args->client->read_buf, received_buff);
    } else {
        printf("Buffer overflow\n");
    }

    size_t size = strlen(args->client->read_buf);

    for (size_t i = 0; i < size; i++) {
        if (i >= sizeof(command_extracted)) {
            printf("Command is too long\n");
            break;
        }
        command_extracted[i] = args->client->read_buf[i];
        if (args->client->read_buf[i] == '\n') {
            command_extracted[i] = '\0';

            // printf("Processing line: %s\n", command_extracted);
            process_command_buffer(args, command_extracted);

            size_t line_length = i + 1;
            size_t remaining = size - line_length;
            memmove(args->client->read_buf,
                    args->client->read_buf + line_length, remaining);
            args->client->read_buf[remaining] = '\0';
            size = remaining;

            i = 0;
        }
    }
}
