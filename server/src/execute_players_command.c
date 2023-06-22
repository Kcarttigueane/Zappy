/*
** EPITECH PROJECT, 2022
** server
** File description:
** execute_players_command.c
*/

#include "server.h"

void execute_commands(server_data_t* s)
{
    client_t *client, *temp = NULL;
    time_t current_time = clock();

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {
        if (!is_command_queue_empty(client)) {
            if (client->player->is_graphical) {
                printf("client->fd: %d\n", client->fd);
                list_args_t args = {
                    .server_data = s,
                    .client = client,
                };

                printf(
                    "client->player->command_queue.commands[client->player->"
                    "command_queue.front]: |%s|\n",
                    client->player->command_queue
                        .commands[client->player->command_queue.front]);
                char* command_name = split_str(
                    client->player->command_queue
                        .commands[client->player->command_queue.front],
                    " ")[0];

                printf("command_name: |%s|\n", command_name);

                size_t index = find_graphical_command_index(command_name);
                printf("index: %ld\n", index);
                if (index == (size_t)FAILURE) {
                    append_to_gui_write_buffer(s, SUC_FORMAT);
                    dequeue_command(client);
                    continue;
                }

                GRAPHICAL_COMMANDS[index].function(&args);
                dequeue_command(client);
            } else {
                if (current_time >=
                    client->player->command_queue
                        .completion_time[client->player->command_queue.front]) {

                    list_args_t args = {
                        .server_data = s,
                        .client = client,
                    };

                    // double completion_time_sec =
                    //     (double)client->player->command_queue
                    //         .completion_time[client->player->command_queue.front] /
                    //     CLOCKS_PER_SEC;

                    // printf("Completion time: %.2f seconds\n", completion_time_sec);
                    // print_command_queue(client);

                    printf(
                        "client->player->command_queue.commands[client->player-"
                        ">"
                        "command_queue.front]: |%s|\n",
                        client->player->command_queue
                            .commands[client->player->command_queue.front]);

                    char* command_name = split_str(
                        client->player->command_queue
                            .commands[client->player->command_queue.front],
                        " ")[0];

                    size_t index = find_player_command_index(command_name);

                    printf("index: %ld\n", index);

                    if (index == (size_t)FAILURE) {
                        append_to_gui_write_buffer(s, SUC_FORMAT);
                        dequeue_command(client);
                        continue;
                    }
                    PLAYER_COMMANDS[index].function(&args);
                    dequeue_command(client);
                }
            }
        }
    }
}
