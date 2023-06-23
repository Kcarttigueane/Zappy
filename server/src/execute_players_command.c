/*
** EPITECH PROJECT, 2022
** server
** File description:
** execute_players_command.c
*/

#include "server.h"

void execute_graphical_command(list_args_t* args)
{
    char* command_name = split_str(args->command, " ")[0];

    size_t index = find_graphical_command_index(command_name);

    if (index == (size_t)FAILURE) {
        append_to_gui_write_buffer(args->server_data, SUC_FORMAT);
    } else {
        GRAPHICAL_COMMANDS[index].function(args);
    }
    dequeue_command(args->client);
}

void execute_player_command(list_args_t* args, time_t current_time)
{
    if (current_time >=
        args->client->player->command_queue
            .completion_time[args->client->player->command_queue.front]) {

        char* command_name = split_str(args->command, " ")[0];

        size_t index = find_player_command_index(command_name);

        if (index == (size_t)FAILURE) {
            append_to_gui_write_buffer(args->server_data, SUC_FORMAT);
        } else {
            PLAYER_COMMANDS[index].function(args);
        }
        dequeue_command(args->client);
    }
}

void execute_commands(server_data_t* s)
{
    client_t *client, *temp = NULL;
    time_t current_time = clock();

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp) {
        if (!is_command_queue_empty(client)) {
            int front = client->player->command_queue.front;
            char* command = &client->player->command_queue.commands[front][0];

            list_args_t args = {
                .server_data = s,
                .client = client,
                .command = command,
            };

            if (client->player->is_graphical)
                execute_graphical_command(&args);
            else
                execute_player_command(&args, current_time);
        }
    }
}
