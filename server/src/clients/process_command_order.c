/*
** EPITECH PROJECT, 2022
** server
** File description:
** process_command_order.c
*/

#include "server.h"

static void graphical_first_command(game_t* game, client_t* client)
{
    client->player->state = GRAPHICAL;
    init_command_queue(client);

    get_map_size(game, client);
    get_time_unit(game, client);
    get_all_tiles_content(game, client);
    get_all_team_names(game, client);
    get_all_player_positions(game);
}

static void player_first_command(game_t* game, client_t* client, char** split_command)
{
    if (!is_team_name_valid(game, split_command))
        return;

    printf("New player connected\n");

    // ! ! ! check for egg and all
    team_t* team = find_team_by_name(game, split_command[0]);

    if (team->nb_players_connected >= team->max_players) {
        printf("No slots available for the team %s\n", team->name);
        append_to_string(client->write_buf, KO_FORMAT);
        return;
    }

    if (!is_egg_list_empty(team)) {
        printf("Egg available\n");
        egg_t* egg = random_select_egg(team);
        update_egg_player(game, client, split_command, egg);

        char response[256] = {0};
        sprintf(response, EBO_FORMAT, egg->id);
        append_to_gui_write_buffer(game, response);
        return;
    } else {
        update_normal_player(game, client, split_command);
    }

    char response[1024] = {0};
    sprintf(response, PNW_FORMAT, client->player->id, client->player->pos.x, client->player->pos.y,
            client->player->orientation, client->player->level, client->player->team_name);
    append_to_gui_write_buffer(game, response);
}

static void handle_first_client_msg(game_t* game, client_t* client, char** split_command)
{
    if (!strcmp(split_command[0], "GRAPHIC")) {
        graphical_first_command(game, client);
    } else {
        player_first_command(game, client, split_command);
    }
}

static void handle_client_command(game_t* game, client_t* client, char** split_command,
                                  char* command_buff)
{
    if (client->player->state == GRAPHICAL) {
        for (size_t i = 0; i < GRAPHICAL_COMMANDS_SIZE; i++) {
            if (!strcasecmp(split_command[0], GRAPHICAL_COMMANDS[i].name)) {
                enqueue_command(client, command_buff, game->freq);
                return;
            }
        }
    } else {
        for (size_t i = 0; i < PLAYER_COMMANDS_SIZE; i++) {
            if (!strcasecmp(split_command[0], PLAYER_COMMANDS[i].name)) {
                enqueue_command(client, command_buff, game->freq);
                return;
            }
        }
    }
}

void process_command_order(game_t* game, client_t* client, char* command_buff)
{
    char** split_command = split_str(command_buff, " ");

    if (!split_command)
        return;

    if (client->player->state == NONE)
        handle_first_client_msg(game, client, split_command);
    else
        handle_client_command(game, client, split_command, command_buff);

    free_word_array(split_command);
}
