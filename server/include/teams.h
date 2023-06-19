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
    LIST_ENTRY(egg_s) entries;  // Add this line
} egg_t;

typedef struct team_s {
    char* name;
    size_t max_players;
    size_t nb_players_connected;
    egg_t* eggs;
    LIST_HEAD(egg_head, egg_s) egg_list;
} team_t;

egg_t* random_select_egg(team_t* team);
int is_egg_list_empty(team_t* team);
egg_t* create_and_add_egg(team_t* team, coord_t pos);
void free_list(team_t* team);
void print_egg_list(team_t* team);
egg_t* find_egg_by_id(team_t* team, size_t id);
void remove_egg_by_id(team_t* team, size_t id);

team_t* find_team_by_name(server_data_t* data, char* team_name);

#endif /* !TEAMS_H_ */
