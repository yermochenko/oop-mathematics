#include "iostream"
#include <cmath>
#include <fstream>
using namespace std;

#include "matrix.h"

int main()
{
	/* example of using class Matrix */
	cout << "Input matrix size: ";
	int size;
	cin >> size;
	Matrix *matrix = new Matrix(size, size);
	cout << "Input matrix elements:" << endl;
	double element;
	for(int i = 0; i < matrix->rowsCount(); i++)
	{
		for(int j = 0; j < matrix->colsCount(); j++)
		{
			cin >> element;
			matrix->set(i, j, element);
		}
	}
	cout << "Matrix after transponing:" << endl;
	for(int i = 0; i < matrix->rowsCount(); i++)
	{
		for(int j = 0; j < matrix->colsCount(); j++)
		{
			cout << matrix->get(j, i) << '\t';
		}
		cout << endl;
	}
	delete matrix;

	double A[10][10];

	setlocale(LC_ALL, "rus");

	fstream fs("text.txt");//������ �� �����

	int n;
	fs >> n;

	int m = n + 1;//������� ��������� ������

	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++){
			fs >> A[i][j];
			cout << "  " << A[i][j];
		}
		cout << endl;
	}
	fs.close();
	//����� �������-������
	//������ ���, ���������� � ������������������ ����
	double g;
	for (int i = 0; i<n; i++)
	{
		// �������� �� 0
		if (A[i][i] == 0)
		{
			for (int k = i + 1; k<n; k++)
			{
				if (A[k][i] != 0)
				{
					for (int j = 0; j<m; j++)
					{
						g = A[i][j];
						A[i][j] = A[k][j];
						A[k][j] = g;
					}
				}
				else{
					cout << "��� ������������� �������" << endl;
					return 0;
				}
			}
		}//����� �������� �� 0
		g = A[i][i];

		for (int j = 0; j<m; j++)
		{
			A[i][j] /= g;
		}
		for (int k = 0; k<n; k++)
		{
			if (k != i)
			{

				g = A[k][i];

				for (int j = 0; j<m; j++)
				{
					A[k][j] = -g*A[i][j] + A[k][j];//������ ����

				}

			}
			//if (j == i) continue;
		}
	}

	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
		{
			fs >> A[i][j];
			cout << "  " << A[i][j];
		}
		cout << endl;
	}
	//������� �������

	for (int i = 0; i < n; i++)
	{
		cout << "x[" << i << "] = " << floor(A[i][m - 1] * 1000) / 1000 << " " << endl;
	}
	cout << endl;
	return 0;
}
