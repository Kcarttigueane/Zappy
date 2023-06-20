/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** teams.h
*/

#ifndef TEAMS_H_
    #define TEAMS_H_

    #include "player.h"

    typedef struct egg_s {
        size_t id;
        coord_t pos;
        LIST_ENTRY(egg_s) entries;
    } egg_t;

    typedef struct team_s {
        char* name;
        size_t max_players;
        size_t nb_players_connected;
        egg_t* eggs;
        LIST_HEAD(egg_head, egg_s) egg_list;
    } team_t;


// ! Function prototypes:

/**
 * \brief Selects a random egg from the team's list of eggs.
 *
 * \param team The team from which an egg should be selected.
 * \return A pointer to the selected egg.
 */
egg_t* random_select_egg(team_t* team);

/**
 * \brief Checks if the team's egg list is empty.
 *
 * \param team The team whose egg list should be checked.
 * \return Returns 1 if the list is empty, 0 otherwise.
 */
int is_egg_list_empty(team_t* team);

/**
 * \brief Creates and adds an egg to the team's list.
 *
 * \param team The team to which an egg should be added.
 * \param pos The position where the egg should be placed.
 * \return A pointer to the new egg.
 */
egg_t* create_and_add_egg(team_t* team, coord_t pos);

/**
 * \brief Frees the memory allocated for the team's list of eggs.
 *
 * \param team The team whose egg list should be freed.
 */
void free_list(team_t* team);

/**
 * \brief Prints the team's list of eggs.
 *
 * \param team The team whose egg list should be printed.
 */
void print_egg_list(team_t* team);

/**
 * \brief Finds an egg in the team's list by its ID.
 *
 * \param team The team whose egg list should be searched.
 * \param id The ID of the egg to find.
 * \return A pointer to the found egg.
 */
egg_t* find_egg_by_id(team_t* team, size_t id);

/**
 * \brief Removes an egg from the team's list by its ID and frees the memory.
 *
 * \param team The team whose egg should be removed.
 * \param id The ID of the egg to remove.
 */
void remove_egg_by_id(team_t* team, size_t id);

team_t* find_team_by_name(server_data_t* data, char* team_name);

#endif /* !TEAMS_H_ */
