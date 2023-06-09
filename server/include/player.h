/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** player.h
*/

#pragma once

typedef struct client_s client_t;
typedef struct team_s team_t;
typedef struct player_s player_t;

#include "./server.h"
#include "teams.h"

/*
    q0 food
    q1 linemate
    q2 deraumere
    q3 sibur
    q4 mendiane
    q5 phiras
    q6 thystame
*/

typedef enum orientation_s {
    UP_CENTER = 1,
    UP_LEFT,
    CENTER_LEFT,
    DOWN_LEFT,
    DOWN_CENTER,
    DOWN_RIGHT,
    CENTER_RIGHT,
    UP_RIGHT
} orientation_t;

typedef struct coord_s {
    int x;
    int y;
} coord_t;

typedef enum state_s {
    NONE,
    EGG,
    ACTIVE,
    DEAD,
} state_t;

typedef struct command_queue_s {
    char commands[10][256];
    int front;
    int rear;
} command_queue_t;

typedef struct player_s {
    size_t id;
    coord_t pos;
    orientation_t orientation;
    size_t level;
    char* team_name;
    size_t inventory[7];
    size_t life_units;
    time_t last_eat_time;
    state_t state;
    command_queue_t command_queue;
    team_t* team;
} player_t;

typedef struct client_s {
    int fd;
    struct sockaddr_in address;
    player_t* player;
    char write_buf[1024];
    char read_buf[1024];
    LIST_ENTRY(client_s) entries;
} client_t;

// ! Function prototypes:

//  ! Command queue functions:

void init_command_queue(client_t* client);
int is_command_queue_empty(client_t* client);
int is_command_queue_full(client_t* client);
void enqueue_command(client_t* client, const char* command);
void dequeue_command(client_t* client);
void print_command_queue(client_t* client);

void print_client_info(client_t* client);
