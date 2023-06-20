/*
** EPITECH PROJECT, 2022
** server
** File description:
** program_arguments.c
*/

#include "server.h"

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

int process_argument(int i, int argc, char** argv, server_data_t* s)
{
    if (regex_match("[-]{1,2}h(elp)?", argv[i])) {
        fprintf(stdout, SERVER_USAGE);
        exit(SUCCESS);
    }
    if (!strcmp(argv[i], "-p") && i + 1 < argc) {
        validate_and_set_port(argv[++i], s);
        return i;
    }
    if (!strcmp(argv[i], "-x") && i + 1 < argc) {
        validate_and_set_width(argv[++i], s);
        return i;
    }
    if (!strcmp(argv[i], "-y") && i + 1 < argc) {
        validate_and_set_height(argv[++i], s);
        return i;
    }
    if (!strcmp(argv[i], "-n")) {
        return parse_teams_names(argc, argv, i, s);
    }
    if (!strcmp(argv[i], "-c") && i + 1 < argc) {
        validate_and_set_clients_nb(argv[++i], s);
        return i;
    }
    if (!strcmp(argv[i], "-f") && i + 1 < argc) {
        validate_and_set_freq(argv[++i], s);
        return i;
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
