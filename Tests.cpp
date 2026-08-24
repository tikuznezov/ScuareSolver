#ifndef sqeq
#define sqeq
#include "sqeq.h"
#endif

#define SPEC_TESTS_NUM 5
#define TEST_FAULT 0
#define  CUT_RAND 10000

struct TestData
{
    Coefficient coef;
    Roots roots;
};

int CheckTwoSolutions(TestData *test_data, Roots *roots_by_function, int *test_num);
int CheckOneSolution(TestData *test_data, Roots *roots_by_function, int *test_num);
int CheckNoSolutions(TestData *test_data, Roots *roots_by_function, int *test_num);
int CheckInfSolutions(TestData *test_data, Roots *roots_by_function, int *test_num);

// запускает тесты из внешнего файла
int TestsFromFile(int (*test)(TestData *, int*), FILE *file);

// запускает множество встроенных тестов
int UnitestSq(int (*test)(TestData *, int*));

// запускает тестирование квадратного уравнения
int RunTestSq(TestData *test_data, int *test_num);

// запускает тесты со случайными величинами
int StressTest(int (*test)(TestData *, int*), int num_of_tests);


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
            return CheckTwoSolutions(test_data, &roots_by_function, test_num);
            break;
        }

        case ONE_SOLUTION:
        {
            return CheckOneSolution(test_data, &roots_by_function, test_num);
            break;
        }

        case NO_SOLUTIONS:
        {
            return CheckNoSolutions(test_data, &roots_by_function, test_num);
            break;
        }

        case INF_SOLUTIONS:
        {
            return CheckInfSolutions(test_data, &roots_by_function, test_num);
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

    printf("\nЗапуск системных тестов\n");

    TestData test_data[SPEC_TESTS_NUM] =
    {
    //  {a,  b,  c, x1, x2, roots count}
        {.coef{.a =   1, .b =   2, .c =   1}, .roots{.x1 =  -1, .x2 =   0, ONE_SOLUTION}},
        {.coef{.a =   0, .b =   0, .c =   2}, .roots{.x1 =   0, .x2 =   0, NO_SOLUTIONS}},
        {.coef{.a =   0, .b =   0, .c =   0}, .roots{.x1 =   0, .x2 =   0, INF_SOLUTIONS}},
        {.coef{.a =   1, .b =   0, .c =  -1}, .roots{.x1 =  -1, .x2 =   1, TWO_SOLUTIONS}},
        {.coef{.a = 150, .b =  32, .c =  33}, .roots{.x1 = 455, .x2 =  21, NO_SOLUTIONS}}
    };

    printf("Успешная инициализация данных для тестов\n\n");

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


int CheckTwoSolutions(TestData *test_data, Roots *roots_by_function, int *test_num)
{
    double ref_x1 = MIN(test_data->roots.x1, test_data->roots.x2);
    double ref_x2 = MAX(test_data->roots.x1, test_data->roots.x2);
    double x1     = MIN(roots_by_function->x1, roots_by_function->x2);
    double x2     = MAX(roots_by_function->x1, roots_by_function->x2);

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

    return 0;
}

int CheckOneSolution(TestData *test_data, Roots *roots_by_function, int *test_num)
{
    double ref_x1 = test_data->roots.x1;
    double x1 = roots_by_function->x1;

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

int CheckNoSolutions(TestData *test_data, Roots *roots_by_function, int *test_num)
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
}

int CheckInfSolutions(TestData *test_data, Roots *roots_by_function, int *test_num)
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
}


int TestsFromFile(int (*test)(TestData *, int*), FILE *file)
{
    printf("Запуск тестов из указанного файла\n");

    int max_read_line = MAX_LINE;
    int error = 0;
    char check_eof;

    Coefficient coef_from_file = {};
    Roots roots_from_file = {};

    int num_of_eq = 0; // сколько уравнений считалось
    while (num_of_eq < MAX_NUM_OF_TESTS)
    {
        // Получаем коэффициенты и считываем конец файла
        check_eof = fscanf(file, "%lf; %lf; %lf", &coef_from_file.a, &coef_from_file.b, &coef_from_file.c);

        // увеличиваем счетчик считанных уравнений
        num_of_eq++;

        // решаем уравнение, получаем ошибки
        error = SqEqSolve(&coef_from_file, &roots_from_file);

        if (check_eof == EOF)
        {
            return 0;
            break;
        }
        else if (CheckRoots(&coef_from_file, &roots_from_file) != 0)
        {
            RED printf("Ошибка в тесте из файла номер %d \n", num_of_eq); DEF_COL
            YELLOW
            PrintCoefs(&coef_from_file);
            PrintRoots(&roots_from_file);
            DEF_COL
        }
        else if (error != 0)
        {
            Output(error, &roots_from_file);
            return 1;
            break;
        }
    }
    printf("Тесты успешно пройдены\n");
    return 0;
}

// Тесты с набором случайных коэффициентов
int StressTest(int (*test)(TestData *, int*), int num_of_tests)
{
    printf("Запуск теста со случайными величинами\n");

    int error = 0;
    int current_num_of_test = 0;
    srand(time(NULL));

    while (current_num_of_test++ < num_of_tests)
        {
            Coefficient coef = {};
            coef.a = rand() % CUT_RAND;
            coef.b = rand() % CUT_RAND;
            coef.c = rand() % CUT_RAND;

            Roots roots = {};

            error = SqEqSolve(&coef, &roots);
            if (CheckRoots(&coef, &roots) != 0)
            {
                // TODO нужно ли указывать номер теста?
                RED printf("Ошибка в тесте cо случайными величинами номер %d \n", current_num_of_test); DEF_COL
                YELLOW
                PrintCoefs(&coef);
                PrintRoots(&roots);
                DEF_COL
            }
            else if (error != 0)
            {
                Output(error, &roots);
                return 1;
                break;
            }

        }
    printf("Тестирование завершено\n\n");
    return 0;
}
