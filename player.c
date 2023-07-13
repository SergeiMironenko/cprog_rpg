#include <stdio.h>
#include <stdlib.h>

#include "player.h"

// Инициализация игрока
Player *init_player(int damage, int max_hp, int luck)
{
    Player *player = (Player *)malloc(sizeof(Player));
    player->damage = damage;
    player->hp = max_hp;
    player->max_hp = max_hp;
    player->luck = luck;
    player->inventory = 0;
    return player;
}

// Получение урона игроком
void hit_player(Player *player, int damage)
{
    player->hp -= damage;
}

// Вывод информации об игроке
void player_info(Player *player)
{
    printf("--------------------------\n");
    printf("|      СТАТУС ИГРОКА     |\n");
    printf("| Очки здоровья: %2d / %2d |\n", player->hp, player->max_hp);
    printf("| Урон: %2d               |\n", player->damage);
    printf("--------------------------\n");
}
