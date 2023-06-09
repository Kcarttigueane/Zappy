/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** command.h
*/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#define MAX_ARGS 5

typedef void (*command_func_t)(void);

typedef struct command_s {
    char* name;
    command_func_t function;
    char* description;
    int expected_arg_count;
} command_t;

// ! Function Prototypes (GUI):

void msz(void);
void bct(void);
void tna(void);
void pnw(void);
void ppo(void);
void plv(void);
void pin(void);
void pex(void);
void pbc(void);
void pic(void);
void pie(void);
void pfk(void);
void pdr(void);
void pgt(void);
void pdi(void);
void enw(void);
void ebo(void);
void edi(void);
void sgt(void);
void sst(void);
void seg(void);
void smg(void);
void suc(void);
void sbp(void);

// ! Function Prototypes (Player):

void forward(void);
void right(void);
void left(void);
void look(void);
void inventory(void);
void broadcast(void);
void connect_nbr(void);
void fork_player(void);
void eject(void);
void take(void);
void set(void);
void incantation(void);
void hatch(void);
void fake_end(void);

#endif /* !COMMANDS_H_ */
