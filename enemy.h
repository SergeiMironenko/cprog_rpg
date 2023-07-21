#ifndef ENEMY_H_
#define ENEMY_H_

typedef struct Enemy
{
    int hp;
    int max_hp;
    int damage;
    char *name;
    char xp;
} Enemy;

Enemy *init_enemy(int damage, int max_hp, char *name);  // Инициализация противника
void hit_enemy(Enemy *enemy, int damage);  // Получение урона противником
void enemy_info(Enemy *enemy);  // Вывод информации о противнике

#endif  // ENEMY_H_
