#ifndef sqeq
#define sqeq
#include "sqeq.h"
#endif

#include "user_massages.cpp"
#include "math.cpp"
#include "Tests.cpp"

// TODO stress test
// TODO documentation
// TODO perror input from file


int main(int arg_c, char *arg_v[])
{
    for (int i = 0; i < arg_c; i++)
    {
        if ((strcmp(arg_v[i], "t")) == 0)
            UnitestSq(RunTestSq);
        if ((strcmp(arg_v[i], "f")) == 0)
        {
            FILE *file = fopen(arg_v[++i], "r");
            if (file == NULL)
            {
                perror("Ошибка чтения файла");
                return 1;
            }

            SolveFromFile(file);
        }

    }

    //HelloSq();
    //UserChoice();

    RED printf("Снять комментирование\n");
}
