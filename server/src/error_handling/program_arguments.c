/*
** EPITECH PROJECT, 2022
** server
** File description:
** program_arguments.c
*/

#include "server.h"

static int is_unique_team_name(char* name, char** team_names, int team_count)
{
    for (int i = 0; i < team_count; i++) {
        if (strcmp(name, team_names[i]) == 0)
            return FAILURE;
    };

    return SUCCESS;
}

static int parse_teams_names(int argc, char** argv, int i, server_data_t* s)
{
    i++;

    while (i < argc && argv[i][0] != '-') {
        if (is_unique_team_name(argv[i], s->game.team_names,
                                s->game.team_count) == FAILURE) {
            fprintf(stderr, UNIQUE_TEAM_NAMES);
            fprintf(stdout, SERVER_USAGE);
            return FAILURE;
        }
        s->game.team_names = realloc(s->game.team_names,
        (s->game.team_count + 1) * sizeof(char*));
        s->game.team_names[s->game.team_count] = argv[i];
        s->game.team_count++;
        i++;
    }

    return i - 1;
}

int process_argument(int i, int argc, char** argv, server_data_t* s)
{
    if (regex_match("[-]{1,2}h(elp)?", argv[i])) {
        fprintf(stdout, SERVER_USAGE);
        exit(SUCCESS);
    }
    if (!strcmp(argv[i], "-p") && i + 1 < argc)
        return validate_and_set_port(argv[++i], s) ? FAILURE : i;
    if (!strcmp(argv[i], "-x") && i + 1 < argc)
        return validate_and_set_width(argv[++i], s) ? FAILURE : i;
    if (!strcmp(argv[i], "-y") && i + 1 < argc)
        return validate_and_set_height(argv[++i], s) ? FAILURE : i;
    if (!strcmp(argv[i], "-n"))
        return parse_teams_names(argc, argv, i, s);
    if (!strcmp(argv[i], "-c") && i + 1 < argc)
        return validate_and_set_clients_nb(argv[++i], s) ? FAILURE : i;
    if (!strcmp(argv[i], "-f")) {
        if (i + 1 >= argc) {
            fprintf(stderr, FREQ_MISSING);
            fprintf(stdout, SERVER_USAGE);
            return FAILURE;
        } else
            return validate_and_set_freq(argv[++i], s) ? FAILURE : i;
    }
    return i;
}

int parse_arguments(int argc, char** argv, server_data_t* s)
{
    if (!s)
        return handle_failure("Failed to allocate memory for parameters.\n");

    s->PORT = DEFAULT_PORT;
    s->game.width = DEFAULT_WIDTH;
    s->game.height = DEFAULT_HEIGHT;
    s->game.freq = DEFAULT_FREQ;
    s->game.clients_nb = DEFAULT_CLIENTS_NB;
    s->game.team_count = 0;
    s->game.team_names = NULL;

    for (int i = 1; i < argc; ++i) {
        i = process_argument(i, argc, argv, s);
        if (i == FAILURE)
            return FAILURE;
    }

    debug_program_args(s);

    return SUCCESS;
}

void free_teams_names(server_data_t* s)
{
    if (!s->game.team_names)
        return;

    free(s->game.team_names);
}
