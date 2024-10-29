#include <clocale>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#define lines 5
#define columns 6

using namespace std;

void fillM(vector<vector<double>>& matrix, vector<double>& B)
{
    matrix[0][0] = 8; matrix[0][1] = 6; matrix[0][2] = 1; matrix[0][3] = 3; matrix[0][4] = 4; matrix[0][5] = 33;
    matrix[1][0] = 6; matrix[1][1] = 9; matrix[1][2] = 5; matrix[1][3] = 5; matrix[1][4] = 2; matrix[1][5] = 51;
    matrix[2][0] = 1; matrix[2][1] = 5; matrix[2][2] = 8; matrix[2][3] = 2; matrix[2][4] = 3; matrix[2][5] = 42;
    matrix[3][0] = 3; matrix[3][1] = 5; matrix[3][2] = 2; matrix[3][3] = 9; matrix[3][4] = 4; matrix[3][5] = 41;
    matrix[4][0] = 4; matrix[4][1] = 2; matrix[4][2] = 3; matrix[4][3] = 4; matrix[4][4] = 9; matrix[4][5] = 34;
    for (int i = 0; i < lines; i++)
    {
        B[i] = matrix[i][columns - 1];
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

void printLU(const vector<vector<double>>& matrix)
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns - 1; j++)
        {
            cout << fixed << setprecision(3) << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void printV(const vector<double>& vec)
{
    for (int i = 0; i < lines; i++)
    {
        cout << fixed << setprecision(3) << vec[i] << " ";
    }
}

void zapL(vector<vector<double>>& L, const vector<vector<double>>& A)
{
    L[0][0] = sqrt(A[0][0]);
    for (int i = 1; i < lines; i++)
    {
        L[i][0] = A[i][0] / L[0][0];
    }
    for (int k = 1; k < lines; k++)
    {
        double sqSum = 0;
        for (int m = 0; m < k; m++)
        {
            sqSum = sqSum + L[k][m] * L[k][m];
        }
        L[k][k] = sqrt(A[k][k] - sqSum);
        if (k < lines - 1)
        {
            for (int i = k + 1; i < lines; i++)
            {
                double pairSum = 0;
                for (int m = 0; m < k; m++)
                {
                    pairSum = pairSum + L[i][m] * L[k][m];
                }
                L[i][k] = (A[i][k] - pairSum) / L[k][k];
            }
        }
    }
}

void zapU(vector<vector<double>>& U, const vector<vector<double>>& L)
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns - 1; j++)
        {
            U[i][j] = L[j][i];
        }
    }
}

void CalcY(vector<double>& Y, const vector<double>& B, const vector<vector<double>>& L)
{
    Y[0] = B[0] / L[0][0];
    for (int i = 0; i < lines; i++)
    {
        Y[i] = B[i];
        for (int m = 0; m < i; m++)
        {
            Y[i] = Y[i] - L[i][m] * Y[m];
        }
        Y[i] = Y[i] / L[i][i];
    }
}

void CalcX(vector<double>& X, const vector<double>& Y, const vector<vector<double>>& U)
{
    X[lines - 1] = Y[lines - 1] / U[lines - 1][lines - 1];
    for (int i = lines - 2; i >= 0; i--)
    {
        X[i] = Y[i];
        for (int m = i + 1; m < lines; m++)
        {
            X[i] = X[i] - U[i][m] * X[m];
        }
        X[i] = X[i] / U[i][i];
    }
}

int main()
{
    vector<vector<double>> matrixA(lines, vector<double>(columns));
    vector<vector<double>> matrixL(lines, vector<double>(columns - 1));
    vector<vector<double>> matrixU(lines, vector<double>(columns - 1));
    vector<double> B(lines);
    vector<double> Y(lines);
    vector<double> X(lines);
    fillM(matrixA, B);
    zapL(matrixL, matrixA);
    zapU(matrixU, matrixL);
    CalcY(Y, B, matrixL);
    CalcX(X, Y, matrixU);
    printM(matrixA);
    cout << "\n";
    printLU(matrixL);
    cout << "\n";
    printLU(matrixU);
    cout << "\n";
    printV(Y);
    cout << "\n";
    printV(X);
}