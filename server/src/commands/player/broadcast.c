/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** broadcast.c
*/

#include "server.h"

#define NO_DIRECTION 0
#define NORTH 1
#define NORTH_WEST 2
#define WEST 3
#define SOUTH_WEST 4
#define SOUTH 5
#define SOUTH_EAST 6
#define EAST 7
#define NORTH_EAST 8

typedef struct {
    int min_ratio;
    int max_ratio;
    int direction;
} region_t;

const region_t regions[8] = {
    {-2, -1, NORTH},      // front-right
    {-1, 1, WEST},        // right
    {1, 2, SOUTH_WEST},   // back-right
    {2, 0, SOUTH},        // back
    {0, -2, SOUTH_EAST},  // back-left
    {-2, -1, EAST},       // left
    {-1, 1, NORTH_EAST},  // front-left
    {1, 2, NORTH}         // front
};

int shortest_delta_x(size_t map_width, int x1, int x2)
{
    int delta_x = abs(x2 - x1);

    if (delta_x > (int)map_width / 2) {
        delta_x = (int)map_width - delta_x;
    }

    if (x1 > x2) {
        delta_x = -delta_x;
    }

    return delta_x;
}

int shortest_delta_y(size_t map_height, int y1, int y2)
{
    int delta_y = abs(y2 - y1);

    if (delta_y > (int)map_height / 2) {
        delta_y = (int)map_height - delta_y;
    }

    if (y1 > y2) {
        delta_y = -delta_y;
    }

    return delta_y;
}

int adjust_direction(int direction, orientation_t orientation)
{
    int adjusted_direction = (direction + orientation - 2) % 8;
    if (adjusted_direction == 0) {
        adjusted_direction = 8;
    }
    return adjusted_direction;
}

int calculate_direction(int delta_x, int delta_y)
{
    if (delta_x == 0 && delta_y == 0) {
        return NO_DIRECTION;
    }

    int ratio = 2 * delta_y / delta_x;
    int direction = -1;

    for (int i = 0; i < 8; i++) {
        if (ratio >= regions[i].min_ratio && ratio < regions[i].max_ratio) {
            direction = regions[i].direction;
            break;
        }
    }

    return direction;
}

void broadcast(game_t* game, client_t* client)
{
    player_t* player = client->player;
    char* command = peek_command(client);

    char** command_split = split_str(command, " ");
    char* message = command_split[1];

    if (message == NULL) {
        append_to_string(client->write_buf, KO_FORMAT);
        return;
    }

    int x = player->pos.x;
    int y = player->pos.y;
    int direction;
    int delta_x;
    int delta_y;

    client_t *curr_client, *tmp;

    LIST_FOREACH_SAFE(curr_client, &game->client_list, entries, tmp)
    {
        if (curr_client->fd != client->fd && curr_client->player->state == PLAYER) {
            delta_x = shortest_delta_x(game->width, x, curr_client->player->pos.x);
            delta_y = shortest_delta_y(game->height, y, curr_client->player->pos.y);
            direction = calculate_direction(delta_x, delta_y);
            direction = adjust_direction(direction, curr_client->player->orientation);
            dprintf(curr_client->fd, "message %d, %s\n", direction, message);
        }
    }

    char response[1024] = {0};

    sprintf(response, PBC_FORMAT, player->id, message);

    append_to_gui_write_buffer(game, response);

    append_to_string(client->write_buf, OK_FORMAT);

    free_word_array(command_split);
}
