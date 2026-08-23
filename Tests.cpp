#ifndef sqeq
#define sqeq
#include "sqeq.h"
#endif

#define SPEC_TESTS_NUM 3
#define TEST_FAULT 0

struct TestData
{
    Coefficient coef;
    Roots roots;
};

// возвращает 1 если тест не пройден

int RunTestSq(TestData *test_data, int *test_num)
{
    //printf("Коэффициенты: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg\n", test_data->coef.a, test_data->coef.b, test_data->coef.c, test_data->roots.x1, test_data->roots.x2);
    assert(test_data);
    assert(test_num);

    int bug = 0; // код ошибки равен нулю
    Roots roots_by_function = {}; // структура где будут корни из функции

    // вычисляет корни, записывает их в roots_by_function, получает ошибки в bug
    bug = SqEqSolve(&test_data->coef, &roots_by_function);

    // printf("Получены корни: x1 = %lf, x2 = %lf\n", roots_by_function.x1, roots_by_function.x2);

    if (bug != 0)
    {
        Output(bug, &roots_by_function);
        printf("Ошибка в тесте номер %d\n", ++*test_num);
        return 0;
    }

    switch (roots_by_function.count_roots)
    {
        case TWO_SOLUTIONS:
        {
            double ref_x1 = MIN(test_data->roots.x1, test_data->roots.x2);
            double ref_x2 = MAX(test_data->roots.x1, test_data->roots.x2);
            double x1     = MIN(roots_by_function.x1, roots_by_function.x2);
            double x2     = MAX(roots_by_function.x1, roots_by_function.x2);

            if ((Equal(x1, ref_x1) == 0) || (Equal(x2, ref_x2) == 0))
            {
                RED
                printf("Ошибка в тесте номер %d\n", ++*test_num);
                YELLOW
                printf("Коэффициенты: "); PrintCoefs(&test_data->coef);
                DEF_COL
                printf("Эталон    - "); PrintRoots(&test_data->roots);
                printf("Результат - "); PrintRoots(&test_data->roots);
                return 1;
            }
            else
                return 0;

            break;
        }

        case ONE_SOLUTION:
        {
            double ref_x1 = test_data->roots.x1;
            double x1 = roots_by_function.x1;

            if (Equal(ref_x1, x1) == 0)
            {
                RED
                printf("Ошибка в тесте номер %d\n", ++*test_num);
                YELLOW
                printf("Коэффициенты: "); PrintCoefs(&test_data->coef);
                DEF_COL
                printf("Эталон    - "); PrintRoots(&test_data->roots);
                printf("Результат - "); PrintRoots(&test_data->roots);
                return 1;
            }
            return 0;
        }
        // TODO case to function
        case NO_SOLUTIONS:
        {
            if (test_data->roots.count_roots == NO_SOLUTIONS)
            {
                GREEN
                printf("No solutions\n");
                DEF_COL
            }
            else
            {
                RED
                printf("Test %d - no solutions error\n", ++*test_num);
                YELLOW
                printf("Коэффициенты: "); PrintCoefs(&test_data->coef);
                DEF_COL
                printf("Эталон    - "); PrintRoots(&test_data->roots);
                printf("Результат - "); PrintRoots(&test_data->roots);
            }
            return 0;

            break;
        }

        case INF_SOLUTIONS:
        {
            if (test_data->roots.count_roots == INF_SOLUTIONS)
            {
                GREEN
                printf("Inf solutions\n");
                DEF_COL
            }
            else
            {
                RED
                printf("Test %d - inf solutions error\n", ++*test_num);
                YELLOW
                printf("Коэффициенты: "); PrintCoefs(&test_data->coef);
                DEF_COL
                printf("Эталон    - "); PrintRoots(&test_data->roots);
                printf("Результат - "); PrintRoots(&test_data->roots);
                return 1;
            }
            return 0;
            break;
        }
    }
    return 0;
}

// запускает множество тестов
int UnitestSq(int (*test)(TestData *, int*))
{
    assert(test);

    int end = 0;
    int test_num = 0;

    printf("Запуск тестов\n");

    TestData test_data[SPEC_TESTS_NUM] =
    {
    //  {a,  b,  c, x1, x2, roots count}
        {.coef{.a =   1, .b =   2, .c =   1}, .roots{.x1 =   0, .x2 =   0, ONE_SOLUTION}},
        {.coef{.a =   0, .b =   0, .c =   0}, .roots{.x1 =   0, .x2 =   0, NO_SOLUTIONS}},
        {.coef{.a =  31, .b =  32, .c =  33}, .roots{.x1 =   0, .x2 =   0, TWO_SOLUTIONS}}
    };

    printf("Успешная инициализация данных для тестов\n\n\n");

    while (test_num < SPEC_TESTS_NUM)
    {
        printf("Запуск теста %d\n", test_num+1);
        end = test(&test_data[test_num], &test_num);
        test_num++; // указываем номер теста +1 от номера предыдущего

        if (end != TEST_FAULT)
        {
            RED
            break;
        }
    }

    printf("Тестирование завершено\n");
    DEF_COL
    return 0;
}
