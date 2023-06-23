/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** player.h
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "common.h"
    #include "map.h"
    #include "queue.h"
    #include "server.h"
    #include "teams.h"

    typedef enum orientation_s {
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4,
    } orientation_t;

    typedef enum state_s {
        NONE,
        EGG,
        ACTIVE,
        DEAD,
    } state_t;

    typedef enum inventory_s {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    } inventory_t;

    typedef struct player_s {
        bool is_graphical;
        size_t id;
        bool is_frozen;
        coord_t pos;
        orientation_t orientation;
        size_t level;
        size_t inventory[MAX_NB_RESOURCES];
        int life_units;
        time_t start_time;
        state_t state;
        char* team_name;
        command_queue_t command_queue;
    } player_t;

// ! Function prototypes:


#endif /* !PLAYER_H_ */
