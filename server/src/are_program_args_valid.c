/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** are_program_args_valid.c
*/

#include "../include/lib.h"
#include "../include/server.h"

bool are_program_args_valid(int argc, char** argv)
{
    if (argc < 12 || regex_match("[-]{1,2}h(elp)?", argv[1])) {
        fprintf(stdout, SERVER_USAGE);
        return false;
    }
    return true;
}

static int parse_teams_names(int argc, char** argv, int i, server_data_t* s)
{
    i++;

    while (i < argc && argv[i][0] != '-') {
        s->game.team_names = realloc(s->game.team_names,
                                     (s->game.team_count + 1) * sizeof(char*));
        s->game.team_names[s->game.team_count] = argv[i];
        s->game.team_count++;
        i++;
    }

    return i - 1;
}

int parse_arguments(int argc, char** argv, server_data_t* s)
{
    if (!s)
        return handle_failure("Failed to allocate memory for parameters.\n");

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            s->PORT = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-x") == 0 && i + 1 < argc) {
            s->game.width = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-y") == 0 && i + 1 < argc) {
            s->game.height = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-n") == 0) {
            i = parse_teams_names(argc, argv, i, s);
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            s->game.clients_nb = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            s->game.freq = atoi(argv[++i]);
        }
    }

    return SUCCESS;
}

void free_teams_names(server_data_t* s)
{
    if (!s->game.team_names)
        return;

    free(s->game.team_names);
}
