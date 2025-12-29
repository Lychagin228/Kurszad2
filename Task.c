#include <stdio.h>
#include <locale.h>
#include "analysis.h"

// Главная функция
int main() {
    setlocale(LC_CTYPE, "RUS");
    int user_choice;
    double x, y, a, b, step;
    int n;
    double found_x;
    char filename[256];
    int output_choice;

    printf("\n");
    printf("****************************************\n");
    printf("*          АНАЛИЗ ФУНКЦИИ             *\n");
    printf("****************************************\n");
    printf("* f(x) = {                            *\n");
    printf("*   arctan(2x),         x < -2        *\n");
    printf("*   (e^x - x - 1)/x^2, -2 <= x < 0    *\n");
    printf("*   sqrt(x^2 + 4),      x >= 0        *\n");
    printf("****************************************\n");
    printf("* Текущая точность: %.6lf            *\n", global_eps);
    printf("****************************************\n");

    do {
        user_choice = menu();

        switch (user_choice) {
        case 1:
            printf("Введите x: ");
            scanf("%lf", &x);
            printf("f(%.3lf) = %.6lf\n", x, f(x));
            break;

        case 2:
            printf("Введите начало интервала: ");
            scanf("%lf", &a);
            printf("Введите конец интервала: ");
            scanf("%lf", &b);
            printf("Введите шаг: ");
            scanf("%lf", &step);
            
            printf("Вывести результат:\n");
            printf("1 - на экран\n");
            printf("2 - в файл\n");
            printf("3 - и на экран, и в файл\n");
            printf("Ваш выбор: ");
            scanf("%d", &output_choice);
            
            if (output_choice == 1) {
                tablica(a, b, step);
            } else if (output_choice == 2) {
                printf("Введите имя файла: ");
                scanf("%s", filename);
                tablica_to_file(a, b, step, filename);
            } else if (output_choice == 3) {
                printf("Введите имя файла: ");
                scanf("%s", filename);
                tablica_and_file(a, b, step, filename);
            } else {
                printf("Неверный выбор, результат выведен на экран\n");
                tablica(a, b, step);
            }
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
            
            printf("Выберите метод:\n");
            printf("1 - задать количество разбиений\n");
            printf("2 - использовать глобальную точность\n");
            printf("Ваш выбор: ");
            scanf("%d", &output_choice);
            
            if (output_choice == 1) {
                printf("Введите количество разбиений (целое число > 0): ");
                scanf("%d", &n);
                if (n <= 0) {
                    printf("Ошибка: количество разбиений должно быть положительным!\n");
                    break;
                }
                printf("Результат:\n");
                printf("Интеграл от %.3lf до %.3lf = %.6lf\n", a, b, integral_with_n(a, b, n));
            } else {
                printf("Используется глобальная точность: %.6lf\n", global_eps);
                printf("Результат:\n");
                printf("Интеграл от %.3lf до %.3lf = %.6lf\n", a, b, integral_with_eps(a, b));
            }
            
            printf("\nСохранить результат в файл? (1 - да, 0 - нет): ");
            scanf("%d", &output_choice);
            if (output_choice == 1) {
                printf("Введите имя файла: ");
                scanf("%s", filename);
                integral_to_file(a, b, filename);
            }
            break;

        case 4:
            printf("Введите y: ");
            scanf("%lf", &y);
            printf("Введите начало интервала поиска: ");
            scanf("%lf", &a);
            printf("Введите конец интервала поиска: ");
            scanf("%lf", &b);
            printf("Введите шаг поиска (рекомендуется 0.001): ");
            scanf("%lf", &step);
            printf("Используется глобальная точность: %.6lf\n", global_eps);
            
            found_x = poisk_x(y, global_eps, a, b, step);
            
            printf("Результат поиска: ");
            if (found_x != 10000.0) {
                printf("x = %.6lf, f(x) = %.6lf\n", found_x, f(found_x));
            } else {
                printf("Решение не найдено на интервале [%.1lf, %.1lf] с заданной точностью.\n", a, b);
            }
            
            printf("\nСохранить результат в файл? (1 - да, 0 - нет): ");
            scanf("%d", &output_choice);
            if (output_choice == 1) {
                printf("Введите имя файла: ");
                scanf("%s", filename);
                poisk_x_to_file(y, global_eps, a, b, step, filename);
            }
            break;

        case 5:
            printf("Введите x: ");
            scanf("%lf", &x);
            printf("Используется глобальная точность: %.6lf\n", global_eps);
            printf("f'(%.3lf) = %.6lf\n", x, proizvodnaya(x));
            break;

        case 6:
            printf("Текущее значение точности: %.6lf\n", global_eps);
            printf("Введите новое значение точности: ");
            scanf("%lf", &global_eps);
            if (global_eps <= 0) {
                printf("Ошибка: точность должна быть положительной! Установлено значение 0.001\n");
                global_eps = 0.001;
            } else {
                printf("Точность успешно изменена на: %.6lf\n", global_eps);
            }
            break;

        case 7:
            printf("Выход из программы.\n");
            break;

        default:
            printf("Ошибка: неверный выбор операции!\n");
            break;
        }

        if (user_choice != 7) {
            printf("\nВернуться в меню? (1 - да, 0 - нет): ");
            int continue_flag;
            scanf("%d", &continue_flag);
            if (continue_flag == 0) {
                user_choice = 7;
                printf("Завершение работы программы.\n");
            }
        }

    } while (user_choice != 7);

    return 0;
}

