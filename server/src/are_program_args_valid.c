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

static int add_team(server_data_t* s, char* team_name)
{
    char** tmp =
        realloc(s->game.team_names, sizeof(char*) * (s->game.team_count + 1));

    if (tmp == NULL)
        return FAILURE;

    s->game.team_names = tmp;
    s->game.team_names[s->game.team_count++] = strdup(team_name);
    return SUCCESS;
}

// int parse_arguments(int argc, char** argv, server_data_t* s)
// {
//     int option;

//     while ((option = getopt(argc, argv, "p:x:y:n:c:f:")) != FAILURE) {
//         switch (option) {
//             case 'p':
//                 s->PORT = atoi(optarg);
//                 printf("Port: %d\n", s->PORT);
//                 break;
//             case 'x':
//                 printf("Width: %d\n", atoi(optarg));
//                 s->game.width = atoi(optarg);
//                 break;
//             case 'y':
//                 printf("Height: %d\n", atoi(optarg));
//                 s->game.height = atoi(optarg);
//                 break;
//             case 'n':
//                 printf("Team name: %s\n", optarg);
//                 if (add_team(s, optarg) != 0) {
//                     return FAILURE;
//                 }
//                 break;
//             case 'c':
//                 printf("Clients per team: %d\n", atoi(optarg));
//                 s->game.clients_nb = atoi(optarg);
//                 break;
//             case 'f':
//                 printf("Frequency: %d\n", atoi(optarg));
//                 s->game.freq = atoi(optarg);
//                 break;
//             default:
//                 return FAILURE;
//         }
//     }

//     return SUCCESS;
// }

int parse_arguments(int argc, char** argv, server_data_t* s)
{
    if (s == NULL) {
        printf("Failed to allocate memory for parameters.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            s->PORT = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-x") == 0 && i + 1 < argc) {
            s->width = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-y") == 0 && i + 1 < argc) {
            s->height = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-n") == 0) {
            i++;
            while (i < argc && argv[i][0] != '-') {
                s->teams =
                    realloc(s->teams, (s->team_count + 1) * sizeof(char*));
                s->teams[s->team_count] = argv[i];
                s->team_count++;
                i++;
            }
            i--;  // roll back one argument to handle next option correctly
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            s->clients_nb = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            s->freq = atoi(argv[++i]);
        }
    }

    return s;
}
