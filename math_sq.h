#ifndef _MATH
#define _MATH

#include "sqeq.h"

struct Point
{
    double x;
    double y;
};


// проверяет является ли число корнем уравнения с заданными коэффициентами
bool CheckRoots(Coefficient *coef, Roots *roots);

// вычисляет значение уравнения в точке x
double FindFuncValue(Coefficient *coef, double x);

// находит корни многочлена 2 степени
int StandardSqEqSolve(Coefficient *coef, Roots *result);

//выводит корни и их количество
void PrintRoots(Roots *);

// приравнивает два числа с точностью eps
int Equal(double a, double b);

// выводит корни уравнения
void PrintSqEqRoots(Roots *result);

// решает уравнение получая массив с коэффициентами и массив для результата
int SqEqSolve(Coefficient *coef, Roots *x1_x2);

// решает уравнение
int LinEqSolve(Coefficient *coef, Roots *x1_x2);

// вычисляет расстояние между точками
double Distance(Point a, Point b);

#endif
