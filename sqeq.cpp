#include <stdio.h>
#include <math.h>




void input_abc_coef (double result[]);
// получаем коэффициенты и проверяем внеслись ли значения в переменные

void print_arr_double(double result[], int len, char name);
// выводит массив double подряд

void print_sqeq_roots(double result[], int len, char name);
// выводит корни уравнения

void sq_eq_solve(double coef[], double result[]);
// решает уравнение получая массив с коэффициентами и массив для результата

void uncorrect_input(double *coef);
// Вывод ошибки и очистка ввода




int main()
{
    double abc[3] = {0};
    input_abc_coef(abc); // input a,b,c - получаем массив аргументов
    double x1_x2[2] = {0};
            // print_arr_double(abc, 3, 'c');
            // print_arr_double(x1_x2, 2, 'x');

    // func (a, b, c, &x1, &x2) - при необходимости получаем данные из массива
    sq_eq_solve(abc, x1_x2);

    // func (b, c, %x1) - перенаправляем если а = 0
    print_sqeq_roots(x1_x2, 2, 'x'); // output result - выводим результат в нужном виде (a, b , c, x1, x2)
}




void input_abc_coef (double result[])
{
    char coef[4] = "abc";
    printf("Введите коэффициенты квадратного уравнения: \n");
    for (int i = 0; i < 3; i++)
    {
    printf("%c = ", coef[i]);

    while (scanf("%lf", &(result[i]) ) != 1)
        uncorrect_input(&(result[i]));
    }
}


void print_arr_double(double result[], int len, char name)
{
    for (int i = 0; i < len; i++)
    {
    printf("%c%d = %lf\n", name , i, result[i]);
    }
}


void sq_eq_solve(double coef[], double result[])
{

    enum {a, b, c};
    enum {x1, x2};
    double discriminant = coef[b]*coef[b] - 4*coef[a]*coef[c];
    if (discriminant < 0)
    {
        printf("Discriminant < 0, roots not defined\n");
        result[x1] = result[x2] = NULL;
        return;
    }
    double sqrt_disc = sqrt(discriminant);
    result[x1] = ((-coef[b]) + sqrt_disc) / (2 * coef[a]);
    result[x2] = ((-coef[b]) - sqrt_disc) / (2 * coef[a]);
}


void print_sqeq_roots(double result[], int len, char name)
{
    enum {x1, x2};

    if (result[x1] == result[x2])
    {
        printf("Единственный корень: %lf\n", result[x1]);
        return;
    }
    else
    {
    printf("Два корня: \n");
    print_arr_double(result, len, name);
    }
}


void uncorrect_input(double *coef)
{
    int c = 0;
    while (((c = getchar()) != EOF) && (c != '\n'));
    printf("\nОшибка ввода. Введенные символы не являются числом \nили число больше допустимого значения.\n");
    printf("Введите коэффициент заново: ");
}
