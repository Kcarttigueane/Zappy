/*
** EPITECH PROJECT, 2023
** gui
** File description:
** utils
*/

#include "../../include/display.hpp"

int getNumDigits(int number) {
    std::string numberString = std::to_string(number);
    return numberString.length();
}

std::string getIntFormatedString(int nb, int spaces)
{
    int nb_size = getNumDigits(nb);

    std::string numberFormat = std::to_string(nb);
    for (int i = 0; i < (spaces + 1) - nb_size; i++)
        numberFormat += " ";
    return numberFormat;
}