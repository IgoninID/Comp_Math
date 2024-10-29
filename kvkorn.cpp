#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#define lines 5
#define columns 5

using namespace std;

void fillM(vector<vector<double>>& matrix)
{
    matrix[0][0] = 7; matrix[0][1] = 5; matrix[0][2] = 4; matrix[0][3] = 4; matrix[0][4] = 4;
    matrix[1][0] = 5; matrix[1][1] = 9; matrix[1][2] = 4; matrix[1][3] = 2; matrix[1][4] = 8;
    matrix[2][0] = 4; matrix[2][1] = 4; matrix[2][2] = 7; matrix[2][3] = 4; matrix[2][4] = 4;
    matrix[3][0] = 4; matrix[3][1] = 2; matrix[3][2] = 4; matrix[3][3] = 8; matrix[3][4] = 2;
    matrix[4][0] = 4; matrix[4][1] = 8; matrix[4][2] = 4; matrix[4][3] = 2; matrix[4][4] = 8;
}

void printM(const vector<vector<double>>& matrix)
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << fixed << setprecision(2) << setw(10) << matrix[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
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
    printM(L);
}

void CalcY(vector<vector<double>>& Y, const vector<vector<double>>& L)
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (j > i)
            {
                Y[i][j] = 0;
            }
            else if (j == i)
            {
                Y[i][j] = 1/L[i][i];
            }
            else if (j < i)
            {
                Y[i][j] = 0;
                for (int m = j; m < i; m++)
                {
                    Y[i][j] = Y[i][j] + L[i][m] * Y[m][j];
                }
                Y[i][j] = Y[i][j]/(-L[i][i]);
            }
        }
    }
    printM(Y);
}

void CalcAinv(vector<vector<double>>& Ainv, const vector<vector<double>>& Y)
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            Ainv[i][j] = 0;
            for (int m = 0; m < lines; m++)
            {
                Ainv[i][j] = Ainv[i][j] + Y[m][i] * Y[m][j];
            }
        }
    }
    printM(Ainv);
}

int main()
{
    vector<vector<double>> matrixA(lines, vector<double>(columns));
    vector<vector<double>> matrixL(lines, vector<double>(columns));
    vector<vector<double>> matrixY(lines, vector<double>(columns));
    vector<vector<double>> matrixAinv(lines, vector<double>(columns));
    fillM(matrixA);
    printM(matrixA);
    zapL(matrixL, matrixA);
    CalcY(matrixY, matrixL);
    CalcAinv(matrixAinv, matrixY);
}