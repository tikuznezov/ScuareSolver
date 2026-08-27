#ifndef _SQEQ
#define _SQEQ

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>
#include <sys/ioctl.h>


//! Задает красный цвет текста
#define RED printf("\x1b[31m");
//! Задает желтый цвет текста
#define YELLOW printf("\x1b[33m");
//! Задает зеленый цвет текста
#define GREEN printf("\x1b[32m");
//! Задает белый цвет текста на черном фоне (по умолчанию)
#define DEF_COL printf("\x1b[0m");
//! Задает черный текст на белом фоне
#define BLACKonWHITE printf("\x1b[30;47m");

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

//! Константа, ограничивающая максимальное количество уравнений в файле. Нужна, чтобы цикл while не был бесконечным
const int MAX_NUM_OF_EQ_FROM_FILE = 100000;
//! Константа, ограничивающая максимальное количество уравнений в файле для тестирования. Нужна, чтобы цикл while не был бесконечным
const int MAX_NUM_OF_TESTS_FROM_FILE = 100000;


/**
* @brief Структура, содержащая в себе корни уравнения и их количество.
* @param x1 - первый корень уравнения (наименьший или единственный)
* @param x2 - второй корень уравнения (наибольший или NAN)
*/
struct Roots
{
    double x1 = NAN;
    double x2 = NAN;
    int count_roots = 0;
};

/**
* @brief Структура, содержащая в себе коэффициенты уравнения
* @param a - старший коэффициент
* @param b - средний коэффициент
* @param b - свободный коэффициент
*/
struct Coefficient
{
    double a = 0.f;
    double b = 0.f;
    double c = 0.f;
};

//! Виды возможных ошибок
enum TYPE_OF_ERROR
{
    NO_ERROR,
    DIVISION_BY_ZERO,
    INCORRECT_INPUT,
    USER_IS_BYAKA
};

//! Варианты количества действительных корней уравнения
enum NUMBERS_OF_SOLUTION
{
    INF_SOLUTIONS = -1,
    NO_SOLUTIONS = 0,
    ONE_SOLUTION = 1,
    TWO_SOLUTIONS = 2
};

//! структура для ввода, говорит о том, нужно ли продолжать считывать значения коэффициентов
enum CONTINUE_TAKEING_COEFS
{
    BREAK = 17, // 17 - произвольный код ошибке, пока в разработке
    CONTINUE = 1
};


/**
 * @brief Получает коэффициенты и проверяем внеслись ли значения в переменные
 *
 * @param coef - структура с коэффициентами функции
 * @return int - возвращает код ошибки CONTINUE_TAKEING_COEFS
 */
int InputAbcCoef(Coefficient *coef);

/**
 * @brief Вывод ошибки и очистка ввода
 *
 * @param repeat_count - счетчик количества считанных ответов за время работы функции
 * @return int - возвращает код ошибки CONTINUE_TAKEING_COEFS
 */
int NotCorrectInput(int repeat_count);

/**
 * @brief Считывает код ошибки и выводит результат. Если код равен 0, выводит ответ.
 *
 * @param error - код текущей ошибки, выводит по нему информацию
 * @param x1_x2 - структура с корнями уравнения и их количеством, идет на отображение пользователю
 */
void Output(int error, Roots *x1_x2);

/**
 * @brief Выводит в терминал приветствие
 */
void HelloSq();

/**
 * @brief Выводит сообщение с вопросом, хочет ли пользователь решить уравнение
 */
void WantSq();

/**
 * @brief Очищает терминал
 */
void ClearTerm();

/**
 * @brief Принимает выбор пользователя, если нужно, решает уравнение. Считывает bool, если 1, выводит в терминал график функции
 *
 * @param is_print_graph - отвечает за печать графика функции, если true, выводит график в терминал
 * @return int - в разработке, должен возвращать код ошибки при диагностике
 */
int UserChoice(bool is_print_graph);

/**
 * @brief Принимает данные из ввода, возвращает решение о необходимости решать уравнение: YES, NO, ERROR
 *
 * @return int - возвращает enum USER_CHOICE
 */
int TakeMassage();

/**
 * @brief Упрашивает решить уравнение, вызывает take_massage
 *
 * @return int - возвращает enum USER_CHOICE
 */
int Please();

/**
 * @brief Спрашивает, нужно ли решать следующее уравнение
 *
 * @return int - возвращает enum YES NO ERROR
 */
int WantAnotherOne();

/**
 * @brief Выводит корни и количество решений
 *
 */
void PrintCoefs(Coefficient *coef);

/**
 * @brief Решает уравнения из файла
 *
 * @return int
 */
int SolveFromFile(FILE *);

/**
 * @brief Проверяет параметры при запуске программы: запускает различные сценарии исполнения программы
 *
 * @return int возвращает 1 при ошибке, 0 при штатном исполнении
 */
int CheckRunParameters(int, char *);

/**
 * @brief Выводит пользователю варианты запуска программы
 */
void WhatCanDoThisProgram();

/**
 * @brief Анализирует параметры main
 *
 * @param argc - параметр argc командной строки
 * @param argv - параметр argv командной строки
 */
void CheckRunParameters(int argc, char** argv);

// Анализ параметров main

/**
 * @brief Запуск решения из файла, опирается на параметры main
 *
 * @param argc - флаги запуска main
 * @param argv - флаги запуска main
 * @param i - указатель на текущий номер параметра
 * @return int
 */
int RP_SolveFromFile(int argc, char** argv, int *i);

/**
 * @brief Запуск тестов из файла, опирается на параметры main
 *
 * @param argc - флаги запуска main
 * @param argv - флаги запуска main
 * @param i - указатель на текущий номер параметра
 * @return int
 */
int RP_TestsFromFile(int, char**, int *);

/**
 * @brief Запуск теста с набором случайных коэффициентов, опирается на параметры main
 *
 * @param argc - флаги запуска main
 * @param argv - флаги запуска main
 * @param i - указатель на текущий номер параметра
 * @return int
 */
int RP_StressTest(int, char**, int *); ///< Запуск теста со случайными коэффициентами, опирается на параметры main

/**
 * @brief Выводит график функции в терминал
 *
 * @param Func - функция, которую необходимо вывести
 * @param coef - коэффициенты этой функции
 */
int PrintFunc(double Func(Coefficient *, double), Coefficient *coef);

/**
 * @brief Вызывает функцию PrintFunc, после ее выполнение спрашивает у пользователя,
 *        нужно ли изменить масштаб. Если нужно, просит его ввести новый масштаб и
 *        заново вызывает PrintFunc с учетом пользовательского масштаба
 *
 * @param Func
 * @param coef
 */
void ChangingScalePrintFunc(double Func(Coefficient *, double), Coefficient *coef);


#endif
