#include "tests.h"
#include "sqeq.h"



void CheckRunParameters(int argc, char** argv)
{
    assert(argv);

    if (argc > 0)
    {
        for (int i = 1; i <= argc; i++)
        {
            //запускает тесты, если при запуске был параметр "st"
            if ((strcmp(argv[i], "-st")) == 0)
            {
                UnitTestSq(); // вернет 0 при штатном исполнении, 1 при ошибке
            }
            // запускает решение по данным из файла, если при запуске был параметр "f" по директории указанной после него
            else if ((strcmp(argv[i], "-f")) == 0)
            {
                RP_SolveFromFile(argc, argv, &i); // вернет 0 при штатном исполнении, 1 при ошибке
            }
            // запускает диалог с пользователем
            else if ((strcmp("run_AI", argv[i]) == 0) || (strcmp(argv[i], "-r") == 0))
            {
                HelloSq();
                bool isprint = false;
                // Проверка, есть ли нужный флаг после флага печати. Если его нет, номер не увеличивается.
                if ((argc >= i+1) && ((strcmp(argv[i+1], "-pr")) == 0))// Прибавляем 1 тк нам нужен i+1 элемент
                {
                    isprint = true;
                    ++i;
                }
                UserChoice(isprint);
            }
            // запускает тесты по данным из файла, если при запуске был параметр "tf" по директории указанной после него
            else if ((strcmp(argv[i], "-tf")) == 0)
            {
                RP_TestsFromFile(argc, argv, &i); // вернет 0 при штатном исполнении, 1 при ошибке
            }
            // запускает тесты со случайными величинами, если при запуске был параметр rt по директории указанной после него
            else if (((strcmp(argv[i], "-rand_t")) == 0) || ((strcmp(argv[i], "-rt")) == 0))
            {
                RP_StressTest(argc, argv, &i); // вернет 0 при штатном исполнении, 1 при ошибке
            }
            // если нет нужного параметра, выводит предупреждение
            else
            {
                RED
                printf("Введен некорректный параметр\n");
                DEF_COL
                // return 1; // Обрыв выполнения при некорректном параметре
            }
        }
    }
    else
        WhatCanDoThisProgram();
    return;
}


int RP_SolveFromFile(int argc, char** argv, int *i)
{
    assert(argc);
    assert(argv);
    assert(i);

    if (argc < *i + 1) // Прибавляем 1 тк нам нужен i+1 элемент
    {
        RED printf("Неуказан путь к файлу для решения\n"); DEF_COL
        return 1;
    }
    FILE *file = fopen(argv[++*i], "r");
    if (file == NULL)
    {
        perror("Ошибка чтения файла"); // текстовое описание последней системной ошибки
        return 1;
    }
    // решает все уравнения из файла
    return SolveFromFile(file);
    // завершение программы после конца считывания из файла
}


int RP_TestsFromFile(int argc, char** argv, int *i)
{
    assert(argc);
    assert(argv);
    assert(i);

    if (argc < *i + 1) // Прибавляем 1 тк нам нужен i+1 элемент
    {
        RED printf("Не указан путь к файлу для тестирования\n"); DEF_COL
        return 1;
    }

    FILE *file = fopen(argv[++*i], "r");

    if (file == NULL)
    {
        perror("Ошибка чтения файла для теста"); //  perror выводит последнюю системную ошибку
        return 1;
    }
    // решает все уравнения из файла
    return TestsFromFile(file);
    // завершение программы после конца считывания из файла
}


int RP_StressTest(int argc, char** argv, int *i)
{
    assert(argc);
    assert(argv);
    assert(i);

    if (argc < *i + 1) // Прибавляем 1 тк нам нужен i+1 элемент
    {
        RED printf("Неуказанно количество тестов со случайной величиной (-rt *количество тестов*)\n"); DEF_COL
        return 1;
    }
    return StressTest(atoi(argv[++*i]));
}
