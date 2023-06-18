/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** connect_nbr.c
*/

#include "server.h"

void connect_nbr(__attribute_maybe_unused__ list_args_t* args)
{
    char response[24] = {0};

    sprintf(response, "%ld\n",
            args->client->player->team->max_players -
                args->client->player->team->nb_players_connected);

    append_to_string(args->client->write_buf, response);
}
