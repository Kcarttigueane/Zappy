/*
** EPITECH PROJECT, 2022
** server
** File description:
** execute_players_command.c
*/

#include "colors.h"
#include "server.h"

static void execute_graphical_command(game_t* game, client_t* client, char* command)
{
    char* command_name = split_str(command, " ")[0];

    int index = find_graphical_command_index(command_name);

    if (index == FAILURE) {
        append_to_gui_write_buffer(game, SUC_FORMAT);
    } else {
        GRAPHICAL_COMMANDS[index].function(game, client);
    }

    dequeue_command(client);
}

static void execute_player_command(game_t* game, client_t* client, char* command,
                                   time_t current_time)
{
    clock_t completion_time = get_last_command_completion_time(client);

    if (current_time >= completion_time) {

        char* command_name = split_str(command, " ")[0];

        int index = find_player_command_index(command_name);

        if (index == FAILURE) {
            append_to_gui_write_buffer(game, SUC_FORMAT);
        } else {
            PLAYER_COMMANDS[index].function(game, client);
        }
        dequeue_command(client);
    }
}

void execute_commands(server_data_t* s)
{
    client_t *client, *temp = NULL;
    time_t current_time = clock();

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {
        if (client->player->state == NONE)
            continue;
        if (!is_command_queue_empty(client)) {
            char* command = peek_command(client);

            if (client->player->state == GRAPHICAL)
                execute_graphical_command(&s->game, client, command);
            else
                execute_player_command(&s->game, client, command, current_time);
        }
    }
}
