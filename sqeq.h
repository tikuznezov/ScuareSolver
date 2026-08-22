#include <stdio.h>
#include <math.h>
#include <assert.h>


// получаем коэффициенты и проверяем внеслись ли значения в переменные
int input_abc_coef(struct coefficient *coef);

// выводит корни уравнения
void print_sqeq_roots(struct roots *result);

// решает уравнение получая массив с коэффициентами и массив для результата
int sq_eq_solve(struct coefficient *coef, struct roots *x1_x2);

// решает уравнение
int lin_eq_solve(struct coefficient *coef, struct roots *x1_x2);

// Вывод ошибки и очистка ввода
void not_correct_input();

// рисует график функции в терминале (пока не готова)
int show_grath(struct coefficient coef, int len_x, int len_y);

// switch и вывод результата
void output(int error, struct roots *x1_x2);

// приравнивает два числа с точностью eps
int equal(double a, double b);

// выводит приветствие
int hello_sq();

// спрашивает, хочешь ли решить уравнение
int want_sq();

// очищает ввод
void clear_term();

// принимает данные из ввода
// если в начале стоит yes/no/da/net (можно заглавными)
// возвращает YES = 1, NO = 2, ERROR = 0
#define SKIP_YES return YES; // замена на yes/da на y/d
#define SKIP_NO  return  NO; // замена на no/net на n/n
int take_massage();

// упрашивает решить уравнение, вызывает take_massage
int please();

// выводит сообщение о некорректном вводе
void not_correct_input();

// спрашивает, нужно ли решать следующее уравнение
int want_another_one();

// корни уравнения
struct roots
{
    double x1 = 0;
    double x2 = 0;
};

// коэффициенты уравнения
struct coefficient
{
    double a = 0.f;
    double b = 0.f;
    double c = 0.f;
};


#define RED printf("\n\x1b[31m");
#define YELLOW printf("\x1b[33m");
#define GREEN printf("\x1b[32m");
#define DEF_COL printf("\x1b[0m");

enum TYPE_OF_ERROR
{
    NO_ERROR                = 0,
    DIVISION_BY_ZERO        = 1,
    DISCRIMINANT_LOWER_ZERO = 2,
    INCORRECT_INPUT         = 3,
    X_IS_ANY_NUMBER         = 4,
    THERES_NO_SOLVES        = 5,
    LIN_EQ                  = 6,
    USER_IS_BYAKA           = 7
};
