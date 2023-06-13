/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** command.h
*/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stddef.h>

#define MAX_ARGS 5

typedef void (*command_func_t)(list_args_t* args);

typedef struct command_s {
    char* name;
    command_func_t function;
    char* description;
} command_t;

// ! Function Prototypes (GUI):

void msz(list_args_t* args);
void bct(list_args_t* args);
void tna(list_args_t* args);
void ppo(list_args_t* args);
void plv(list_args_t* args);
void pin(list_args_t* args);
void mct(list_args_t* args);
void pie(list_args_t* args);
void sgt(list_args_t* args);
void sst(list_args_t* args);

// ! Function Prototypes (Player):

void forward(list_args_t* args);
void right(list_args_t* args);
void left(list_args_t* args);
void look(list_args_t* args);
void inventory(list_args_t* args);
void broadcast(list_args_t* args);
void connect_nbr(list_args_t* args);
void fork_player(list_args_t* args);
void eject(list_args_t* args);
void take(list_args_t* args);
void set(list_args_t* args);
void incantation(list_args_t* args);
void hatch(list_args_t* args);
void fake_end(list_args_t* args);

// ! Function Prototypes (Utils):

size_t find_player_command_index(char* command_name);
size_t find_graphical_command_index(char* command_name);

#endif /* !COMMANDS_H_ */
