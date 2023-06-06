/*
** EPITECH PROJECT, 2022
** B-YEP-400-LYN-4-1-zappy-kevin.carttigueane
** File description:
** server.h
*/

#pragma once

#include <stdbool.h>
#include <stdio.h>

#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <uuid/uuid.h>
#include "unistd.h"

#include <sys/queue.h>

#include <time.h>

// ! MY INCLUDES:

#include "command.h"
#include "lib.h"
#include "player.h"
#include "signals.h"

enum ErrorCodes { SUCCESS = 0, FAILURE = -1, ERROR = 84 };

#define SERVER_USAGE \
    "./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq\n\
\tport\t\t is the port number\n\
\twidth\t\t is the width of the world\n\
\theight\t\t is the height of the world\n\
\tnameX\t\t is the name of the team X\n\
\tclientsNb\t is the number of authorized clients per team\n\
\tfreq\t\t is the reciprocal of time unit for execution of actions"

// ! STRUCTURES:

#define MAX_NB_RESOURCES 7

typedef struct {
    size_t quantity[MAX_NB_RESOURCES];
} Tile;

typedef struct server_data {
    int time_unit;
    game_t game;
    int PORT;
    int socket_fd;
    fd_set readfds;
    fd_set writefds;
} server_data_t;

// typedef struct {
//     int egg_num;
//     Player* player;  // the player who laid the egg
//     int x, y;        // position of the egg on the map
// } Egg;

typedef struct game_s {
    Tile** map;
    size_t width, height;
    player_t* players;
    int nb_players;
    Egg* eggs;  // a dynamically-allocated array of Egg structs
    int nb_eggs;
} game_t;

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

// ! SERVER Functions:

bool are_program_args_valid(int argc, char const* argv[]);

int bind_and_listen_socket(server_data_t* s);
int initialize_server(server_data_t* s);

int server_loop(server_data_t* s);

// ! Extern Variables:

extern volatile sig_atomic_t stop_server;
