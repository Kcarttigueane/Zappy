/*
** EPITECH PROJECT, 2022
** B-YEP-400-LYN-4-1-zappy-kevin.carttigueane
** File description:
** server.h
*/

#ifndef SERVER_H_
#define SERVER_H_

// ! MY INCLUDES:

typedef struct client_s client_t;
typedef struct game_s game_t;
typedef struct server_data server_data_t;
typedef struct list_args list_args_t;

#include "command.h"
#include "common.h"
#include "lib.h"
#include "map.h"
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

#define TIMER_INTERVAL 20

typedef struct client_s {
    int fd;
    struct sockaddr_in address;
    player_t* player;
    char write_buf[MAX_BUFFER];
    char read_buf[MAX_BUFFER];
    LIST_ENTRY(client_s) entries;
} client_t;

// ! STRUCTURES:

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

typedef struct list_args {
    server_data_t* server_data;
    client_t* client;
} list_args_t;

// ! SERVER Functions:

bool are_program_args_valid(int argc, char** argv);
int parse_arguments(int argc, char** argv, server_data_t* s);
void free_teams_names(server_data_t* s);

int bind_and_listen_socket(server_data_t* s);
int initialize_server(server_data_t* s);

int server_loop(server_data_t* s);

void accept_new_connection(server_data_t* s);

void parse_client_input(list_args_t* args, char* input_buffer);

// ! CLIENT Functions:

void add_client(game_t* game, client_t* client);
void free_client_list(game_t* game);
void remove_client_by_fd(game_t* game, int fd);

// ! Extern Variables:

extern volatile sig_atomic_t stop_server;
extern const command_t GRAPHICAL_COMMANDS[];
extern const size_t GRAPHICAL_COMMANDS_SIZE;

extern const command_t PLAYER_COMMANDS[];
extern const size_t PLAYER_COMMANDS_SIZE;

int init_players(server_data_t* s, client_t* client);

void print_all_clients(game_t* game);

#endif /* !SERVER_H_ */
