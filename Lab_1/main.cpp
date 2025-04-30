//
// Created by Dmitriy on 06.03.2025.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Функция для ввода параметров матриц
void Enter_parm_matr(int& n1, int& m1, int& n2, int& m2) {
    do {
        cout << "Введите размеры первой матрицы n*m\n";
        cout << "значение n = ";
        cin >> n1;
        cout << "значение m = ";
        cin >> m1;
    } while (n1 <= 0 || m1 <= 0);

    do {
        cout << "Введите размеры второй матрицы n*m\n";
        cout << "значение n = ";
        cin >> n2;
        cout << "значение m = ";
        cin >> m2;
    } while (n2 <= 0 || m2 <= 0);
}

// Функция для заполнения матриц
void filling_matr(int** M1, int** M2, int n1, int m1, int n2, int m2, int k) {
    switch (k) {
    case 1:
        for (int i = 0; i < n1; i++)
            for (int j = 0; j < m1; j++)
                cin >> M1[i][j];
        for (int i = 0; i < n2; i++)
            for (int j = 0; j < m2; j++)
                cin >> M2[i][j];
        break;
    case 2:
        for (int i = 0; i < n1; i++)
            for (int j = 0; j < m1; j++)
                M1[i][j] = rand() % 10;
        for (int i = 0; i < n2; i++)
            for (int j = 0; j < m2; j++)
                M2[i][j] = rand() % 10;
        break;
    }
}

// Функция для вывода матрицы
void print_matr(int** M, int n, int m, const string& name) {
    cout << "\n" << name << "\n\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << M[i][j] << " ";
        cout << endl;
    }
}

// Функция для приведения матриц к требуемому размеру
void Reduction_matr(int**& M3, int**& M4, int** M1, int** M2, int n1, int m1, int n2, int m2, int& l) {
    while (l < n1 || l < n2 || l < m1 || l < m2)
        l *= 2;

    M3 = new int* [l];
    M4 = new int* [l];
    for (int i = 0; i < l; i++) {
        M3[i] = new int[l];
        M4[i] = new int[l];
        for (int j = 0; j < l; j++) {
            M3[i][j] = 0;
            M4[i][j] = 0;
        }
    }

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m1; j++)
            M3[i][j] = M1[i][j];

    for (int i = 0; i < n2; i++)
        for (int j = 0; j < m2; j++)
            M4[i][j] = M2[i][j];
}

// Функция для разбиения матриц на подматрицы
void submatrices(int** M3, int** M4, int l, int**& mat1, int**& mat2, int**& mat3, int**& mat4, int**& mat5, int**& mat6, int**& mat7, int**& mat8) {
    mat1 = new int* [l / 2];
    mat2 = new int* [l / 2];
    mat3 = new int* [l / 2];
    mat4 = new int* [l / 2];
    mat5 = new int* [l / 2];
    mat6 = new int* [l / 2];
    mat7 = new int* [l / 2];
    mat8 = new int* [l / 2];

    for (int i = 0; i < l / 2; i++) {
        mat1[i] = new int[l / 2];
        mat2[i] = new int[l / 2];
        mat3[i] = new int[l / 2];
        mat4[i] = new int[l / 2];
        mat5[i] = new int[l / 2];
        mat6[i] = new int[l / 2];
        mat7[i] = new int[l / 2];
        mat8[i] = new int[l / 2];

        for (int j = 0; j < l / 2; j++) {
            mat1[i][j] = M3[i][j];
            mat2[i][j] = M3[i][j + l / 2];
            mat3[i][j] = M3[i + l / 2][j];
            mat4[i][j] = M3[i + l / 2][j + l / 2];
            mat5[i][j] = M4[i][j];
            mat6[i][j] = M4[i][j + l / 2];
            mat7[i][j] = M4[i + l / 2][j];
            mat8[i][j] = M4[i + l / 2][j + l / 2];
        }
    }
}

// Функция для создания промежуточных матриц
void intermed_matr(int**& p1, int**& p2, int**& p3, int**& p4, int**& p5, int**& p6, int**& p7, int l) {
    p1 = new int* [l / 2];
    p2 = new int* [l / 2];
    p3 = new int* [l / 2];
    p4 = new int* [l / 2];
    p5 = new int* [l / 2];
    p6 = new int* [l / 2];
    p7 = new int* [l / 2];

    for (int i = 0; i < l / 2; i++) {
        p1[i] = new int[l / 2];
        p2[i] = new int[l / 2];
        p3[i] = new int[l / 2];
        p4[i] = new int[l / 2];
        p5[i] = new int[l / 2];
        p6[i] = new int[l / 2];
        p7[i] = new int[l / 2];
    }
}

// Функция для вычисления промежуточных матриц
void Calcul_intermed_matr(int** p1, int** p2, int** p3, int** p4, int** p5, int** p6, int** p7, int** mat1, int** mat2, int** mat3, int** mat4, int** mat5, int** mat6, int** mat7, int** mat8, int l) {
    for (int i = 0; i < l / 2; i++) {
        for (int j = 0; j < l / 2; j++) {
            p1[i][j] = 0;
            for (int z = 0; z < l / 2; z++) {
                p1[i][j] += (mat1[i][z] + mat4[i][z]) * (mat5[z][j] + mat8[z][j]);
            }

            p2[i][j] = 0;
            for (int z = 0; z < l / 2; z++) {
                p2[i][j] += (mat3[i][z] + mat4[i][z]) * mat5[z][j];
            }

            p3[i][j] = 0;
            for (int z = 0; z < l / 2; z++) {
                p3[i][j] += mat1[i][z] * (mat6[z][j] - mat8[z][j]);
            }

            p4[i][j] = 0;
            for (int z = 0; z < l / 2; z++) {
                p4[i][j] += mat4[i][z] * (mat7[z][j] - mat5[z][j]);
            }

            p5[i][j] = 0;
            for (int z = 0; z < l / 2; z++) {
                p5[i][j] += (mat1[i][z] + mat2[i][z]) * mat8[z][j];
            }

            p6[i][j] = 0;
            for (int z = 0; z < l / 2; z++) {
                p6[i][j] += (mat3[i][z] - mat1[i][z]) * (mat5[z][j] + mat6[z][j]);
            }

            p7[i][j] = 0;
            for (int z = 0; z < l / 2; z++) {
                p7[i][j] += (mat2[i][z] - mat4[i][z]) * (mat7[z][j] + mat8[z][j]);
            }
        }
    }
}

// Функция для создания вспомогательных матриц
void auxiliary_matr(int**& mat9, int**& mat10, int**& mat11, int**& mat12, int l) {
    mat9 = new int* [l / 2];
    mat10 = new int* [l / 2];
    mat11 = new int* [l / 2];
    mat12 = new int* [l / 2];

    for (int i = 0; i < l / 2; i++) {
        mat9[i] = new int[l / 2];
        mat10[i] = new int[l / 2];
        mat11[i] = new int[l / 2];
        mat12[i] = new int[l / 2];
    }
}

// Функция для вычисления вспомогательных матриц
void Calcul_auxiliary_matr(int** mat9, int** mat10, int** mat11, int** mat12, int** p1, int** p2, int** p3, int** p4, int** p5, int** p6, int** p7, int l) {
    for (int i = 0; i < l / 2; i++) {
        for (int j = 0; j < l / 2; j++) {
            mat9[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
            mat10[i][j] = p3[i][j] + p5[i][j];
            mat11[i][j] = p2[i][j] + p4[i][j];
            mat12[i][j] = p1[i][j] - p2[i][j] + p3[i][j] + p6[i][j];
        }
    }
}

// Функция для создания результирующей матрицы
void Create_result_matr(int**& M5, int l) {
    M5 = new int* [l];
    for (int i = 0; i < l; i++) {
        M5[i] = new int[l];
    }
}

// Функция для заполнения результирующей матрицы
void transferr_auxiliary_resulting(int** M5, int** mat9, int** mat10, int** mat11, int** mat12, int l) {
    for (int i = 0; i < l / 2; i++) {
        for (int j = 0; j < l / 2; j++) {
            M5[i][j] = mat9[i][j];
            M5[i][j + l / 2] = mat10[i][j];
            M5[i + l / 2][j] = mat11[i][j];
            M5[i + l / 2][j + l / 2] = mat12[i][j];
        }
    }
}

// Функция для выравнивания границ результирующей матрицы
void Alignment_result_matr(int** M5, int**& M6, int l, int& f, int& s) {
    int x = 0;
    f = 100;
    s = 100;

    for (int i = 0; i < l; i++) {
        x = 0;
        for (int j = 0; j < l; j++) {
            if (M5[i][j] != 0) {
                x++;
                f = 100;
            }
        }
        if (x == 0 && i < f) {
            f = i;
        }
    }

    for (int i = 0; i < l; i++) {
        x = 0;
        for (int j = 0; j < l; j++) {
            if (M5[j][i] != 0) {
                x++;
                s = 100;
            }
        }
        if (x == 0 && i < s) {
            s = i;
        }
    }

    M6 = new int* [f];
    for (int i = 0; i < f; i++) {
        M6[i] = new int[s];
        for (int j = 0; j < s; j++)
            M6[i][j] = M5[i][j];
    }
}

// Функция для очистки динамической памяти
void clean_memory(int** M1, int** M2, int** M3, int** M4, int** M5, int** M6, int** mat1, int** mat2, int** mat3, int** mat4, int** mat5, int** mat6, int** mat7, int** mat8, int** mat9, int** mat10, int** mat11, int** mat12, int** p1, int** p2, int** p3, int** p4, int** p5, int** p6, int** p7, int n1, int n2, int l, int f) {
    for (int i = 0; i < n1; i++)
        delete[] M1[i];
    for (int i = 0; i < n2; i++)
        delete[] M2[i];
    for (int i = 0; i < l; i++) {
        delete[] M3[i];
        delete[] M4[i];
        delete[] M5[i];
    }
    for (int i = 0; i < f; i++)
        delete[] M6[i];
    for (int i = 0; i < l / 2; i++) {
        delete[] mat1[i];
        delete[] mat2[i];
        delete[] mat3[i];
        delete[] mat4[i];
        delete[] mat5[i];
        delete[] mat6[i];
        delete[] mat7[i];
        delete[] mat8[i];
        delete[] mat9[i];
        delete[] mat10[i];
        delete[] mat11[i];
        delete[] mat12[i];
        delete[] p1[i];
        delete[] p2[i];
        delete[] p3[i];
        delete[] p4[i];
        delete[] p5[i];
        delete[] p6[i];
        delete[] p7[i];
    }
    delete[] M1, M2, M3, M4, M5, M6;
    delete[] mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, mat9, mat10, mat11, mat12;
    delete[] p1, p2, p3, p4, p5, p6, p7;
}

int main1() {
    srand(time(NULL));
    int n1, m1, n2, m2, k, l = 2;
    system("chcp 1251");
    cout << "Вас приветствует программа" << endl <<
        "быстрого перемножения матриц методом Штрассена\n\n";

    Enter_parm_matr(n1, m1, n2, m2);

    int** M1 = new int* [n1];
    for (int i = 0; i < n1; i++)
        M1[i] = new int[m1];
    int** M2 = new int* [n2];
    for (int i = 0; i < n2; i++)
        M2[i] = new int[m2];

    do {
        cout << "Выберите способ заполнения матриц\n" <<
            "1 - Вручную \n2 - Случайным образом\n";
        cin >> k;
    } while (k != 1 && k != 2);

    filling_matr(M1, M2, n1, m1, n2, m2, k);

    print_matr(M1, n1, m1, "Матрица 1");
    print_matr(M2, n2, m2, "Матрица 2");

    int** M3, ** M4;
    Reduction_matr(M3, M4, M1, M2, n1, m1, n2, m2, l);

    print_matr(M3, l, l, "Приведенная матрица 1");
    print_matr(M4, l, l, "Приведенная матрица 2");

    int** mat1, ** mat2, ** mat3, ** mat4, ** mat5, ** mat6, ** mat7, ** mat8;
    submatrices(M3, M4, l, mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8);

    int** p1, ** p2, ** p3, ** p4, ** p5, ** p6, ** p7;
    intermed_matr(p1, p2, p3, p4, p5, p6, p7, l);

    Calcul_intermed_matr(p1, p2, p3, p4, p5, p6, p7, mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, l);

    int** mat9, ** mat10, ** mat11, ** mat12;
    auxiliary_matr(mat9, mat10, mat11, mat12, l);

    Calcul_auxiliary_matr(mat9, mat10, mat11, mat12, p1, p2, p3, p4, p5, p6, p7, l);

    int** M5;
    Create_result_matr(M5, l);

    transferr_auxiliary_resulting(M5, mat9, mat10, mat11, mat12, l);

    int f, s;
    int** M6;
    Alignment_result_matr(M5, M6, l, f, s);

    print_matr(M6, f, s, "Результирующая матрица");

    clean_memory(M1, M2, M3, M4, M5, M6, mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, mat9, mat10, mat11, mat12, p1, p2, p3, p4, p5, p6, p7, n1, n2, l, f);

    system("pause");
    return 0;
}