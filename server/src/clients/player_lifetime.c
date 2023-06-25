/*
** EPITECH PROJECT, 2022
** server
** File description:
** player_lifetime.c
*/

#include "server.h"

void update_player_life(player_t* player, int freq)
{
    int life_unit_duration = (double)126.0 / freq;
    clock_t current_time = clock();
    double elapsed_time = (double)(current_time - player->start_time) / CLOCKS_PER_SEC;

    if (elapsed_time >= life_unit_duration) {
        printf("Player %ld lost 1 life unit\n", player->id);
        player->life_units -= 1;
        player->start_time = current_time;
    }
}

void player_lifetime(server_data_t* s)
{
    client_t *client, *temp;
    char response[1024] = {0};

    LIST_FOREACH_SAFE(client, &s->game.client_list, entries, temp)
    {
        if (client->player && client->player->state == PLAYER && client->player->state == PLAYER) {
            update_player_life(client->player, s->game.freq);

            if (client->player->inventory[FOOD] > 0) {
                client->player->inventory[FOOD] -= 1;
                client->player->life_units += 1;
                printf("Player %ld ate 1 food\n", client->player->id);
            }

            if (client->player->life_units <= 0) {
                sprintf(response, PDI_FORMAT, client->player->id);
                append_to_gui_write_buffer(&s->game, response);
                printf("Player %ld died\n", client->player->id);
                memset(client->write_buf, 0, sizeof(client->write_buf));
            }
        }
    }
}
