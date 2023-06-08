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
    size_t nb_players_connected;
    size_t nb_eggs;
} team_t;

#endif /* !TEAMS_H_ */
