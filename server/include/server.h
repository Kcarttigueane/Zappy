/*
** EPITECH PROJECT, 2022
** B-YEP-400-LYN-4-1-zappy-kevin.carttigueane
** File description:
** server.h
*/

#ifndef SERVER_H_
#define SERVER_H_

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
#include "teams.h"

enum ErrorCodes { SUCCESS = 0, FAILURE = -1, ERROR = 84 };

#define SERVER_USAGE \
    "./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb\
     -f freq\n\
\tport\t\t is the port number\n\
\twidth\t\t is the width of the world\n\
\theight\t\t is the height of the world\n\
\tnameX\t\t is the name of the team X\n\
\tclientsNb\t is the number of authorized clients per team\n\
\tfreq\t\t is the reciprocal of time unit for execution of actions\n"

#define CALC_TOTAL_RESOURCES(total_tiles)                             \
    {                                                                 \
        (total_tiles) * 0.5, (total_tiles)*0.3, (total_tiles)*0.15,   \
            (total_tiles)*0.1, (total_tiles)*0.1, (total_tiles)*0.08, \
            (total_tiles)*0.05                                        \
    }

#ifndef LIST_FOREACH_SAFE
#    define LIST_FOREACH_SAFE(var, head, field, tvar) \
        for ((var) = LIST_FIRST((head));              \
             (var) && ((tvar) = LIST_NEXT((var), field), 1); (var) = (tvar))
#endif

// ! STRUCTURES:

enum MAX_VALUES {
    MAX_NB_RESOURCES = 7,
    MAX_NB_PLAYERS = 6,
    MAX_BUFFER = 1024,
    MAX_COMMANDS_LENGTH = 256,
    MAX_COMMANDS_PER_CLIENT = 10,
};

typedef struct {
    size_t quantity[MAX_NB_RESOURCES];
} Tile;

typedef struct game_s {
    Tile** map;
    size_t width, height;
    size_t nb_players;
    char** team_names;
    size_t team_count;
    size_t clients_nb;
    size_t freq;
    client_t* clients;
    LIST_HEAD(client_head, client_s) client_list;
} game_t;

typedef struct server_data {
    int time_unit;
    game_t game;
    int PORT;
    int socket_fd;
    fd_set readfds;
    fd_set writefds;
} server_data_t;

// ! SERVER Functions:

bool are_program_args_valid(int argc, char** argv);
int parse_arguments(int argc, char** argv, server_data_t* s);
void free_teams_names(server_data_t* s);

int bind_and_listen_socket(server_data_t* s);
int initialize_server(server_data_t* s);

int server_loop(server_data_t* s);

void accept_new_connection(server_data_t* s);

// ! MAP Functions:

void print_resources_location(Tile** map, size_t height, size_t width);
void calc_total_resources(int total_tiles, int* total_resources);
Tile** init_map(size_t width, size_t height);
void shuffle(int* array, size_t n);
void distribute_resources(Tile** map, int total_resources[], size_t height,
                          size_t width);
void free_map(Tile** map, size_t width);

// ! CLIENT Functions:

void add_client(game_t* game, client_t* client);
void free_client_list(game_t* game);
void remove_client_by_fd(game_t* game, int fd);

// ! Extern Variables:

extern volatile sig_atomic_t stop_server;

int init_players(server_data_t* s, client_t* client);

void print_all_clients(game_t* game);

#endif /* !SERVER_H_ */
