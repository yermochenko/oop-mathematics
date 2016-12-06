#include "iostream"
#include <cmath>
#include <fstream>
using namespace std;

#include "matrix.h"

int main()
{
	setlocale(LC_ALL, "rus");
	fstream fs("text.txt");//������ �� �����
	unsigned int n;
	fs >> n;
	double e;
	Matrix *matrix = new Matrix(n, n + 1);
	for (unsigned int i = 0; i < matrix->rowsCount(); i++)
	{
		for (unsigned int j = 0; j < matrix->colsCount(); j++)
		{
			fs >> e;
			matrix->set(i, j, e);
			cout << e << "\t";
		}
		cout << endl;
	}
	fs.close();

	//����� �������-������
	//������ ���, ���������� � ������������������ ����
	double  f;
	for (unsigned int i = 0; i < matrix->rowsCount(); i++)
	{
		// �������� �� 0
		if (matrix->get(i, i) == 0)
		{
			bool error = true;
			for (unsigned int k = i + 1; error && k < matrix->rowsCount(); k++)
			{
				if (matrix->get(k, i) != 0)
				{
					error = false;
					double f1;
					for (unsigned int j = 0; j < matrix->colsCount(); j++)
					{
						f1 = matrix->get(i, j);
						matrix->set(i, j, matrix->get(k, j));
						matrix->set(k, j, f1);
					}
				}
			}
			if(error)
			{
				cout << "��� ������������� �������" << endl;
				return 0;				
			}
		}//����� �������� �� 0
		f = matrix->get(i, i);
		for (unsigned int j = 0; j < matrix->colsCount(); j++)
		{
			matrix->set(i, j, matrix->get(i, j) / f);
		}
		for (unsigned int k = 0; k < matrix->rowsCount(); k++)
		{
			if (k != i)
			{
				double g = matrix->get(k, i);
				for (unsigned int j = 0; j < matrix->colsCount(); j++)
				{
					matrix->set(k, j, -g * matrix->get(i, j) + matrix->get(k, j));//������ ����
				}
			}
		}
	}

	// ����� ���������� �������
	for (unsigned int i = 0; i < matrix->rowsCount(); i++)
	{
		for (unsigned int j = 0; j < matrix->colsCount(); j++)
		{
			cout << matrix->get(i, j) << "  ";
		}
		cout << endl;
	}
	//������� �������

	for (unsigned int i = 0; i < matrix->rowsCount(); i++)
	{
		cout << "x[" << i << "] = " << matrix->get(i, matrix->colsCount() - 1) << " " << endl;
	}
	cout << endl;
	return 0;
}
