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
#include "debug.h"
#include "error_handling.h"
#include "lib.h"
#include "map.h"
#include "player.h"
#include "responses_format.h"
#include "signals.h"
#include "teams.h"

enum ErrorCodes { SUCCESS = 0, FAILURE = -1, ERROR = 84 };

#define SERVER_USAGE \
    "./zappy_server -p port -x width -y height -n name1 name2 ... \
                -c clientsNb\
                    -f freq\n\
                \tport\t\t is the port number\n\
                \twidth\t\t is the width of the world\n\
                \theight\t\t is the height of the world\n\
                \tnameX\t\t is the name of the team X\n\
                \tclientsNb\t is the number of authorized clients per team\n\
                \tfreq\t\t is the reciprocal of time unit for execution of actions\n"

#define WRONG_FREQUENCY "\n-f option only accepts integer values between 2 and 10000\n\n"
#define WRONG_PORT "\nPort must be between 1024 and 65535\n\n"
#define WRONG_WIDTH "\n-x option only accepts integer values between 10 and 30\n\n"
#define WRONG_HEIGHT "\n-y option only accepts integer values between 10 and 30\n\n"
#define WRONG_CLIENTS_NB "\n-c option only accepts integer values greater or equal to 1\n\n"
#define FREQ_MISSING "\n-f option is missing\n\n"
#define UNIQUE_TEAM_NAMES "\n-n option only accepts unique team names\n\n"

#define DEFAULT_PORT 4242
#define DEFAULT_WIDTH 10
#define DEFAULT_HEIGHT 10
#define DEFAULT_CLIENTS_NB 2
#define DEFAULT_FREQ 100

typedef struct client_s {
    int fd;
    struct sockaddr_in address;
    player_t* player;
    char write_buf[MAX_W_BUFFER_LENGTH];
    char read_buf[MAX_BUFFER];
    LIST_ENTRY(client_s) entries;
} client_t;

// ! STRUCTURES:

typedef struct game_s {
    size_t next_player_id;
    tile_t** map;
    size_t width, height;
    size_t nb_players;
    char** team_names;
    size_t team_count;
    size_t clients_nb;
    size_t freq;
    team_t* team;
    client_t* clients;
    LIST_HEAD(client_head, client_s) client_list;
} game_t;

typedef struct server_data {
    game_t game;
    int PORT;
    int socket_fd;
    fd_set readfds;
    fd_set writefds;
} server_data_t;

// ! SERVER Functions:

void free_teams_names(server_data_t* s);

/**
** @brief Binds the server to a socket and listens for connections.
**
** This function initializes a server address using the INADDR_ANY address and
** the port specified in the server_data_t structure. It then binds the server
** to the socket and starts listening for incoming connections.
**
** @param s Pointer to server_data_t structure containing server details
**          including the socket file descriptor and the port to bind to.
** @return Returns SUCCESS if the server successfully binds and starts
**         listening, otherwise returns the error from handle_error function.
**/
int bind_and_listen_socket(server_data_t* s);

/**
** @brief Initializes a server, sets socket options, binds, and listens.
**
** This function creates a server socket, sets it to reuse the same address,
** and then calls bind_and_listen_socket to bind the socket to an address and
** port and listen for incoming connections.
**
** @param s Pointer to server_data_t structure containing server details.
** @return Returns SUCCESS if the server successfully initializes, sets socket
**         options, binds and starts listening, otherwise returns the error
**         from handle_error function.
**/
int initialize_server(server_data_t* s);

// ! Done
void parse_client_input(server_data_t* s, client_t* client, char* received_buffer);

void process_command_order(game_t* game, client_t* client, char* command_buff);
int find_team_index(game_t* game, char* team_name);

void update_egg_player(game_t* game, client_t* client, char** inputs, egg_t* egg);
void update_normal_player(game_t* game, client_t* client, char** inputs);

int server_loop(server_data_t* s);

void accept_new_connection(server_data_t* s);

void handle_client_activity(server_data_t* s);

void write_and_flush_client_buffer(client_t* client);

int find_object_index(char* object_name);
void execute_commands(server_data_t* s);

// ! CLIENT Functions:

void add_client(game_t* game, client_t* client);
void free_client_list(game_t* game);
void remove_client_by_fd(game_t* game, int fd);

int append_to_gui_write_buffer(game_t* game, char* msg);

player_t* find_player_by_id(game_t* game, int id);
player_t* get_player_from_command(game_t* game, char* command);

// ! Extern Variables:

extern volatile sig_atomic_t stop_server;
extern const command_t GRAPHICAL_COMMANDS[];
extern const size_t GRAPHICAL_COMMANDS_SIZE;

extern const command_t PLAYER_COMMANDS[];
extern const size_t PLAYER_COMMANDS_SIZE;

extern const char* inventory_names[];

void print_all_clients(game_t* game);

bool is_game_over(server_data_t* s);

#endif /* !SERVER_H_ */
