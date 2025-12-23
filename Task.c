#include <stdio.h>
#include <locale.h>
#include "analysis.h"


// Главная функция
int main() {
    setlocale(LC_CTYPE, "RUS");
    int user_choice; // Переименовали для ясности
    double x, y, eps, a, b, step;
    int n;
    double found_x;
    int search_result;

    printf("\n");
    printf("****************************************\n");
    printf("*          АНАЛИЗ ФУНКЦИИ             *\n");
    printf("****************************************\n");
    printf("* f(x) = {                            *\n");
    printf("*   arctan(2x),         x < -2        *\n");
    printf("*   (e^x - x - 1)/x^2, -2 <= x < 0    *\n");
    printf("*   sqrt(x^2 + 4),      x >= 0        *\n");
    printf("****************************************\n");

    do {
        // Получаем выбор пользователя из меню
        user_choice = menu();
        
        // Обрабатываем выбор
        switch (user_choice) {
        case 1:
            printf("Введите x: ");
            scanf("%lf", &x);
            printf("f(%.3lf) = %.3lf\n", x, tochka(x));
            break;

        case 2:
            printf("Введите начало интервала: ");
            scanf("%lf", &a);
            printf("Введите конец интервала: ");
            scanf("%lf", &b);
            printf("Введите шаг: ");
            scanf("%lf", &step);
            tablica(a, b, step);
            break;

        case 3:
            printf("Введите начало интервала: ");
            scanf("%lf", &a);
            printf("Введите конец интервала: ");
            scanf("%lf", &b);
            if (a > b) {
                printf("Ошибка: начало интервала должно быть меньше конца!\n");
                break;
            }
            printf("Введите число для нахождения точности (целое число > 0): ");
            scanf("%d", &n);
            if (n <= 0) {
                printf("Ошибка: такое число должно быть положительным!\n");
                break;
            }
            printf("Интеграл = %.6lf\n", integral(a, b, n));
            break;

        case 4:
            printf("Введите y: ");
            scanf("%lf", &y);
            printf("Введите точность: ");
            scanf("%lf", &eps);
            if (eps <= 0) {
                printf("Ошибка: точность должна быть положительной!\n");
                break;
            }
            printf("Поиск x для y = %.3lf\n", y);
            
            search_result = poisk_x(y, eps, &found_x);
            if (search_result == 1) {
                printf("Результат поиска: x = %.4lf, f(x) = %.6lf\n", found_x, f(found_x));
            } else {
                printf("Решение не найдено на интервале [-10, 10] с заданной точностью.\n");
            }
            break;

        case 5:
            printf("Введите x: ");
            scanf("%lf", &x);
            printf("f'(%.3lf) = %.6lf\n", x, proizvodnaya(x));
            break;

        case 6:
            printf("Выход из программы.\n");
            break;

        default:
            printf("Ошибка: неверный выбор операции!\n");
            break;
        }

        // Если не выход, спрашиваем о продолжении
        if (user_choice != 6) {
            printf("\nВернуться в меню? (1 - да, 0 - нет): ");
            int continue_flag;
            scanf("%d", &continue_flag);
            if (continue_flag == 0) {
                user_choice = 6; // Имитируем выбор "Выход"
                printf("Завершение работы программы.\n");
            }
        }

    } while (user_choice != 6);

    return 0;
}
