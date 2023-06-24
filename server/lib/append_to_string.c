/*
** EPITECH PROJECT, 2022
** server
** File description:
** append_to_string.c
*/

#include "lib.h"

void append_to_string(char* dest, char* src)
{
    memmove(dest + strlen(dest), src, strlen(src) + 1);
}
