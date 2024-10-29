#include <clocale>
#include <iostream>
#include <iomanip>
#include <vector>
#define lines 5
#define columns 6

using namespace std;

/// <summary>
/// Заполнение матрицы по варианту 5
/// </summary>
/// <param name="matrix-матрица"></param>
void fillM(vector< vector<double> >& matrix)
{
    matrix[0][0] = 9; matrix[0][1] = 9; matrix[0][2] = 0; matrix[0][3] = 0; matrix[0][4] = 0; matrix[0][5] = 18;
    matrix[1][0] = 7; matrix[1][1] = 3; matrix[1][2] = 6; matrix[1][3] = 0; matrix[1][4] = 0; matrix[1][5] = 16;
    matrix[2][0] = 0; matrix[2][1] = 3; matrix[2][2] = 4; matrix[2][3] = 5; matrix[2][4] = 0; matrix[2][5] = 12;
    matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 2; matrix[3][3] = 6; matrix[3][4] = 5; matrix[3][5] = 13;
    matrix[4][0] = 0; matrix[4][1] = 0; matrix[4][2] = 0; matrix[4][3] = 6; matrix[4][4] = 4; matrix[4][5] = 10;
}

/// <summary>
/// Вывод матрицы на экран
/// </summary>
/// <param name="matrix-матрица"></param>
void printM(const vector< vector<double> >& matrix)
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
/// Вывод матрицы на экран
/// </summary>
/// <param name="matrix-матрица"></param>
void printMO(const vector< vector<double> >& matrix)
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns+2; j++)
        {
            cout << fixed << setprecision(3) << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
}

void Calc_Vec(const vector<vector<double>> &Matrix, vector<vector<double>>& izmM, vector<double> &f, vector<double>& l, vector<double>& c, vector<double>& r, vector<double>& p, vector<double>& q, vector<double>& x)
{
    for (int k = 0; k < lines; k++)
    {
        izmM[k][0] = k;
        f[k] = Matrix[k][lines];
        izmM[k][1] = f[k];
        if (k >= 1)
        {
            l[k] = Matrix[k][k-1];
            izmM[k][2] = l[k];
        }
        c[k] = Matrix[k][k];
        izmM[k][3] = c[k];
        if (k <= lines - 2)
        {
            r[k] = Matrix[k][k+1];
            izmM[k][4] = r[k];
        }
        p[k] = 0;
        q[k] = 0;
        x[k] = 0;
    }
}

void CalcP_Q(vector<vector<double>> &izmM, vector<double> &p, vector<double>& q, const vector<double>& f, const vector<double>& c, const vector<double>& r, const vector<double>& l)
{
    p[0] = f[0] / c[0];
    q[0] = r[0] / c[0];
    izmM[0][5] = p[0];
    izmM[0][6] = q[0];
    for (int k = 1; k < lines; k++)
    {
        p[k] = (f[k] - l[k] * p[k - 1]) / (c[k] - l[k] * q[k - 1]);
        izmM[k][5] = p[k];
        q[k] = r[k] / (c[k] - l[k] * q[k - 1]);
        izmM[k][6] = q[k];
    }
}

void CalcX(vector<vector<double>>& izmM, vector<double> &x, const vector<double> &p, const vector<double> &q)
{
    x[lines - 1] = p[lines - 1];
    izmM[lines - 1][7] = x[lines - 1];
    for (int k = lines - 2; k >= 0; k--)
    {
        x[k] = p[k] - q[k] * x[k + 1];
        izmM[k][7] = x[k];
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    vector< vector<double> > matrix(lines, vector<double>(columns)); //матрица
    vector< vector<double> > matrixO(lines, vector<double>(columns+2)); //матрица
    vector<double> f(lines);
    vector<double> c(lines);
    vector<double> l(lines);
    vector<double> r(lines);
    vector<double> p(lines);
    vector<double> q(lines);
    vector<double> x(lines);
    fillM(matrix);
    cout << "Начальная матрица:\n";
    printM(matrix);
    Calc_Vec(matrix, matrixO, f, l, c, r, p, q, x);
    CalcP_Q(matrixO, p, q, f, c, r, l);
    CalcX(matrixO, x, p, q);
    cout << "\n" << "Матрица векторов(последняя колонка ответ):\n";
    printMO(matrixO);
}
