#include <stdio.h>

#include "functions.h"

// Очистка потока ввода
void clear_stdin(char c)
{
    while (c != '\n') c = getchar();
}

// Проверка ввода
int validate_input(int choice_max)
{
    int choice = 0;
    char c = '\n';
    // clear_stdin(c);
    scanf("%d%c", &choice, &c);
    if (c == '\n' && choice && choice >= 1 && choice <= choice_max) return choice;
    // printf("Неверный ввод, попробуйте снова");
    // if (c == 'q') break;
    return 0;
}
