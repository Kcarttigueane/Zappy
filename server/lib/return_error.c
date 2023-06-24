/*
** EPITECH PROJECT, 2022
** B-YEP-400-LYN-4-1-zappy-kevin.carttigueane
** File description:
** return_error.c
*/

#include "../include/lib.h"
#include "../include/colors.h"

int handle_error(const char* msg)
{
    fprintf(stderr, RED "%s" RESET "\n", msg);
    return 84;
}

int handle_failure(const char* msg)
{
    fprintf(stderr, RED "%s" RESET "\n", msg);
    return -1;
}
