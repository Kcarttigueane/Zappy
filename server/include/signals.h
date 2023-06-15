/*
** EPITECH PROJECT, 2022
** B-YEP-400-LYN-4-1-zappy-kevin.carttigueane
** File description:
** signals.h
*/

#pragma once

/**
 ** @brief Handles the SIGINT signal.
 **
 ** When the process receives a SIGINT signal (Ctrl+C),
 ** this function gets called to handle it.
 ** It stops the server by setting the 'stop_server' flag to true.
 **
 ** @param sig The signal number. parameter not used and its value is ignored.
**/
void sigint_handler(__attribute_maybe_unused__ int sig);

/**
** @brief Sets up a signal handler for SIGINT.
**
** This function uses sigaction to associate the SIGINT signal
** with the sigint_handler function. If the association fails,
** it calls handle_error and returns FAILURE.
**
** @return SUCCESS if the signal handler successful, and FAILURE otherwise.
**/
int setup_signal_handler(void);
