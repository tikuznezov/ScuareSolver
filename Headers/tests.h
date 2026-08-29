#ifndef _TESTS
#define _TESTS


#include "sqeq.h"

//! Константа ошибки тестирования
const int TEST_FAULT = 0;
//! Константа, ограничивающая количество тестов со случайными величинами
const int CUT_RAND = 100000;


/**
 * @brief Данные для тестирования
 */
struct TestData
{
    Coefficient coef;
    Roots roots;
};
/**
 * @brief Проверяет, соответствуют ли два корня из данных для теста двум корням,
 *        полученным в ходе решения уравнения.
 *
 * @param test_data - структура с данными для теста
 * @param roots_by_function - структура с корнями, полученными в ходе решения уравнения по коэффициентам из test_data
 * @param test_num - порядковый номер проводимого теста
 * @return int
 */
int CheckTwoSolutions(TestData *test_data, Roots *roots_by_function, int *test_num);

/**
 * @brief Проверяет, соответствует ли корень из данных для теста корню,
 *        полученному в ходе решения уравнения.
 *
 * @param test_data - структура с данными для теста
 * @param roots_by_function - структура с корнями, полученными в ходе решения уравнения по коэффициентам из test_data
 * @param test_num - порядковый номер проводимого теста
 * @return int
 */
int CheckOneSolution(TestData *test_data, Roots *roots_by_function, int *test_num);

/**
 * @brief Проверяет, действительно ли отсутствуют корни у уравнения,
 *        сравнивая данные из test_data и roots_by_function.
 *
 * @param test_data - структура с данными для теста
 * @param roots_by_function - структура с корнями, полученными в ходе решения уравнения по коэффициентам из test_data
 * @param test_num - порядковый номер проводимого теста
 * @return int
 */
int CheckNoSolutions(TestData *test_data, Roots *roots_by_function, int *test_num);

/**
 * @brief Проверяет, действительно ли у уравнения бесконечное количество решений,
 *        сравнивая данные из test_data и roots_by_function.
 *
 * @param test_data - структура с данными для теста
 * @param roots_by_function - структура с корнями, полученными в ходе решения уравнения по коэффициентам из test_data
 * @param test_num - порядковый номер проводимого теста
 * @return int
 */
int CheckInfSolutions(TestData *test_data, Roots *roots_by_function, int *test_num); //!< Проверка бесконечного количества решений

/**
 * @brief Запускает тесты из внешнего файла
 *
 * @param file - ссылка на файл, из которого будут взяты коэффициенты для уравнения
 * @return int - возвращает 0 при штатной работе и отличное от нуля значение, при ошибках
 */
int TestsFromFile(FILE *file);

/**
 * @brief Проводит один тест вычисления корней квадратного уравнения
 *
 * @param coef -
 * @param x12
 * @param error
 * @return int
 */
int RunTestSq(Coefficient *coef, Roots *x12, int *error);

//! запускает множество встроенных тестов
int UnitTestSq(); // UnitTest

//! запускает тесты со случайными величинами
int StressTest(int num_of_tests);


#endif
