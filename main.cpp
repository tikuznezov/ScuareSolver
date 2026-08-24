#ifndef sqeq
#define sqeq
#include "sqeq.h"
#endif

#include "user_massages.cpp"
#include "math.cpp"
#include "Tests.cpp"


// TODO documentation
// TODO запуск конкретного теста ?

int main(int arg_c, char *arg_v[])
{
    // int argc = arg_c;
    // char **argv = arg_v;
    // CheckRunParameters(arg_c, *arg_v);
    // не получается передать параметры main в другую функцию


    if (arg_c > 1)
    {
        for (int i = 0; i < arg_c; i++)
        {
            //запускает тесты, если при запуске был параметр "st"
            if ((strcmp(arg_v[i], "st")) == 0)
            {
                UnitestSq(RunTestSq);
            }
            // запускает решение по данным из файла, если при запуске был параметр "f" по директории указанной после него
            else if ((strcmp(arg_v[i], "f")) == 0)
            {
                FILE *file = fopen(arg_v[++i], "r");
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
            else if ((strcmp("run_AI", arg_v[i]) == 0) || (strcmp(arg_v[i], "r") == 0))
            {
                HelloSq();
                UserChoice();
            }
            // запускает тесты по данным из файла, если при запуске был параметр "еf" по директории указанной после него
            else if ((strcmp(arg_v[i], "tf")) == 0)
            {
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
            else if (((strcmp(arg_v[i], "rand_t")) == 0) || ((strcmp(arg_v[i], "rt")) == 0))
            {

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
//int CheckRunParameters
