/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** look.c
*/

#include "colors.h"
#include "server.h"

size_t get_nbr_player_on_tile(game_t* game, coord_t pos)
{
    client_t *client, *temp;

    size_t count = 0;

    LIST_FOREACH_SAFE(client, &game->client_list, entries, temp)
    {
        if (client->player->pos.x == pos.x && client->player->pos.y == pos.y)
            count++;
    }
    return count;
}

int get_nb_element_on_tile(tile_t* tile)
{
    int nb = 0;

    for (size_t i = 0; i < MAX_NB_RESOURCES; ++i)
        nb += tile->quantity[i];

    return nb;
}

void get_objects_on_tile(game_t* game, client_t* client, tile_t* tile, coord_t pos)
{
    size_t nb_players = get_nbr_player_on_tile(game, pos);

    for (size_t i = 0; i < nb_players; ++i) {
        append_to_string(client->write_buf, "player");
        append_to_string(client->write_buf, " ");
    }

    for (size_t j = 0; j < MAX_NB_RESOURCES; j++) {
        if (tile->quantity[j] > 0) {
            // printf("inventory_name: %s\n", inventory_names[j]);
            for (size_t k = 0; k < tile->quantity[j]; ++k) {
                append_to_string(client->write_buf, inventory_names[j]);
                append_to_string(client->write_buf, " ");
            }
        }
    }
}

static void look_south(game_t* game, client_t* client, int level)
{
    player_t* player = client->player;
    for (int i = 0; i <= level; ++i) {
        for (int j = i; j >= -i; --j) {
            int look_x = player->pos.x + j;
            int look_y = player->pos.y - i;
            // wrap around map if out of bounds
            look_x = (look_x + game->width) % game->width;
            look_y = (look_y + game->height) % game->height;

            tile_t* tile = &game->map[look_y][look_x];
            coord_t pos = {look_x, look_y};
            debug_tile_content(tile, pos);
            get_objects_on_tile(game, client, tile, pos);
            append_to_string(client->write_buf, ", ");
        }
    }
}

static void look_east(game_t* game, client_t* client, int level)
{
    player_t* player = client->player;
    for (int i = 0; i <= level; ++i) {
        for (int j = i; j >= -i; --j) {
            int look_x = player->pos.x + i;
            int look_y = player->pos.y + j;
            // wrap around map if out of bounds
            look_x = (look_x + game->width) % game->width;
            look_y = (look_y + game->height) % game->height;

            tile_t* tile = &game->map[look_y][look_x];
            coord_t pos = {look_x, look_y};
            debug_tile_content(tile, pos);
            get_objects_on_tile(game, client, tile, pos);
            append_to_string(client->write_buf, ", ");
        }
    }
}

static void look_north(game_t* game, client_t* client, int level)
{
    player_t* player = client->player;
    for (int i = 0; i <= level; ++i) {
        for (int j = -i; j <= i; ++j) {
            int look_x = player->pos.x + j;
            int look_y = player->pos.y + i;
            // wrap around map if out of bounds
            look_x = (look_x + game->width) % game->width;
            look_y = (look_y + game->height) % game->height;

            tile_t* tile = &game->map[look_y][look_x];
            coord_t pos = {look_x, look_y};
            debug_tile_content(tile, pos);
            get_objects_on_tile(game, client, tile, pos);
            append_to_string(client->write_buf, ", ");
        }
    }
}

static void look_west(game_t* game, client_t* client, int level)
{
    player_t* player = client->player;
    for (int i = 0; i <= level; ++i) {
        for (int j = -i; j <= i; ++j) {
            int look_x = player->pos.x - i;
            int look_y = player->pos.y + j;
            // wrap around map if out of bounds
            look_x = (look_x + game->width) % game->width;
            look_y = (look_y + game->height) % game->height;

            tile_t* tile = &game->map[look_y][look_x];
            coord_t pos = {look_x, look_y};
            debug_tile_content(tile, pos);
            get_objects_on_tile(game, client, tile, pos);
            append_to_string(client->write_buf, ", ");
        }
    }
}

void look(game_t* game, client_t* client)
{
    printf("look\n");
    player_t* player = client->player;
    int level = player->level;

    append_to_string(client->write_buf, "[");
    switch (player->orientation) {
        case NORTH:
            printf("look_north\n");
            look_north(game, client, level);
            break;
        case EAST:
            printf("look_east\n");
            look_east(game, client, level);
            break;
        case SOUTH:
            printf("look_south\n");
            look_south(game, client, level);
            break;
        case WEST:
            printf("look_west\n");
            look_west(game, client, level);
            break;
    }
    append_to_string(client->write_buf, "]\n");
}
