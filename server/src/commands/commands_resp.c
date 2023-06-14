/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** commands_resp.c
*/

#include "server.h"

void append_to_player_w_buffer(char* dest, char* src)
{
    memmove(dest + strlen(dest), src, strlen(src) + 1);
}

void append_to_gui_w_buffer(char* dest, char* src)
{
    memmove(dest + strlen(dest), src, strlen(src) + 1);
}
