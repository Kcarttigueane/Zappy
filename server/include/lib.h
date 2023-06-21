/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
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

/**
 ** @brief Counts the number of tokens in a string.
 **
 ** @param str String to count tokens in.
 ** @param delimiter The delimiter used to split the string.
 ** @return The number of tokens in the string.
**/
size_t count_tokens(const char* str, const char* delimiter);

/**
 ** @brief Splits a string into tokens based on a delimiter.
 **
 ** @param str String to split.
 ** @param delimiter The delimiter used to split the string.
 ** @return An array of pointers to the tokens.
**/
char** split_str(char* str, char* delimiter);

// ! WORD ARRAY functions:

/**
 ** @brief Returns the size of a word array.
 **
 ** @param array The word array to get the size of.
 ** @return The size of the word array.
**/
size_t get_size_word_array(char** array);

/**
 ** @brief Frees a word array.
 **
 ** @param map The word array to free.
**/
void free_word_array(char** map);

/**
 ** @brief Concatenates two strings.
 **
 ** @param s1 The first string.
 ** @param s2 The second string.
 ** @return A new string that is the concatenation of s1 and s2.
**/

/**
 ** @brief Prints or logs the contents of a word array for debugging purposes.
 **
 ** @param word_array The word array to debug.
**/
void debug_word_array(char** word_array);

// ! STRING functions:

char* my_strcat(char* s1, char* s2);

/**
 ** @brief Prints an error message and returns an error code.
 **
 ** @param msg The error message to print.
 ** @return The error code.
**/
int handle_error(const char* msg);

/**
 ** @brief Prints a failure message and returns a failure code.
 **
 ** @param msg The failure message to print.
 ** @return The failure code.
**/
int handle_failure(const char* msg);

/**
 ** @brief Checks if a string matches a regex pattern.
 **
 ** @param pattern The regex pattern to match against.
 ** @param string The string to check.
 ** @return True if the string matches the pattern, false otherwise.
*/
bool regex_match(const char* pattern, const char* string);

/**
** @brief Appends the contents of one string to another.
**
** This function appends the characters from the source string `src` to the
** destination string `dest`. The resulting string is terminated with a null
** character.
**
** @param dest Pointer to the destination string.
** @param src Pointer to the source string.
**
** @note The destination string `dest` must have sufficient space to accommodate
** the appended characters from `src`.
**
** @warning The behavior is undefined if `dest` or `src` are null pointers.
**
** @see memmove, strlen
**/
void append_to_string(char* dest, char* src);

// ! TIME functions:

/**
 ** @brief Converts a timestamp to a string.
 **
 ** @param timestamp The timestamp to convert.
 ** @return A string representing the timestamp.
**/
char* timestamp_to_string(time_t timestamp);

/**
 ** @brief Converts a string to a timestamp.
 **
 ** @param str The string to convert.
 ** @return The resulting timestamp.
**/
time_t string_to_timestamp(char* str);
