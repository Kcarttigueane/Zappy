/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** teams.h
*/

#ifndef TEAMS_H_
#define TEAMS_H_

#include "player.h"

typedef struct team_s {
    char* name;
    size_t max_players;
    size_t nb_players;
    size_t nb_eggs;
    player_t** players;
} team_t;

#endif /* !TEAMS_H_ */
