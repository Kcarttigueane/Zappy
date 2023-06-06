/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** command.h
*/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#define MAX_ARGS 5

typedef void (*command_func_t)();

typedef struct command_s {
    char* name;
    command_func_t function;
    char* description;
    int expected_arg_count;
} command_t;

// ! Function Prototypes (GUI):

void msz();
void bct();
void tna();
void pnw();
void ppo();
void plv();
void pin();
void pex();
void pbc();
void pic();
void pie();
void pfk();
void pdr();
void pgt();
void pdi();
void enw();
void ebo();
void edi();
void sgt();
void sst();
void seg();
void smg();
void suc();
void sbp();

// ! Function Prototypes (Player):

void forward();
void right();
void left();
void look();
void inventory();
void broadcast();
void connect_nbr();
void fork_player();
void eject();
void take();
void set();
void incantation();
void hatch();
void fake_end();

#endif /* !COMMANDS_H_ */
