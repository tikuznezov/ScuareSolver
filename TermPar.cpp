#include "sqeq.h"
#include "tests.h"


int CheckRunParameters(int argc, char** argv)
{
    if (argc > 0)
    {
        for (int i = 1; i <= argc; i++)
        {
            //запускает тесты, если при запуске был параметр "st"
            if ((strcmp(argv[i], "-st")) == 0)
            {
                UnitestSq(RunTestSq);
            }
            // запускает решение по данным из файла, если при запуске был параметр "f" по директории указанной после него
            else if ((strcmp(argv[i], "-f")) == 0)
            {
                if (argc < i + 1) // Прибавляем 1 тк нам нужен i+1 элемент
                {
                    RED printf("Неуказан путь к файлу для решения\n"); DEF_COL
                    return 1;
                }
                FILE *file = fopen(argv[++i], "r");
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
            else if ((strcmp("run_AI", argv[i]) == 0) || (strcmp(argv[i], "-r") == 0))
            {
                HelloSq();
                UserChoice();
            }
            // запускает тесты по данным из файла, если при запуске был параметр "еf" по директории указанной после него
            else if ((strcmp(argv[i], "-tf")) == 0)
            {
                if (argc < i + 1) // Прибавляем 1 тк нам нужен i+1 элемент
                {
                    RED printf("Не указан путь к файлу для тестирования\n"); DEF_COL
                    return 1;
                }
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
            else if (((strcmp(argv[i], "-rand_t")) == 0) || ((strcmp(argv[i], "-rt")) == 0))
            {
                if (argc < i + 1) // Прибавляем 1 тк нам нужен i+1 элемент
                {
                    RED printf("Неуказанно количество тестов со случайной величиной (-rt *количество тестов*)\n"); DEF_COL
                    return 1;
                }
                StressTest(RunTestSq, atoi(argv[++i]));
            }
            else
            {
                RED printf("Введен некорректный параметр\n"); DEF_COL
                // return 1;
            }
        }
    }
    else
        WhatCanDoThisProgram();
    return 0;
}
