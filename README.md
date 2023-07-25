# c_matrix_datatype

This library, written by me, adds the matrix_t data type to C. It is a 2D matrix of doubles and includes many operations, such as:

vas_eq_matrix - matrix comparison

vas_create_matrix - matrix creation

vas_remove_matrix - matrix removal

vas_sum_matrix - addition of matrices of the same size

vas_sub_matrix - subtraction of matrices of the same size

vas_mult_number - multiplication of a matrix by a double

vas_mult_matrix - multiplication of two matrices

vas_transpose - matrix transposition (rotation)

vas_calc_complements - matrix of cofactors

vas_determinant - calculation of the determinant

vas_inverse_matrix - inverse matrix

vas_get_minor - matrix minor

Auxiliary functions include:

vas_check_matrix_err - matrix validity check

vas_copy_matrix - matrix copy

vas_print_matrix - matrix print

Matrix filling functions include:

vas_fill_matrix_incr - filling with increment plus one

vas_fill_matrix_single - filling with a single value

vas_fill_matrix_random - filling with random values

The library is built into a .a file. To use it, you need to place vas_matrix.a and vas_matrix.h in the project folder.

To build the library, simply type "make" in the terminal in the project's src folder.

The library has unit tests. To run the tests, enter "make test" in the terminal in the src folder of the project (you may need the check library for C). The tests cover all functions and have very high coverage.

The library has passed auto-tests at the Programming School 21 of Sber (an analogue of School 42), and the auto-check (as well as my personal tests) included a valgrind test and no leaks were detected.

-----------------------------------------

Эта написанная мной библиотека добавляет дата-тип matrix_t в С, который является 2D матрицей даблов и включает многие операции, например:

vas_eq_matrix - сравнение матриц

vas_create_matrix - создание матриц

vas_remove_matrix - удаление матриц

vas_sum_matrix - сложение матриц одинакового размера

vas_sub_matrix - вычитание матриц одинакового размера

vas_mult_number - умножение матрицы на дабл

vas_mult_matrix - перемножение двух матриц

vas_transpose - транспонирование(поворот) матрицы

vas_calc_complements - матрица кофакторов

vas_determinant - определение детерминанта

vas_inverse_matrix - обратная матрица

vas_get_minor - минор матрицы

Вспомогательные:

vas_check_matrix_err - проверка на валидность матрицы

vas_copy_matrix - копирование матриц

vas_print_matrix - принт матрицы

Заполнение:

vas_fill_matrix_incr - заполнение с инкрементом плюс 1

vas_fill_matrix_single - заполнение одним значением

vas_fill_matrix_random - заполнение случайными значениями

Библиотека билдится в .a файл. Для работы нужно поместить в папку проекта vas_matrix.а и vas_matrix.h.

Для билда библиотеки достаточно написать make в терминале в папке src проекта.

Библиотека имеет юнит-тесты. Для запуска тестов необходимо ввести make test в терминале в src-папке проекта (возможно понадобится библиотека check для С). Тесты покрывают все функции и имеют очень высокое покрытие.

Библиотека прошла авто-тесты в Школе программирования 21 от Сбера (аналог Школы 42), авто-проверка (как и мои личные тесты) включала в себя тест на valgrind и ликов не было обнаружено.

