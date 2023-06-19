/*
** EPITECH PROJECT, 2022
** server
** File description:
** egg_linked_list.c
*/

#include "server.h"

egg_t* random_select_egg(team_t* team)
{
    egg_t *e, *selected = NULL;
    int count = 0;

    LIST_FOREACH(e, &team->egg_list, entries)
    {
        count++;
    }

    if (count > 0) {
        int random_index = rand() % count;

        int i = 0;
        LIST_FOREACH(e, &team->egg_list, entries)
        {
            if (i == random_index) {
                selected = e;
                break;
            }
            i++;
        }
    }

    return selected;
}

int is_egg_list_empty(team_t* team)
{
    return LIST_EMPTY(&team->egg_list);
}

egg_t* create_and_add_egg(team_t* team, coord_t pos)
{
    egg_t* e = (egg_t*)calloc(1, sizeof(egg_t));

    if (!e)
        return NULL;

    e->id = rand();
    e->pos = pos;

    LIST_INSERT_HEAD(&team->egg_list, e, entries);

    return e;
}

void free_list(team_t* team)
{
    egg_t *e, *temp;

    LIST_FOREACH_SAFE(e, &team->egg_list, entries, temp)
    {
        LIST_REMOVE(e, entries);
        free(e);
    }
}

void print_egg_list(team_t* team)
{
    egg_t* e;

    LIST_FOREACH(e, &team->egg_list, entries)
    {
        printf("ID: %ld Pos: (%i, %i)\n", e->id, e->pos.x, e->pos.y);
    }
}

egg_t* find_egg_by_id(team_t* team, size_t id)
{
    egg_t* e;

    LIST_FOREACH(e, &team->egg_list, entries)
    {
        if (e->id == id) {
            return e;
        }
    }

    return NULL;
}

void remove_egg_by_id(team_t* team, size_t id)
{
    egg_t *e, *temp;

    LIST_FOREACH_SAFE(e, &team->egg_list, entries, temp)
    {
        if (e->id == id) {
            LIST_REMOVE(e, entries);
            free(e);
            return;
        }
    }

    printf("Egg with id: %lu not found.\n", id);
}
