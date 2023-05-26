/*
** EPITECH PROJECT, 2023
** server
** File description:
** main.c
*/

#include "./include/server.h"

int main(int argc, char const* argv[])
{
    if (!are_program_args_valid(argc, argv))
        return ERROR;

    if (setup_signal_handler() == ERROR)
        return ERROR;

    return 0;
}
