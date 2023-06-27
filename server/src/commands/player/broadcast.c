/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** broadcast.c
*/

#include "server.h"
#include <math.h>

#define M_PI 3.14159265358979323846

int get_signed_shortest_distance(int pos1, int pos2, int size)
{
    int distance = pos2 - pos1;

    if (abs(distance) > size / 2) {
        distance = (distance > 0) ? distance - size : distance + size;
    }
    return distance;
}

int get_direction(game_t* game, player_t* src, player_t* dst)
{
    int dx = get_signed_shortest_distance(src->pos.x, dst->pos.x, game->width);
    int dy = get_signed_shortest_distance(src->pos.y, dst->pos.y, game->height);

    if (dx == 0 && dy == 0) {
        return 0;
    } else {
        int angle = (int)(atan2(dy, dx) * (180.0 / M_PI) + 180) / 45;
        return angle % 8 + 1;
    }
}

void broadcast(game_t* game, client_t* client)
{
    char* command = peek_command(client);

    char** command_split = split_str(command, " ");
    char* message = command_split[1];

    if (message == NULL) {
        append_to_string(client->write_buf, KO_FORMAT);
        return;
    }

    client_t *curr_client, *temp;

    LIST_FOREACH_SAFE(curr_client, &game->client_list, entries, temp)
    {
        if (curr_client->player->state == GRAPHICAL || curr_client->player->state == NONE)
            continue;

        int direction = get_direction(game, client->player, curr_client->player);

        char response[MAX_BUFFER] = {0};
        printf("direction: %d\n", direction);
        sprintf(response, "message %d, %s\n", direction, message);
        append_to_string(curr_client->write_buf, response);
    }

    char response[1024] = {0};

    sprintf(response, PBC_FORMAT, client->player->id, command);

    append_to_gui_write_buffer(game, response);

    append_to_string(client->write_buf, OK_FORMAT);

    free_word_array(command_split);
}
