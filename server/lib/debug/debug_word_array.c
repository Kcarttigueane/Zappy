/*
** EPITECH PROJECT, 2022
** B-YEP-400-LYN-4-1-zappy-kevin.carttigueane
** File description:
** debug_word_array.c
*/

#include <stdio.h>
#include <unistd.h>
#include "colors.h"

void debug_word_array(char** word_array)
{
    if (word_array == NULL)
        return;

    for (int i = 0; word_array[i] != NULL; i++) {
        printf("word_array[");
        printf(GREEN);
        printf("%d", i);
        printf(RESET);
        printf("] = ");
        printf("\"");
        printf(YELLOW);
        printf("%s", word_array[i]);
        printf(RESET);
        printf("\"");
        printf("\n");
    }
}
