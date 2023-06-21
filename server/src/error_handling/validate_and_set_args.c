/*
** EPITECH PROJECT, 2022
** server
** File description:
** validate_and_set_args.c
*/

#include "server.h"

int validate_and_set_port(char* arg, server_data_t* s)
{
    int port = atoi(arg);

    if (port < 1024 || port > 65535) {
        fprintf(stderr, WRONG_PORT);
        fprintf(stdout, SERVER_USAGE);
        return FAILURE;
    }

    s->PORT = port;
    return SUCCESS;
}

int validate_and_set_width(char* arg, server_data_t* s)
{
    size_t width = strtoul(arg, NULL, 10);

    if (width < 10 || width > 30) {
        fprintf(stderr, WRONG_WIDTH);
        fprintf(stdout, SERVER_USAGE);
        return FAILURE;
    }

    s->game.width = width;
    return SUCCESS;
}

int validate_and_set_height(char* arg, server_data_t* s)
{
    size_t height = strtoul(arg, NULL, 10);

    if (height < 10 || height > 30) {
        fprintf(stderr, WRONG_HEIGHT);
        fprintf(stdout, SERVER_USAGE);
        return FAILURE;
    }
    s->game.height = height;
    return SUCCESS;
}

int validate_and_set_clients_nb(char* arg, server_data_t* s)
{
    size_t clients_nb = strtoul(arg, NULL, 10);

    if (clients_nb < 1) {
        fprintf(stderr, WRONG_CLIENTS_NB);
        fprintf(stdout, SERVER_USAGE);
        return FAILURE;
    }

    s->game.clients_nb = clients_nb;
    return SUCCESS;
}

int validate_and_set_freq(char* arg, server_data_t* s)
{
    size_t freq = strtoul(arg, NULL, 10);

    if (freq < 2 || freq > 10000) {
        fprintf(stderr, WRONG_FREQUENCY);
        fprintf(stdout, SERVER_USAGE);
        return FAILURE;
    }

    s->game.freq = freq;
    return SUCCESS;
}