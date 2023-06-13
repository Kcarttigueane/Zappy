/*
** EPITECH PROJECT, 2022
** server
** File description:
** execute_players_command.c
*/

#include "server.h"

void execute_commands(server_data_t* s)
{
    client_t *client, *temp;

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {

        if (!is_command_queue_empty(client)) {
            if (!client->player->is_graphical) {
                list_args_t args = {
                    .server_data = s,
                    .client = client,
                };

                size_t index = find_graphical_command_index(
                    client->player->command_queue
                        .commands[client->player->command_queue.front]);

                if (index == (size_t)FAILURE) {
                    printf("Graphical : Command not found\n");
                    dequeue_command(client);
                    continue;
                }

                GRAPHICAL_COMMANDS[index].function(&args);
            }

            // size_t index = find_player_command_index(
            //     client->player->command_queue
            //         .commands[client->player->command_queue.front]);

            // if (index == (size_t)FAILURE) {
            //     printf("Player : Command not found\n");
            //     dequeue_command(client);
            //     continue;
            // }

            // PLAYER_COMMANDS[index].function(s);
            // dequeue_command(client);
        }
    }
}
