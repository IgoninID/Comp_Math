#include <iostream>
#include <iomanip>
#include <vector>
#define lines 5
#define columns 5

using namespace std;


void fillMatrixs(vector< vector<double> >&A, vector< vector<double> >& L, vector< vector<double> >& U)
{
    A[0][0] = 4; A[0][1] = 6; A[0][2] = 7; A[0][3] = 5; A[0][4] = 3;
    A[1][0] = 6; A[1][1] = 7; A[1][2] = 7; A[1][3] = 6; A[1][4] = 6;
    A[2][0] = 9; A[2][1] = 8; A[2][2] = 4; A[2][3] = 1; A[2][4] = 3;
    A[3][0] = 9; A[3][1] = 3; A[3][2] = 7; A[3][3] = 7; A[3][4] = 4;
    A[4][0] = 1; A[4][1] = 3; A[4][2] = 2; A[4][3] = 5; A[4][4] = 9;

    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
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
    }
}

void printM(const vector<vector<double>> &matrix)
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

void CalcLU(const vector< vector<double> >&A, vector< vector<double> >& L, vector< vector<double> >& U)
{
    for (int i = 0; i < lines; i++)
    {
        L[i][0] = A[i][0];
    }
    for (int j = 1; j < columns; j++)
    {
        U[0][j] = A[0][j]/L[0][0];
    }
    for (int k = 0; k < columns; k++)
    {
        for (int i = k; i < lines; i++)
        {
            L[i][k] = A[i][k];
            for (int m = 0; m < k; m++)
            {
                L[i][k] = L[i][k] - L[i][m] * U[m][k];
            }
        }
        if (k <= lines-2)
        {
            for (int j = k+1; j < columns; j++)
            {
                U[k][j] = A[k][j];
                for (int m = 0; m < k; m++)
                {
                    U[k][j] = U[k][j] - L[k][m] * U[m][j];
                }
                U[k][j] = U[k][j]/L[k][k];
            }
        }
    }
    printM(L);
    printM(U);
}

void CalcY(vector<vector<double>> &Y, const vector<vector<double>> &L)
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
                    Y[i][j] = Y[i][j] - L[i][m] * Y[m][j];
                }
                Y[i][j] = Y[i][j]/L[i][i];
            }
        }
    }
    printM(Y);
}

void CalcX(vector<vector<double>> &X, const vector<vector<double>> &U)
{
    for (int i = lines-1; i >= 0; i--)
    {
        for (int j = columns-1; j >= 0; j--)
        {
            if (j < i)
            {
                X[i][j] = 0;
            }
            else if (j == i)
            {
                X[i][j] = 1;
            }
            else if (j > i)
            {
                X[i][j] = 0;
                for (int m = i+1; m <= j; m++)
                {
                    X[i][j] = X[i][j] - U[i][m] * X[m][j];
                }
            }
        }
    }
    printM(X);
}

void CalcAinv(vector<vector<double>> &Ainv, const vector<vector<double>> &X, const vector<vector<double>> &Y)
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            Ainv[i][j] = 0;
            for (int m = 0; m < lines; m++)
            {
                Ainv[i][j] = Ainv[i][j] + X[i][m] * Y[m][j];
            }
        }
    }
    printM(Ainv);
}

int main()
{
    vector< vector<double> > matrixA(lines, vector<double>(columns)); //матрица A
    vector< vector<double> > matrixL(lines, vector<double>(columns)); //матрица L
    vector< vector<double> > matrixU(lines, vector<double>(columns)); //матрица U
    vector< vector<double> > matrixX(lines, vector<double>(columns)); //матрица X
    vector< vector<double> > matrixY(lines, vector<double>(columns)); //матрица Y
    vector< vector<double> > matrixAinv(lines, vector<double>(columns)); //матрица Ainv
    fillMatrixs(matrixA, matrixL, matrixU);
    printM(matrixA);
    CalcLU(matrixA, matrixL, matrixU);
    CalcY(matrixY, matrixL);
    CalcX(matrixX, matrixU);
    CalcAinv(matrixAinv, matrixX, matrixY);
}
