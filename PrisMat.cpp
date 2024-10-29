#include <iostream>
#include <iomanip>
#include <vector>
const int n = 5;

using namespace std;

void Fill(vector<vector<double>> &matrix)
{
    matrix[0][0] = 4; matrix[0][1] = 6; matrix[0][2] = 7; matrix[0][3] = 5; matrix[0][4] = 3; matrix[0][5] = 1; matrix[0][6] = 0; matrix[0][7] = 0; matrix[0][8] = 0; matrix[0][9] = 0;
    matrix[1][0] = 6; matrix[1][1] = 7; matrix[1][2] = 7; matrix[1][3] = 6; matrix[1][4] = 6; matrix[1][5] = 0; matrix[1][6] = 1; matrix[1][7] = 0; matrix[1][8] = 0; matrix[1][9] = 0;
    matrix[2][0] = 9; matrix[2][1] = 8; matrix[2][2] = 4; matrix[2][3] = 1; matrix[2][4] = 3; matrix[2][5] = 0; matrix[2][6] = 0; matrix[2][7] = 1; matrix[2][8] = 0; matrix[2][9] = 0;
    matrix[3][0] = 9; matrix[3][1] = 3; matrix[3][2] = 7; matrix[3][3] = 7; matrix[3][4] = 4; matrix[3][5] = 0; matrix[3][6] = 0; matrix[3][7] = 0; matrix[3][8] = 1; matrix[3][9] = 0;
    matrix[4][0] = 1; matrix[4][1] = 3; matrix[4][2] = 2; matrix[4][3] = 5; matrix[4][4] = 9; matrix[4][5] = 0; matrix[4][6] = 0; matrix[4][7] = 0; matrix[4][8] = 0; matrix[4][9] = 1;
}

void PrintMatrix(const vector<vector<double>> &matrix)
{
    for (int i = 0; i < n; i++)
    {
        for (int j =0; j < 2*n; j++)
        {
            cout << fixed << setprecision(2) << matrix[i][j] << setw(10);
        }
        cout << "\n";
    }
}

void rectangle(vector<vector<double>> &matrix, const int k)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = k+1; j < 2*n; j++)
        {
            if (i!=k)
            {
                matrix[i][j] = (matrix[i][j] * matrix[k][k] - matrix[k][j] * matrix[i][k])/matrix[k][k];
            }
        }
    }
}

void Zero(vector<vector<double>> &matrix, const int k)
{
    for (int i = 0; i < n; i++)
    {
        if (i != k)
        {
            matrix[i][k] = 0;
        }
    }
}

void Divide(vector<vector<double>> &matrix, const int k)
{
    for (int j = (2*n)-1; j >= k; j--)
    {
        matrix[k][j] = matrix[k][j]/matrix[k][k];
    }
}

void Pris(vector<vector<double>> &matrix)
{
    for (int k = 0; k < n; k++)
    {
        rectangle(matrix, k);
        Zero(matrix, k);
        Divide(matrix, k);
        PrintMatrix(matrix);
        cout << "\n";
    }
}

int main()
{
    vector<vector<double>> matrix(n, vector<double>(2*n));
    Fill(matrix);
    PrintMatrix(matrix);
    cout << "\n";
    Pris(matrix);
    return 0; 
}