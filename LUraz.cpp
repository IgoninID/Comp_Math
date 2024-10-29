#include <clocale>
#include <iostream>
#include <iomanip>
#include <vector>
#define lines 5
#define columns 6

using namespace std;


void fillMatrixs(vector< vector<double> >&A, vector< vector<double> >& L, vector< vector<double> >& U, vector<double> &C)
{
    A[0][0] = 2; A[0][1] = 2; A[0][2] = 5; A[0][3] = 1; A[0][4] = 8; A[0][5] = 18;
    A[1][0] = 1; A[1][1] = 1; A[1][2] = 9; A[1][3] = 5; A[1][4] = 4; A[1][5] = 20;
    A[2][0] = 7; A[2][1] = 3; A[2][2] = 8; A[2][3] = 7; A[2][4] = 8; A[2][5] = 33;
    A[3][0] = 3; A[3][1] = 4; A[3][2] = 8; A[3][3] = 6; A[3][4] = 7; A[3][5] = 28;
    A[4][0] = 5; A[4][1] = 8; A[4][2] = 1; A[4][3] = 5; A[4][4] = 8; A[4][5] = 27;

    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns-1; j++)
        {
            L[i][j] = 0;
            if (i == j)
            {
                U[i][j] = 1;
            }
            else
            {
                U[i][j] = 0;
            }
        }
        C[i] = A[i][5];
    }
}

/// <summary>
/// Вывод матрицы на экран
/// </summary>
/// <param name="matrix-матрица"></param>
void printM(const vector< vector<double> >& matrix)
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns-1; j++)
        {
            cout << fixed << setprecision(3) << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
}

/// <summary>
/// Вывод матрицы на экран
/// </summary>
/// <param name="matrix-матрица"></param>
void printMA(const vector< vector<double> >& matrix)
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

void CalcL_U(vector< vector<double> >& L, vector< vector<double> >& U, const vector< vector<double> >& A)
{
    for (int i = 0; i < lines; i++)
    {
        L[i][0] = A[i][0];
    }
    for (int j = 1; j < lines; j++)
    {
        U[0][j] = A[0][j] / L[0][0];
    }

    for (int k = 1; k < lines; k++)
    {
        for (int i = k; i < lines; i++)
        {
            L[i][k] = A[i][k];
            for (int m = 0; m < k; m++)
            {
                L[i][k] = L[i][k] - L[i][m] * U[m][k];
            }
        }
        if (k <= lines - 1)
        {
            for (int j = k + 1; j < lines; j++)
            {
                U[k][j] = A[k][j];
                for (int m = 0; m < k; m++)
                {
                    U[k][j] = U[k][j] - L[k][m] * U[m][j];
                }
                U[k][j] = U[k][j] / L[k][k];
            }
        }
    }
}

void Calc_Y(vector<double>& Y, const vector<double>& C, const vector<vector<double>>& L)
{
    Y[0] = C[0] / L[0][0];
    for (int i = 1; i < lines; i++)
    {
        Y[i] = C[i];
        for (int m = 0; m <= i - 1; m++)
        {
            Y[i] = Y[i] - L[i][m] * Y[m];
        }
        Y[i] = Y[i] / L[i][i];
    }
}

void Calc_X(vector<double> &X,const vector<double> &Y,const vector<vector<double>> &U)
{
    X[lines-1] = Y[lines-1];
    for (int i = lines - 1; i >= 0; i--)
    {
        X[i] = Y[i];
        for (int m = i + 1; m < lines; m++)
        {
            X[i] = X[i] - U[i][m] * X[m];
        }
    }
}

void PrintVector(const vector<double> &vec)
{
    for (int i = 0; i < lines; i++)
    {
        cout << vec[i] << " ";
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    vector< vector<double> > matrixA(lines, vector<double>(columns)); //матрица A
    vector< vector<double> > matrixL(lines, vector<double>(columns-1)); //матрица L
    vector< vector<double> > matrixU(lines, vector<double>(columns-1)); //матрица U
    vector<double> Y(lines);
    vector<double> X(lines);
    vector<double> C(lines);
    fillMatrixs(matrixA, matrixL, matrixU, C);
    CalcL_U(matrixL, matrixU, matrixA);
    cout << "Исходная матрица:\n";
    printMA(matrixA);
    cout << "\n";
    cout << "Матрица L:\n";
    printM(matrixL);
    cout << "\n";
    cout << "Матрица U:\n";
    printM(matrixU);
    cout << "\n";
    cout << "Вектор Y:\n";
    Calc_Y(Y, C, matrixL);
    PrintVector(Y);
    cout << "\n";
    Calc_X(X, Y, matrixU);
    cout << "\n";
    cout << "Вектор X(ответ):\n";
    PrintVector(X);
}