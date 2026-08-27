#ifndef _TESTS
#define _TESTS

#include "sqeq.h"

//! Количество системных тестов
const int SPEC_TESTS_NUM = 5;
//! Константа ошибки тестирования
const int TEST_FAULT = 0;
//! Константа, ограничивающая количество тестов со случайными величинами
const int CUT_RAND = 100000;

//! данные для тестирования
struct TestData
{
    Coefficient coef;
    Roots roots;
};

int CheckTwoSolutions(TestData *test_data, Roots *roots_by_function, int *test_num); //!< Проверяет верны ли два корня
int CheckOneSolution(TestData *test_data, Roots *roots_by_function, int *test_num); //!< Проверяет верен ли корень
int CheckNoSolutions(TestData *test_data, Roots *roots_by_function, int *test_num); //!< Проверка отсутствия решений
int CheckInfSolutions(TestData *test_data, Roots *roots_by_function, int *test_num); //!< Проверка бесконечного количества решений

/**
 @brief запускает тесты из внешнего файла
*/
int TestsFromFile(FILE *file);

//! Проводит один тест вычисления корней квадратного уравнения
int RunTestSq(Coefficient coef, Roots x12, int *error);

//! запускает множество встроенных тестов
int UnitTestSq(); // UnitTest

//! запускает тесты со случайными величинами
int StressTest(int num_of_tests);


#endif
