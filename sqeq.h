#ifndef sqeq
#define sqeq


#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>


#define RED printf("\x1b[31m");
#define YELLOW printf("\x1b[33m");
#define GREEN printf("\x1b[32m");
#define DEF_COL printf("\x1b[0m");

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

const int MAX_LINE = 100;
const int MAX_NUM_OF_EQ = 10;
const int MAX_NUM_OF_TESTS = 100;


// корни уравнения
struct Roots
{
    double x1 = NAN;
    double x2 = NAN;
    int count_roots = 0;
};

// коэффициенты уравнения
struct Coefficient
{
    double a = 0.f;
    double b = 0.f;
    double c = 0.f;
};


enum TYPE_OF_ERROR
{
    NO_ERROR,
    DIVISION_BY_ZERO,
    INCORRECT_INPUT,
    USER_IS_BYAKA
};

enum NUMBERS_OF_SOLUTION
{
    INF_SOLUTIONS = -1,
    NO_SOLUTIONS = 0,
    ONE_SOLUTION = 1,
    TWO_SOLUTIONS = 2
};


// получаем коэффициенты и проверяем внеслись ли значения в переменные
int InputAbcCoef(Coefficient *coef);

// выводит корни уравнения
void PrintSqEqRoots(Roots *result);

// решает уравнение получая массив с коэффициентами и массив для результата
int SqEqSolve(Coefficient *coef, Roots *x1_x2);

// решает уравнение
int LinEqSolve(Coefficient *coef, Roots *x1_x2);

// Вывод ошибки и очистка ввода
void NotCorrectInput();

// рисует график функции в терминале (пока не готова)
//int show_grath(coefficient coef, int len_x, int len_y);

// switch и вывод результата
void Output(int error, Roots *x1_x2);

// приравнивает два числа с точностью eps
int Equal(double a, double b);

// выводит приветствие
int HelloSq();

// спрашивает, хочешь ли решить уравнение
int WantSq();

// очищает ввод
void ClearTerm();

// принимает выбор пользователя, если нужно, решает уравнение
int UserChoice();

// принимает данные из ввода
// если в начале стоит yes/no/da/net (можно заглавными)
// возвращает YES = 1, NO = 2, ERROR = 0
// #define SKIP_YES return YES; // замена на yes/da на y/d
// #define SKIP_NO  return  NO; // замена на no/net на n/n
int TakeMassage();

// упрашивает решить уравнение, вызывает take_massage
int Please();

// выводит сообщение о некорректном вводе
void NotCorrectInput();

// спрашивает, нужно ли решать следующее уравнение
int WantAnotherOne();

// проводит один тест вычисления корней квадратного уравнения
int RunTestSq(Coefficient coef, Roots x12, int *error);

// Временная вторая версия получения сообщения
int TakeMassage_1();

// выводит корни и количество решений
void PrintCoefs(Coefficient *);

//выводит корни и их количество
void PrintRoots(Roots *);

// Решает уравнения из файла
int SolveFromFile(FILE *);

// проверяет параметры при запуске программы: запускает чтение из файла или диалог с пользователем
int CheckRunParameters(int, char *);

// выводит пользователю варианты запуска программы
void WhatCanDoThisProgram();

// проверяет является ли число корнем уравнения с заданными коэффициентами
bool CheckRoots(Coefficient *coef, Roots *roots);

// вычисляет значение уравнения в точке x
double FindFuncValue(Coefficient *coef, double x);

// находит корни многочлена 2 степени
int StandardSqEqSolve(Coefficient *coef, Roots *result);

// анализирует параметры main
int CheckRunParameters(int, char**);


#endif
