#ifndef _MATH
#define _MATH

#include "sqeq.h"

//! Задает точку с координатами x, y
struct Point
{
    double x;
    double y;
};


/**
 * @brief Проверяет является ли число корнем уравнения с заданными коэффициентами
 *
 * @param coef - указатель на структуру с коэффициентами уравнения
 * @param roots - указатель на структуру с корнями
 * @return true - если корни удовлетворяют
 * @return false - если корни не удовлетворяют
 */
bool CheckRoots(Coefficient *coef, Roots *roots);

/**
 * @brief Вычисляет значение уравнения в точке x
 *
 * @param coef - структура с коэффициентами уравнения
 * @param x - число от которого будет рассчитываться значение уравнения
 * @return double - значение функции в точке x
 */
double FindFuncValue(Coefficient *coef, double x);

/**
 * @brief Находит корни многочлена 2 степени
 *
 * @param coef - структура с коэффициентами уравнения
 * @param result - структура, куда запишутся корни уравнения
 * @return int - возвращает 1 если была ошибка, 0 если вычисления прошли штатно
 */
int StandardSqEqSolve(Coefficient *coef, Roots *result);

/**
 * @brief Выводит на экран структуру Roots
 */
void PrintRoots(Roots *);

/**
 * @brief Сравнивает два числа с точностью до EPS
 *
 * @param a - первое число для сравнения
 * @param b - второе число для сравнения
 * @return int - возвращает true если равны, false если неравны
 */
bool Equal(double a, double b);

/**
 * @brief Выводит на экран корни квадратного уравнения и их количество
 *
 * @param result - структура Roots с корнями
 */
void PrintSqEqRoots(Roots *result);

/**
 * @brief Решает уравнение получая структуру с коэффициентами и структуру с корнями, принимающую результат
 *
 * @param coef - указатель на структуру с коэффициентами
 * @param x1_x2 - указатель на структуру с корнями
 * @return int
 */
int SqEqSolve(Coefficient *coef, Roots *x1_x2);

/**
 * @brief Решает линейное уравнение
 *
 * @param coef - структура с коэффициентами
 * @param x1_x2
 */
void LinEqSolve(Coefficient *coef, Roots *x1_x2);

/**
 * @brief Вычисляет расстояние между двумя точками
 *
 * @param a - структура Point с точкой a
 * @param b - структура Point с точкой b
 * @return double - расстояние между точками
 */
double Distance(Point a, Point b);

/**
 * @brief Делает число нечетным, вычитая единицу, если оно четное
 *
 * @param x - число
 * @return int - нечетное число
 */
int ToOdd(int x);

#endif
