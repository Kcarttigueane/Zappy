/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** command.h
*/

#pragma once

#define MAX_ARGS 5

typedef void (*command_func_t)();

typedef struct command_s {
    char* name;
    command_func_t function;
    char* description;
    int expected_arg_count;
} command_t;

// ! Function Prototypes:

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
