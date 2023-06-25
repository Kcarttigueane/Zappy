/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** command.h
*/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stddef.h>

typedef void (*command_func_t)(game_t* game, client_t* client);

typedef struct command_s {
    char* name;
    command_func_t function;
    char* description;
    int action_time;
} command_t;

typedef struct incantation_requirements_s {
    size_t num_players;
    size_t linemate;
    size_t deraumere;
    size_t sibur;
    size_t mendiane;
    size_t phiras;
    size_t thystame;
} incantation_requirements_t;

static const incantation_requirements_t INCANTATION_REQUIREMENTS[] = {
    {1, 1, 0, 0, 0, 0, 0},  // ! Level 1->2
    {2, 1, 1, 1, 0, 0, 0},  // ! Level 2->3
    {2, 2, 0, 1, 0, 2, 0},  // ! Level 3->4
    {4, 1, 1, 2, 0, 1, 0},  // ! Level 4->5
    {4, 1, 2, 1, 3, 0, 0},  // ! Level 5->6
    {6, 1, 2, 3, 0, 1, 0},  // ! Level 6->7
    {6, 2, 2, 2, 2, 2, 1},  // ! Level 7->8
};

// ! Function Prototypes (GUI):

/**
 * @brief Get the size of the game map.
 *
 * @param game Pointer to the game structure containing the map data.
 * @param client Pointer to the client structure requesting the map size.
 */
void get_map_size(game_t* game, client_t* client);

/**
 * @brief Get the content of a specific tile in the game map.
 *
 * @param game Pointer to the game structure containing the map data.
 * @param client Pointer to the client structure requesting the tile content.
 */
void get_tile_content(game_t* game, client_t* client);

/**
 * @brief Get all team names in the game.
 *
 * @param game Pointer to the game structure containing the team data.
 * @param client Pointer to the client structure requesting the team names.
 */
void get_all_team_names(game_t* game, client_t* client);

/**
 * @brief Get the position of a player in the game map.
 *
 * @param game Pointer to the game structure containing the player and map data.
 * @param client Pointer to the client structure representing the player.
 */
void get_player_position(game_t* game, client_t* client);

/**
 * @brief Get the level of a player in the game.
 *
 * @param game Pointer to the game structure containing the player data.
 * @param client Pointer to the client structure representing the player.
 */
void get_player_level(game_t* game, client_t* client);

/**
 * @brief Get the player's inventory.
 *
 * @param game Pointer to the game structure containing the player data.
 * @param client Pointer to the client structure representing the player.
 */
void get_player_inventory(game_t* game, client_t* client);

/**
 * @brief Get the content of all tiles in the game map.
 *
 * @param game Pointer to the game structure containing the map data.
 * @param client Pointer to the client structure requesting the tile contents.
 */
void get_all_tiles_content(game_t* game, client_t* client);

/**
 * @brief End the incantation in the game.
 *
 * @param game Pointer to the game structure.
 * @param client Pointer to the client structure performing the incantation.
 */
void end_incantation(game_t* game, client_t* client);

/**
 * @brief Get the time unit of the server.
 *
 * @param game Pointer to the game structure containing the time unit data.
 * @param client Pointer to the client structure requesting the time unit.
 */
void get_time_unit(game_t* game, client_t* client);

/**
 * @brief Set the time unit of the server.
 *
 * @param game Pointer to the game structure where the time unit data will be set.
 * @param client Pointer to the client structure setting the time unit.
 */
void set_time_unit(game_t* game, client_t* client);

/**
 * @brief Get the positions of all players in the game map.
 *
 * @param game Pointer to the game structure containing the player and map data.
 * @param client Pointer to the client structure requesting the player positions.
 */
void get_all_player_positions(game_t* game);


// ! Function Prototypes (Player):

/**
 * @brief Move the player forward in the game map.
 *
 * @param game Pointer to the game structure containing the player and map data.
 * @param client Pointer to the client structure representing the player.
 */
void forward(game_t* game, client_t* client);

/**
 * @brief Rotate the player to the right in the game map.
 *
 * @param game Pointer to the game structure containing the player data.
 * @param client Pointer to the client structure representing the player.
 */
void right(game_t* game, client_t* client);

/**
 * @brief Rotate the player to the left in the game map.
 *
 * @param game Pointer to the game structure containing the player data.
 * @param client Pointer to the client structure representing the player.
 */
void left(game_t* game, client_t* client);

/**
 * @brief Get the viewpoint of the player in the game map.
 *
 * @param game Pointer to the game structure containing the player and map data.
 * @param client Pointer to the client structure representing the player.
 */
void look(game_t* game, client_t* client);

/**
 * @brief Retrieve the player's inventory in the game.
 *
 * @param game Pointer to the game structure containing the player data.
 * @param client Pointer to the client structure representing the player.
 */
void inventory(game_t* game, client_t* client);

/**
 * @brief Broadcast a message to other players in the game map.
 *
 * @param game Pointer to the game structure containing the player data.
 * @param client Pointer to the client structure representing the broadcasting player.
 */
void broadcast(game_t* game, client_t* client);

/**
 * @brief Connect the player to the game.
 *
 * @param game Pointer to the game structure.
 * @param client Pointer to the client structure representing the connecting player.
 */
void connect_nbr(game_t* game, client_t* client);

/**
 * @brief Create a duplicate of the player in the game.
 *
 * @param game Pointer to the game structure containing the player data.
 * @param client Pointer to the client structure representing the player to be duplicated.
 */
void fork_player(game_t* game, client_t* client);

/**
 * @brief Eject the player from the game map.
 *
 * @param game Pointer to the game structure containing the player data.
 * @param client Pointer to the client structure representing the ejected player.
 */
void eject(game_t* game, client_t* client);

/**
 * @brief Have the player take an object from the game map.
 *
 * @param game Pointer to the game structure containing the player and map data.
 * @param client Pointer to the client structure representing the player taking an object.
 */
void take(game_t* game, client_t* client);

/**
 * @brief Have the player set an object on the game map.
 *
 * @param game Pointer to the game structure containing the player and map data.
 * @param client Pointer to the client structure representing the player setting an object.
 */
void set(game_t* game, client_t* client);

/**
 * @brief Perform the Start of incantation by the player in the game.
 *
 * @param game Pointer to the game structure containing the player data.
 * @param client Pointer to the client structure representing the player performing the incantation.
 */
void start_incantation(game_t* game, client_t* client);

/**
 * @brief Perform the End of incantation by the player in the game.
 *
 * @param game Pointer to the game structure containing the player data.
 * @param client Pointer to the client structure representing the player performing the incantation.
 */
void end_incantation(game_t* game, client_t* client);

/**
 * @brief Hatch a new player in the game.
 *
 * @param game Pointer to the game structure.
 * @param client Pointer to the client structure representing the new player.
 */
void hatch(game_t* game, client_t* client);


// ! Function Prototypes (Utils):

/**
 * @brief Finds the index of a given player command.
 *
 * This function iterates over the array of player commands and returns the index of the command
 * matching the provided name.
 *
 * @param command_name Name of the command to find.
 * @return Index of the found command. If command not found, prints error message and returns FAILURE.
 */
int find_player_command_index(char* command_name);

/**
 * @brief Finds the index of a given graphical command.
 *
 * This function iterates over the array of graphical commands and returns the index of the command
 * matching the provided name.
 *
 * @param command_name Name of the command to find.
 * @return Index of the found command. If command not found, prints error message and returns FAILURE.
 */
int find_graphical_command_index(char* command_name);

#endif /* !COMMANDS_H_ */
