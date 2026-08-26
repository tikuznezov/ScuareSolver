#ifndef _TESTS
#define _TESTS

#include "sqeq.h"

const int SPEC_TESTS_NUM = 5;
const int TEST_FAULT = 0;
const int CUT_RAND = 100000;

// данные для тестирования
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
#endif
