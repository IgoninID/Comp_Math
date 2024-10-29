#include <clocale>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#define lines 5
#define columns 6

using namespace std;

void fillM(vector<vector<double>>& matrix, vector<double>& C)
{
    matrix[0][0] = 36; matrix[0][1] = 5; matrix[0][2] = 5; matrix[0][3] = 1; matrix[0][4] = 5; matrix[0][5] = 68;
    matrix[1][0] = 5; matrix[1][1] = 22; matrix[1][2] = 3; matrix[1][3] = 3; matrix[1][4] = 1; matrix[1][5] = 65;
    matrix[2][0] = 3; matrix[2][1] = 3; matrix[2][2] = 44; matrix[2][3] = 3; matrix[2][4] = 3; matrix[2][5] = 150;
    matrix[3][0] = 5; matrix[3][1] = 4; matrix[3][2] = 5; matrix[3][3] = 39; matrix[3][4] = 3; matrix[3][5] = 109;
    matrix[4][0] = 3; matrix[4][1] = 2; matrix[4][2] = 5; matrix[4][3] = 3; matrix[4][4] = 48; matrix[4][5] = 76;
    for (int i = 0; i < lines; i++)
    {
        C[i] = matrix[i][columns - 1];
    }
}

void printM(const vector<vector<double>>& matrix)
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << fixed << setprecision(3) << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void Begin(int &k, vector<double> &X)
{
    k = 0;
    cout << k << " итерация" << "\n";
    for (int i = 0; i < lines; i++)
    {
        X[i] = 0;
        cout << fixed << setprecision(3) << X[i] << " ";
    }
    cout << "\n";
}

void Iter(int& k, const vector<vector<double>> &A, const vector<double> &C, vector<double> &XX, vector<double> &X)
{
    int how_many;
    do
    {
        how_many = 0;
        k += 1;
        cout << k << " итерация" << "\n";
        for (int i = 0; i < lines; i++)
        {
            XX[i] = C[i];
            for (int j = 0; j < lines; j++)
            {
                if (j != i)
                {
                    XX[i] = XX[i] - A[i][j] * X[j];
                }
            }
            XX[i] = XX[i] / A[i][i];
        }
        double e = 0.000001;
        for (int i = 0; i < lines; i++)
        {
            cout << fixed << setprecision(8) << XX[i] << " ";
            if (fabs(X[i] - XX[i]) < e)
            {
                how_many += 1;
            }
            X[i] = XX[i];
        }
        cout << "\n";
    } while (how_many != lines);
}

int main()
{
    setlocale(LC_ALL, "rus");
    vector<vector<double>> matrixA(lines, vector<double>(columns));
    vector<double> C(lines);
    vector<double> X(lines);
    vector<double> XX(lines);
    fillM(matrixA, C);
    cout << "Матрица: " << "\n";
    printM(matrixA);
    cout << "\n";
    int k;
    Begin(k, X);
    Iter(k, matrixA, C, XX, X);
}