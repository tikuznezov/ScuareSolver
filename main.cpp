#ifndef sqeq
#define sqeq
#include "sqeq.h"
#endif

#include "user_massages.cpp"
#include "math.cpp"
#include "tests.cpp"


// TODO запуск конкретного теста ?
// TODO doxygen documentation
// TODO убрать все из main

int main(int arg_c, char *arg_v[])
{
    // int argc = arg_c;
    // char **argv = arg_v;
    // CheckRunParameters(arg_c, *arg_v);
    // не получается передать параметры main в другую функцию


//     char *run_parameters[arg_c-1];
//     int count_parameters = arg_c-1;
//
//     for (int i = 0; i < count_parameters; i++)
//     {
//         run_parameters[i] = strdup(arg_v[i]);
//     }
//     CheckRunParameters(count_parameters, *run_parameters);


    if (arg_c > 1)
    {
        for (int i = 0; i < arg_c; i++)
        {
            //запускает тесты, если при запуске был параметр "st"
            if ((strcmp(arg_v[i], "-st")) == 0)
            {
                UnitestSq(RunTestSq);
            }
            // запускает решение по данным из файла, если при запуске был параметр "f" по директории указанной после него
            else if ((strcmp(arg_v[i], "-f")) == 0)
            {
                if (arg_c < i + 2) // Прибавляем 1 тк arg_v[0] - путь к файлу, и нам нужен i+1 элемент
                {
                    RED printf("Неуказан путь к файлу для решения\n"); DEF_COL
                    return 1;
                }
                FILE *file = fopen(arg_v[++i], "r");
                if (file == NULL)
                {
                    perror("Ошибка чтения файла"); // текстовое описание последней системной ошибки
                    return 1;
                }
                // решает все уравнения из файла
                return SolveFromFile(file);
                // завершение программы после конца считывания из файла
            }
            // запускает диалог с пользователем
            else if ((strcmp("run_AI", arg_v[i]) == 0) || (strcmp(arg_v[i], "-r") == 0))
            {
                HelloSq();
                UserChoice();
            }
            // запускает тесты по данным из файла, если при запуске был параметр "еf" по директории указанной после него
            else if ((strcmp(arg_v[i], "-tf")) == 0)
            {
                if (arg_c < i + 2) // Прибавляем 1 тк arg_v[0] - путь к файлу, и нам нужен i+1 элемент
                {
                    RED printf("Неуказан путь к файлу для тестирования\n"); DEF_COL
                    return 1;
                }
                FILE *file = fopen(arg_v[++i], "r");
                if (file == NULL)
                {
                    perror("Ошибка чтения файла для теста");
                    return 1;
                }
                // решает все уравнения из файла
                TestsFromFile(RunTestSq, file);
                // завершение программы после конца считывания из файла
            }
            // запускает тесты со случайными величинами, если при запуске был параметр rt по директории указанной после него
            else if (((strcmp(arg_v[i], "-rand_t")) == 0) || ((strcmp(arg_v[i], "-rt")) == 0))
            {
                if (arg_c < i + 2) // Прибавляем 1 тк arg_v[0] - путь к файлу, и нам нужен i+1 элемент
                {
                    RED printf("Неуказанно количество тестов со случайной величиной (-rt *количество тестов*)\n"); DEF_COL
                    return 1;
                }
                StressTest(RunTestSq, atoi(arg_v[++i]));
            }
        }
    }
    else
        WhatCanDoThisProgram();

    return 0;
}
//
// // проверяет параметры запуска программы, если они равны нулю, запускает диалог с пользователем
// int CheckRunParameters(int arg_c, char *arg_v[])
// {
//     for (int i = 0; i < arg_c; i++)
//     {
//         if ((strcmp(arg_v[i], "t")) == 0) // запускает тесты, если при запуске был параметр "t"
//             UnitestSq(RunTestSq);
//
//         else if ((strcmp(arg_v[i], "f")) == 0) // считывает данные из файла, если при запуске был параметр "f" по директории указанной после него
//         {
//             FILE *file = fopen(arg_v[++i], "r");
//             if (file == NULL)
//             {
//                 perror("Ошибка чтения файла");
//                 return 1;
//             }
//             // решает все уравнения из файла
//             return SolveFromFile(file);
//             // завершение программы после конца считывания из файла
//         }
//     }
//     return 0;
// }
int CheckRunParameters(int argc, char** argv)
{
    if (argc > 0)
    {
        for (int i = 0; i < argc; i++)
        {
            //запускает тесты, если при запуске был параметр "st"
            if ((strcmp(argv[i], "st")) == 0)
            {
                UnitestSq(RunTestSq);
            }
            // запускает решение по данным из файла, если при запуске был параметр "f" по директории указанной после него
            else if ((strcmp(argv[i], "f")) == 0)
            {
                FILE *file = fopen(argv[++i], "r");
                if (file == NULL)
                {
                    perror("Ошибка чтения файла");
                    return 1;
                }
                // решает все уравнения из файла
                SolveFromFile(file);
                // завершение программы после конца считывания из файла
            }
            // запускает диалог с пользователем
            else if ((strcmp("run_AI", argv[i]) == 0) || (strcmp(argv[i], "r") == 0))
            {
                HelloSq();
                UserChoice();
            }
            // запускает тесты по данным из файла, если при запуске был параметр "еf" по директории указанной после него
            else if ((strcmp(argv[i], "tf")) == 0)
            {
                FILE *file = fopen(argv[++i], "r");
                if (file == NULL)
                {
                    perror("Ошибка чтения файла для теста");
                    return 1;
                }
                // решает все уравнения из файла
                TestsFromFile(RunTestSq, file);
                // завершение программы после конца считывания из файла
            }
            // запускает тесты со случайными величинами, если при запуске был параметр rt по директории указанной после него
            else if (((strcmp(argv[i], "rand_t")) == 0) || ((strcmp(argv[i], "rt")) == 0))
            {

                StressTest(RunTestSq, atoi(argv[++i]));
            }
        }
    }
    else
        WhatCanDoThisProgram();

    return 0;
}
