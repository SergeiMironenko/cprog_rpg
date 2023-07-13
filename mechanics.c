#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "enemy.h"
#include "mechanics.h"

// Схватка
int fight(Player *player)
{
    Enemy *enemy = (Enemy *)malloc(sizeof(Enemy));
    enemy->hp = 10;
    enemy->damage = 3;

    char turn = 1;
    while (1)
    {
        if (turn)
        {
            enemy->hp -= player->damage;
            printf("player damaged %d\n", player->damage);
        }
        else
        {
            hit_player(player, enemy->damage);
            printf("player hurt %d\n", enemy->damage);

        }

        if (player->hp <= 0) return 1;
        if (enemy->hp <= 0) return 0;

        turn = !turn;
    }
}
