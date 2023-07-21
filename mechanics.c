#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "enemy.h"
#include "mechanics.h"
#include "functions.h"

// Схватка
int fight(Player *player, Enemy *enemy)
{
    char choice = 0;
    char choice_max = 5;
    char player_first_hit = rand() % 2;
    while (1)
    {
        player_info(player);
        enemy_info(enemy);
        if (player_first_hit)
        {
            printf("Нанести удар мечом (1)\n");

            if (player->ring >= 3) printf("Нанести урон магией (2)\n");
            else printf("Нужно подождать, пока зарядится кольцо. Нанести удар мечом (2)\n");

            if (player->heal) printf("Полечиться (3)\n");
            else printf("Нечем восполнить здоровье (3)\n");

            if (player->cursed_sword) printf("Нанести урон проклятым мечом (4)\n");

            if (player->cursed_ring) printf("Использовать проклятое кольцо (5)\n");

            choice = validate_input(choice_max);
            switch(choice)
            {
                case 1:
                    hit_enemy(enemy, player->damage);
                    printf("!!! Игрок наносит %d урона.\n", player->damage);
                    break;
                case 2:
                    if (player->ring >= 3)
                    {
                        hit_enemy(enemy, player->magic);
                        printf("!!! Игрок наносит %d урона магией.\n", player->magic);
                        player->ring = 0;
                    }
                    else
                    {
                        hit_enemy(enemy, player->damage);
                        printf("!!! Игрок наносит %d урона.\n", player->damage);
                    }
                    break;
                case 3:
                    player->hp = player->max_hp;
                    player->heal--;
                    break;
                case 4:
                    if (player->cursed_sword)
                    {
                        char r = rand() % 5;
                        if (r)
                        {
                            hit_enemy(enemy, 2 * player->damage);
                            printf("!!! Игрок наносит повышенный урон (%d).\n", 2 * player->damage);
                        }
                        else
                        {
                            player->cursed_sword = 0;
                            printf("!!! Проклятый меч сломан.\n");
                        }
                    }
                    break;
                case 5:
                    if (player->cursed_ring)
                    {
                        char r = rand() % 2;
                        if (r)
                        {
                            hit_enemy(enemy, player->magic + 5);
                            printf("!!! Игрок наносит повышенный урон магией (%d).\n", 2 * player->magic + 5);
                        }
                        else
                        {
                            hit_player(player, 2);
                            printf("!!! Проклятое кольцо наносит урон игроку.\n");
                        }
                    }
                    break;
            }
            if (enemy->hp <= 0) return 1;
        }
        else
        {
            player_first_hit = 1;
        }
        hit_player(player, enemy->damage);
        printf("!!! Противник наносит %d урона.\n", enemy->damage);
        if (player->hp <= 0) return 0;
    }
}
