#include <stdio.h>
#include <stdlib.h>

#include "player.h"

// Инициализация игрока
Player *init_player(char damage, char max_hp, char magic)
{
    Player *player = (Player *)malloc(sizeof(Player));
    player->hp = max_hp;
    player->max_hp = max_hp;
    player->damage = damage;
    player->magic = magic;
    player->cursed_damage = damage + 5;
    player->cursed_magic = magic + 5;
    
    // Инвентарь
    player->heal = 3;
    player->torch = 0;
    player->cursed_sword = 0;
    player->cursed_ring = 0;
    player->key = 0;
    player->ring = 3;
    return player;
}

// Получение урона игроком
void hit_player(Player *player, char damage)
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
