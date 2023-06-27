/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** hatch.c
*/

#include "server.h"

void hatch(game_t* game, client_t* client)
{
    char response[36] = {0};

    sprintf(response, "eht %ld\n", client->player->id);

    append_to_gui_write_buffer(game, response);
}
