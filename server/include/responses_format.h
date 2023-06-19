/*
** EPITECH PROJECT, 2022
** server
** File description:
** responses_format.h
*/

#ifndef RESPONSES_FORMAT_H_
#define RESPONSES_FORMAT_H_

// ! GRAPHICAL COMMANDS:

#define MSZ_FORMAT "msz %zu %zu\n"
#define BCT_FORMAT "bct %i %i %lu %lu %lu %lu %lu %lu %lu\n"
#define TNA_FORMAT "tna %s\n"
#define PPO_FORMAT "ppo %lu %i %i %d\n"
#define PLV_FORMAT "plv %lu %lu\n"
#define PNW_FORMAT "pnw %ld %d %d %i %ld %s\n"
#define PIN_FORMAT "pin %lu %i %i %lu %lu %lu %lu %lu %lu %lu\n"
#define PEX_FORMAT "pex %d\n"
#define PBC_FORMAT "pbc %d %s\n"
#define PIC_FORMAT "pic %d %d %d %d %d ...\n"
#define PIE_FORMAT "pie %d %d %d\n"
#define PFK_FORMAT "pfk %ld\n"
#define PDR_FORMAT "pdr %ld %d\n"
#define PGT_FORMAT "pgt %ld %d\n"
#define PDI_FORMAT "pdi %ld\n"
#define ENW_FORMAT "enw %ld %ld %d %d\n"
#define EBO_FORMAT "ebo %ld\n"
#define EDI_FORMAT "edi %d\n"
#define SGT_FORMAT "sgt %d\n"
#define SST_FORMAT "sst %d\n"
#define SEG_FORMAT "seg %s\n"
#define SMG_FORMAT "smg %s\n"
#define SUC_FORMAT "suc\n"
#define SBP_FORMAT "sbp\n"

// ! PLAYER COMMANDS:

#define OK_FORMAT "ok\n"
#define KO_FORMAT "ko\n"
#define DEAD_FORMAT "dead\n"
#define CURRENT_LEVEL_FORMAT "Current level: %d\n"
#define ELEVATION_UNDERWAY_FORMAT "Elevation underway\n"
#define INVENTORY_FORMAT                                                 \
    "[ food %ld, linemate %ld, deraumere %ld, sibur %ld, mendiane %ld, " \
    "phiras %ld, "                                                       \
    "thystame %ld ]\n"
#define VIEW_FORMAT "[ %s, %s, %s ]\n"  // Example for a level 1 view
#define CONNECT_NBR_FORMAT "%d\n"

#endif /* !RESPONSES_FORMAT_H_ */
