#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
const int n = 5;

using namespace std;

void FillM(vector<vector<double>> &A)
{
	A[0][0] = 4; A[0][1] = 6; A[0][2] = 7; A[0][3] = 5; A[0][4] = 3;
	A[1][0] = 6; A[1][1] = 7; A[1][2] = 7; A[1][3] = 6; A[1][4] = 6;
	A[2][0] = 9; A[2][1] = 8; A[2][2] = 4; A[2][3] = 1; A[2][4] = 3;
	A[3][0] = 9; A[3][1] = 3; A[3][2] = 7; A[3][3] = 7; A[3][4] = 4;
	A[4][0] = 1; A[4][1] = 3; A[4][2] = 2; A[4][3] = 5; A[4][4] = 9;
}

void PrintM(const vector<vector<double>>& matrix)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << fixed << setprecision(5) << setw(10) << matrix[i][j];
		}
		cout << "\n";
	}
}

void QRm(vector<vector<double>>& A, vector<vector<double>> &Q, vector<vector<double>> &R)
{
	for (int t = 0; t <= 300; t++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				Q[i][j] = A[i][j];
				R[i][j] = 0;
			}
		}
		for (int j = 0; j < n; j++)
		{
			double SQsum = 0;
			for (int m = 0; m < n; m++)
			{
				SQsum = SQsum + (Q[m][j] * Q[m][j]);
			}
			R[j][j] = sqrt(SQsum);
			for (int i = 0; i < n; i++)
			{
				Q[i][j] = Q[i][j] / R[j][j];
			}
			for (int k = j + 1; k < n; k++)
			{
				for (int m = 0; m < n; m++)
				{
					R[j][k] = R[j][k] + (Q[m][j] * Q[m][k]);
				}
				for (int i = 0; i < n; i++)
				{
					Q[i][k] = Q[i][k] - (Q[i][j] * R[j][k]);
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				A[i][j] = 0;
				for (int k = 0; k < n; k++)
				{
					A[i][j] = A[i][j] + (R[i][k] * Q[k][j]);
				}
			}
		}

		cout << "Q = " << "\n";
		PrintM(Q);
		cout << "\n" << "R = " << "\n";
		PrintM(R);
		cout << "\n" << "A = " << "\n";
		PrintM(A);
		cout << "\n";
	}
}

int main()
{
	vector<vector<double>> matrixA(n, vector<double>(n));
	vector<vector<double>> matrixQ(n, vector<double>(n));
	vector<vector<double>> matrixR(n, vector<double>(n));
	FillM(matrixA);
	cout << "A = " << "\n";
	PrintM(matrixA);
	cout << "\n";
	QRm(matrixA, matrixQ, matrixR);
}