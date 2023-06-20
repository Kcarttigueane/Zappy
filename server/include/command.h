/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** command.h
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include <stddef.h>

    #define MAX_ARGS 5

    typedef void (*command_func_t)(list_args_t* args);

    typedef struct command_s {
        char* name;
        command_func_t function;
        char* description;
    } command_t;

// ! Function Prototypes (GUI):

/**
** @brief Get the size of the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void get_map_size(list_args_t* args);

/**
** @brief Get the content of a specific tile in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void get_tile_content(list_args_t* args);

/**
** @brief Get all team names in the game.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void get_all_team_names(list_args_t* args);

/**
** @brief Get the position of a player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void get_player_position(list_args_t* args);

/**
** @brief Get the level of a player in the game.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void get_player_level(list_args_t* args);

/**
** @brief Get the player's inventory.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void get_player_inventory(list_args_t* args);

/**
** @brief Get the content of all tiles in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void get_all_tiles_content(list_args_t* args);

/**
** @brief End the incantation in the game.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void end_incantation(list_args_t* args);

/**
** @brief Get the time unit of the server.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void get_time_unit(list_args_t* args);

/**
** @brief Set the time unit of the server.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void set_time_unit(list_args_t* args);

// ! Function Prototypes (Player):

/**
** @brief Forward the player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void forward(list_args_t* args);

/**
** @brief Right the player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**
**/
void right(list_args_t* args);

/**
** @brief Left the player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void left(list_args_t* args);

/**
** @brief Look the player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void look(list_args_t* args);

/**
** @brief Inventory the player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void inventory(list_args_t* args);

/**
** @brief Broadcast the player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/

void broadcast(list_args_t* args);
/**
** @brief Connect the player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void connect_nbr(list_args_t* args);

/**
** @brief Fork the player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void fork_player(list_args_t* args);

/**
** @brief Eject the player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void eject(list_args_t* args);

/**
** @brief Take the player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void take(list_args_t* args);

/**
** @brief Set the player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void set(list_args_t* args);

/**
** @brief Incantation the player in the game map.
**
** @param args list_args_t structure pointer with server data and client data.
**/
void incantation(list_args_t* args);

void hatch(list_args_t* args);
void fake_end(list_args_t* args);

// ! Function Prototypes (Utils):

size_t find_player_command_index(char* command_name);
size_t find_graphical_command_index(char* command_name);

#endif /* !COMMANDS_H_ */
