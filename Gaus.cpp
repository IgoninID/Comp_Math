#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <vector>
#define lines 5
#define columns 6

using namespace std;

/// <summary>
/// Заполнение матрицы по варианту 5
/// </summary>
/// <param name="matrix-матрица"></param>
void fillM(vector< vector<double> > &matrix)
{
    matrix[0][0] = 7.19; matrix[0][1] = 0.27; matrix[0][2] = -8.86; matrix[0][3] = 1.15; matrix[0][4] = 2.71; matrix[0][5] = -6.54;
    matrix[1][0] = 7.72; matrix[1][1] = -6.06; matrix[1][2] = 7.71; matrix[1][3] = -8.91; matrix[1][4] = -8.13; matrix[1][5] = 5.45;
    matrix[2][0] = 4.45; matrix[2][1] = -9.34; matrix[2][2] = 3.59; matrix[2][3] = 0.94; matrix[2][4] = -6.79; matrix[2][5] = 1.58;
    matrix[3][0] = 4.86; matrix[3][1] = -9.22; matrix[3][2] = -6.28; matrix[3][3] = -2.57; matrix[3][4] = -2.58; matrix[3][5] = 1.32;
    matrix[4][0] = 4.44; matrix[4][1] = 3.37; matrix[4][2] = -0.3; matrix[4][3] = 1.45; matrix[4][4] = 9.08; matrix[4][5] = 9.39;
}

/// <summary>
/// Вывод матрицы на экран
/// </summary>
/// <param name="matrix-матрица"></param>
void printM(const vector< vector<double> > &matrix)
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << fixed << setprecision(3) << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
}

/// <summary>
/// Проверка условия ведущего элемента на 0 в методе Гаусса
/// </summary>
/// <param name="k-счетчик цикла"></param>
/// <param name="matrix-матрица"></param>
void CheckAkk_0(int k, vector< vector<double> > &matrix)
{
    if (fabs(matrix[k][k]) < 0.000001)
    {
        int m = k + 1;
        while (fabs(matrix[m][k]) < 0.000001)
        {
            m += 1;
        }
        for (int j = 0; j < columns; j++)
        {
            double temp = matrix[k][j];
            matrix[k][j] = matrix[m][j];
            matrix[m][j] = temp;
        }
    }
}


/// <summary>
/// Правило прямоугольника в методе Гаусса
/// </summary>
/// <param name="k-счетчик цикла"></param>
/// <param name="matrix-матрица"></param>
void Rectangle(int k, vector< vector<double> > &matrix)
{
    for (int i = k + 1; i < lines; i++)
    {
        for (int j = k + 1; j < columns; j++)
        {
            matrix[i][j] = (matrix[i][j] * matrix[k][k] - matrix[k][j] * matrix[i][k]) / matrix[k][k];
        }
    }
}

/// <summary>
/// Обнуление элементов ведущего столбца в методе Гаусса
/// </summary>
/// <param name="k-счетчик цикла"></param>
/// <param name="matrix-матрица"></param>
void Zero(int k, vector< vector<double> > &matrix)
{
    for (int i = k + 1; i < lines; i++)
    {
        matrix[i][k] = 0;
    }
}

/// <summary>
/// Деление элементов ведущей строки на ведущий элемент в методе Гаусса и Жордана-Гаусса
/// </summary>
/// <param name="k-счетчик цикла"></param>
/// <param name="matrix-матрица"></param>
void DivLines(int k, vector< vector<double> > &matrix)
{
    for (int j = columns - 1; j >= k; j--)
    {
        matrix[k][j] = matrix[k][j] / matrix[k][k];
    }
}

/// <summary>
/// Обратный ход в методе Гаусса
/// </summary>
/// <param name="matrix-мартрица"></param>
/// <param name="answer-массив для ответа"></param>
void Reverse(vector< vector<double> > &matrix, vector<double> &answer)
{
    for (int k = (lines - 1); k >= 0; k--)
    {
        if (k == (lines - 1))
        {
            answer[k] = matrix[k][k + 1];
        }
        else
        {
            answer[k] = matrix[k][lines];
            for (int j = (lines - 1); j >= (k + 1); j--)
            {
                answer[k] = answer[k] - (answer[j] * matrix[k][j]);
            }
        }
    }
}

/// <summary>
/// Решение СЛАУ методом Гаусса
/// </summary>
/// <param name="matrix-матрица"></param>
/// <param name="answer-массив для ответа"></param>
void Gauss(vector< vector<double> > &matrix, vector<double> &answer)
{
    for (int k = 0; k < lines; k++)
    {
        CheckAkk_0(k, matrix);
        Rectangle(k, matrix);
        Zero(k, matrix);
        DivLines(k, matrix);
        cout << "\n";
        printM(matrix);
    }

    Reverse(matrix, answer);
}

/// <summary>
/// Проверка условия ведущего элемента на 0 в методе Жордана-Гаусса
/// </summary>
/// <param name="k-счетчик цикла"></param>
/// <param name="matrix-матрица"></param>
void CheckAkkJ(int k, vector< vector<double> > &matrix)
{
    if (fabs(matrix[k][k]) < 0.000001)
    {
        int m = k + 1;
        while ((fabs(matrix[m][k]) < 0.000001) || (m < columns))
        {
            if ((fabs(matrix[m][k]) > 0.000001) || (m > columns))
            {
                break;
            }
            m += 1;
        }
        for (int j = 0; j < columns; j++)
        {
            double temp = matrix[k][j];
            matrix[k][j] = matrix[m][j];
            matrix[m][j] = temp;
        }
    }
}

/// <summary>
/// Правило прямоугольника в методе Жордана-Гаусса
/// </summary>
/// <param name="k-счетчик цикла"></param>
/// <param name="matrix-матрица"></param>
void RetangleJ(int k, vector< vector<double> > &matrix)
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = k + 1; j < columns; j++)
        {
            if (i != k)
            {
                matrix[i][j] = (matrix[i][j] * matrix[k][k] - matrix[k][j] * matrix[i][k]) / matrix[k][k];
            }
        }
    }
}

/// <summary>
/// Обнуление элементов ведущего стобца в методе Жордана-Гаусса
/// </summary>
/// <param name="k-счетчик цикла"></param>
/// <param name="matrix-матрица"></param>
void ZeroJ(int k, vector< vector<double> > &matrix)
{
    for (int i = 0; i < lines; i++)
    {
        if (i != k)
        {
            matrix[i][k] = 0;
        }
    }
}

/// <summary>
/// Заполнение массива элементами из последнего столбца матрицы
/// </summary>
/// <param name="matrix-матрица"></param>
/// <param name="answer-массив для ответа"></param>
void CalcAnswGJ(vector< vector<double> > &matrix, vector<double> &answer)
{
    for (int i = 0; i < lines; i++)
    {
        answer[i] = matrix[i][lines];
    }
}

/// <summary>
/// Решение СЛАУ методом Жордана-Гаусса
/// </summary>
/// <param name="matrix-матрица"></param>
/// <param name="answer-массив для ответа"></param>
void GaussJ(vector< vector<double> > &matrix, vector<double> &answer)
{
    for (int k = 0; k < lines; k++)
    {
        CheckAkkJ(k, matrix);
        RetangleJ(k, matrix);
        ZeroJ(k, matrix);
        DivLines(k, matrix);
        cout << "\n";
        printM(matrix);
    }

    CalcAnswGJ(matrix, answer);
}

int main()
{
    system("chcp 65001 > nul"); //русский
    vector< vector<double> > matrix(lines, vector<double>(columns)); //матрица
    vector<double> answer(lines); //массив для ответа
    cout << "Игонин Вариант 5\n";
    fillM(matrix);
    printM(matrix);
    int GaussOrJGauss;
    cout << "Метод решения(Введите 1 или 0): " << "1 - Метод Гаусса, " << "0 - Метод Жордана-Гаусса\n";
    do
    {
        cin >> GaussOrJGauss;
    } while ((GaussOrJGauss!=1)&&(GaussOrJGauss != 0));

    if (GaussOrJGauss == 1)
    {
        Gauss(matrix, answer);
    }
    if (GaussOrJGauss == 0)
    {
        GaussJ(matrix, answer);
    }
    cout << "Ответ:" << "\n";
    for (int k = 0; k < lines; k++)
    {
        cout << fixed << setprecision(3) << answer[k] << "\t";
    }
    matrix.clear();
    answer.clear();
    return 0;
}