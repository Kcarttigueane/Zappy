/*
** EPITECH PROJECT, 2022
** Repositery-ZAPPY
** File description:
** map.h
*/

#ifndef MAP_H_
    #define MAP_H_

    #define OOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY SIBUR_DENSITY
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05

    #define CALC_TOTAL_RESOURCES(total_tiles)                                 \
        {                                                                     \
            (total_tiles) * OOD_DENSITY, (total_tiles)*LINEMATE_DENSITY,      \
                (total_tiles)*DERAUMERE_DENSITY, (total_tiles)*SIBUR_DENSITY, \
                (total_tiles)*MENDIANE_DENSITY, (total_tiles)*PHIRAS_DENSITY, \
                (total_tiles)*THYSTAME_DENSITY                                \
        }

    #define TIMER_INTERVAL 20

    #include "server.h"

    typedef struct tile_s {
        size_t quantity[MAX_NB_RESOURCES];
    } tile_t;

// ! MAP FUNCTIONS !

/**
 * \brief Adds the quantities of resources on a given map tile to the current resources array.
 *
 * \param[in,out] map 2D array representing the game map.
 * \param[in,out] current_resources Array to store the current amount of each resource.
 * \param[in] i X-coordinate of the map tile.
 * \param[in] j Y-coordinate of the map tile.
 */
void add_current_resources(tile_t** map, int current_resources[], size_t i, size_t j);

/**
 * \brief Calculates the total number of each resource on the game map.
 *
 * \param[in,out] map 2D array representing the game map.
 * \param[in,out] current_resources Array to store the current amount of each resource.
 * \param[in] height The height of the game map.
 * \param[in] width The width of the game map.
 */
void calculate_current_resources(tile_t** map, int current_resources[], size_t height,
                                        size_t width);

/**
 * \brief Spawns resources on the game map.
 *
 * \param[in,out] game
 * \param[in] total_resources Array representing the total number of each resource.
 * \param[in] height The height of the game map.
 * \param[in] width The width of the game map.
 */
void spawning_resources(game_t *game, int total_resources[], size_t height, size_t width);

/**
 * \brief Initializes a game map of given dimensions.
 *
 * \param[in] width The width of the game map.
 * \param[in] height The height of the game map.
 *
 * \return Pointer to the initialized map.
 */
tile_t** init_map(size_t width, size_t height);

/**
 * \brief Shuffles an array of integers in-place.
 *
 * \param[in,out] array The array to be shuffled.
 * \param[in] n The length of the array.
 */
void shuffle(int* array, size_t n);

/**
 * \brief Frees the memory allocated for a game map.
 *
 * \param[in] map 2D array representing the game map.
 * \param[in] width The width of the game map.
 */
void free_tiles_map(tile_t** map, size_t width);

/**
 * \brief Calculates the total number of each resource on a given map tile and adds them to the total resources array.
 *
 * \param[in] tile A map tile.
 * \param[in,out] totals Array to store the total amount of each resource.
 */
void calculate_resource_totals(tile_t* tile, size_t* totals);

/**
 * \brief Prints the total number of each resource on the game map.
 *
 * \param[in] map 2D array representing the game map.
 * \param[in] height The height of the game map.
 * \param[in] width The width of the game map.
 */
void print_total_resources(tile_t** map, size_t height, size_t width);

// ! DEBUG FUNCTIONS !

/**
 * \brief Prints the locations and quantities of resources on the game map.
 *
 * \param[in] map 2D array representing the game map.
 * \param[in] height The height of the game map.
 * \param[in] width The width of the game map.
 */
void print_resources_location(tile_t** map, size_t height, size_t width);

#endif /* !MAP_H_ */
