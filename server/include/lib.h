/*
** EPITECH PROJECT, 2022
** B-YEP-400-LYN-4-1-zappy-kevin.carttigueane
** File description:
** lib.h
*/

#pragma once

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

// ! STR TO WORD ARRAY functions:

size_t count_tokens(const char* str, const char* delimiter);
char** split_str(char* str, char* delimiter);

// ! WORD ARRAY functions:

size_t get_size_word_array(char** array);
void free_word_array(char** map);

// ! FILE functions:

FILE* open_file(const char* filename, const char* mode);
char* read_file_contents(FILE* file);

// ! STRING functions:

char* my_strcat(char* s1, char* s2);

// ! DEBUG functions:

void debug_word_array(char** word_array);

int handle_error(const char* msg);
int handle_failure(const char* msg);

// ! Regex functions:

bool regex_match(const char* pattern, const char* string);

// ! TIME functions:

char* timestamp_to_string(time_t timestamp);
time_t string_to_timestamp(char* str);
