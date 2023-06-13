/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** common.h
*/

#ifndef COMMON_H_
#define COMMON_H_

#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <time.h>
#include <unistd.h>
#include <uuid/uuid.h>

#define MAX_NB_COMMANDS 10
#define MAX_COMMANDS_LENGTH 256
#define MAX_BUFFER 1024
#define MAX_NB_RESOURCES 7
#define MAX_NB_PLAYERS 6
#define MAX_COMMANDS_PER_CLIENT 10
#define MAX_W_BUFFER_LENGTH 100000
#define MAX_R_BUFFER_LENGTH 100000

#ifndef LIST_FOREACH_SAFE
#    define LIST_FOREACH_SAFE(var, head, field, tvar) \
        for ((var) = LIST_FIRST((head));              \
             (var) && ((tvar) = LIST_NEXT((var), field), 1); (var) = (tvar))
#endif /* !LIST_FOREACH_SAFE */

#endif /* !COMMON_H_ */
