#include <stdio.h>
#include <stdlib.h>

#include "enemy.h"

// Инициализация противника
Enemy *init_enemy(int damage, int max_hp, char *name)
{
    Enemy *enemy = (Enemy *)malloc(sizeof(Enemy));
    enemy->damage = damage;
    enemy->hp = max_hp;
    enemy->max_hp = max_hp;
    enemy->name = name;
    return enemy;
}

// Получение урона противником
void hit_enemy(Enemy *enemy, int damage)
{
    enemy->hp -= damage;
}

// Вывод информации о противнике
void enemy_info(Enemy *enemy)
{
    printf("--------------------------\n");
    printf("| %-28s|\n", enemy->name);
    printf("| Очки здоровья: %2d / %2d |\n", enemy->hp, enemy->max_hp);
    printf("| Урон: %2d               |\n", enemy->damage);
    printf("--------------------------\n");
}
