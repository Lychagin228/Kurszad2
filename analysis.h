/**
 * analysis.h - Заголовочный файл для программы анализа кусочной функции
 * Функции для анализа функции f(x)
 *
 * f(x) = {
 *   arctan(2x),         x < -2
 *   (e^x - x - 1)/x^2, -2 <= x < 0
 *   sqrt(x^2 + 4),      x >= 0
 * }
 */

#ifndef ANALYSIS_H
#define ANALYSIS_H

// Глобальная переменная для точности
extern double global_eps;

/**
 * Вычисление значения кусочной функции f(x)
 * @param x аргумент функции
 * @return значение функции f(x) в точке x
 */
double f(double x);

/**
 * Вывод главного меню программы
 * @return номер выбранного пункта меню
 */
int menu();

/**
 * Вывод таблицы значений функции на интервале на экран
 * @param start начало интервала
 * @param end конец интервала
 * @param step шаг табуляции
 * @return 0 в случае успешного выполнения
 */
int tablica(double start, double end, double step);

/**
 * Вывод таблицы значений функции в файл
 * @param start начало интервала
 * @param end конец интервала
 * @param step шаг табуляции
 * @param filename имя файла для записи
 * @return 1 в случае успеха, 0 в случае ошибки
 */
int tablica_to_file(double start, double end, double step, const char* filename);

/**
 * Вывод таблицы значений функции и на экран, и в файл
 * @param start начало интервала
 * @param end конец интервала
 * @param step шаг табуляции
 * @param filename имя файла для записи
 * @return 1 в случае успеха, 0 в случае ошибки
 */
int tablica_and_file(double start, double end, double step, const char* filename);

/**
 * Вычисление интеграла с заданным количеством разбиений
 * @param a нижний предел интегрирования
 * @param b верхний предел интегрирования
 * @param n количество разбиений
 * @return приближенное значение интеграла
 */
double integral_with_n(double a, double b, int n);

/**
 * Вычисление интеграла с использованием глобальной точности
 * @param a нижний предел интегрирования
 * @param b верхний предел интегрирования
 * @return приближенное значение интеграла
 */
double integral_with_eps(double a, double b);

/**
 * Запись результата интеграла в файл
 * @param a нижний предел интегрирования
 * @param b верхний предел интегрирования
 * @param filename имя файла для записи
 * @return 1 в случае успеха, 0 в случае ошибки
 */
int integral_to_file(double a, double b, const char* filename);

/**
 * Поиск аргумента x, при котором значение функции приближенно равно заданному y
 * @param y целевое значение функции
 * @param eps допустимая абсолютная погрешность
 * @param start начало интервала поиска
 * @param end конец интервала поиска
 * @param step шаг поиска
 * @return найденное значение x или 10000.0 если не найдено
 */
double poisk_x(double y, double eps, double start, double end, double step);

/**
 * Запись результата поиска в файл
 * @param y целевое значение функции
 * @param eps допустимая абсолютная погрешность
 * @param start начало интервала поиска
 * @param end конец интервала поиска
 * @param step шаг поиска
 * @param filename имя файла для записи
 * @return 1 в случае успеха, 0 в случае ошибки
 */
int poisk_x_to_file(double y, double eps, double start, double end, double step, const char* filename);

/**
 * Вычисление производной функции в точке с использованием глобальной точности
 * @param x точка, в которой вычисляется производная
 * @return приближенное значение производной
 */
double proizvodnaya(double x);

#endif // ANALYSIS_H




