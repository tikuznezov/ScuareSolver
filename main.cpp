#ifndef sqeq
#define sqeq
#include "sqeq.h"
#endif

#include "user_massages.cpp"
#include "math.cpp"
#include "Tests.cpp"


// TODO arg_c, arg_v, запуск тестов по необходимости
int main()
{
    UnitestSq(TestSq);
    HelloSq();
    UserChoice();
}
