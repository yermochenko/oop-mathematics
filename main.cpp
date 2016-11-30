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
	double  f, f1, g;
	for (int i = 0; i<n; i++)
	{
		// �������� �� 0
		if (A[i][i] == 0)
		{
			for (int l = i + 1; l<n; l++)
			{
				if (A[l][i] != 0)
				{
					for (int t = 0; t<m; t++)
					{
						f1 = A[i][t];
						A[i][t] = A[l][t];
						A[l][t] = f1;
					}
				}
				else{
					cout << "��� ������������� �������" << endl;
					return 0;
				}
			}
		}//����� �������� �� 0
		f = A[i][i];

		for (int j = 0; j<m; j++)
		{
			A[i][j] /= f;
		}
		for (int h = 0; h<n; h++)
		{
			if (h != i)
			{

				g = A[h][i];

				for (int k = 0; k<m; k++)
				{
					A[h][k] = -g*A[i][k] + A[h][k];//������ ����

				}

			}
			//if (j == i) continue;
		}
	}





	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++){
			fs >> A[i][j];
			cout << "  " << A[i][j];
		}
		cout << endl;
	}
	//������� �������

	for (int i = 0; i < n; i++)
		cout << "x[" << i << "] = " << floor(A[i][m - 1] * 1000) / 1000 << " " << endl;
	cout << endl;
	return 0;
}
