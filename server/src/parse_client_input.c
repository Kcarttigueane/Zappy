/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** parse_client_input.c
*/

#include "server.h"

void parse_client_input(list_args_t* args, char* input_buffer)
{
    char** split_command = split_str(input_buffer, "\n");

    debug_word_array(split_command);
}
