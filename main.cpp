#ifndef sqeq
#define sqeq
#include "sqeq.h"
#endif

#include "user_massages.cpp"
#include "math.cpp"
#include "Tests.cpp"


// TODO arg_c, arg_v, запуск тестов по необходимости
// TODO stress test
// TODO documentation
// TODO perror input from file


int main()
{
    UnitestSq(RunTestSq);
    HelloSq();
    UserChoice();
}
