#include "iostream"
#include <cmath>
#include <fstream>
using namespace std;

int main()
{
	double A[10][10];

	setlocale(LC_ALL, "rus");

	fstream fs("text.txt");//читаем из файла

	int n;
	fs >> n;

	int m = n + 1;//столбец свободных членов


	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++){
			fs >> A[i][j];
			cout << "  " << A[i][j];
		}
		cout << endl;
	}
	fs.close();
	//Метод Жердана-Гаусса
	//Прямой ход, приведение к верхнетреугольному виду
	int k;
	double  f, f1;
	for (i = 0; i<n; i++)
	{
		// проверка на 0
		if (A[i][i] == 0)
		{
			for (l = i + 1; l<n; l++)
			{
				if (A[l][i] != 0)
				{
					for (t = 0; t<m; t++)
					{
						f1 = A[i][t];
						A[i][t] = A[l][t];
						A[l][t] = f1;
					}
				}
				else{
					cout << "Нет единственного решения" << endl;
					system("pause");
					return 0;
				}
			}
		}//Конец проверки на 0
		f = A[i][i];

		for (j = 0; j<m; j++)
		{
			A[i][j] /= f;
		}
		for (h = 0; h<n; h++)
		{
			if (h != i)
			{

				g = A[h][i];

				for (k = 0; k<m; k++)
				{
					A[h][k] = -g*A[i][k] + A[h][k];//делаем нули

				}

			}
			if (j == i) continue;
		}
	}





	for (int i = 0; i<n; i++)
	{
		for (j = 0; j<m; j++){
			fs >> A[i][j];
			cout << "  " << A[i][j];
		}
		cout << endl;
	}
	//Выводим решение

	for (i = 0; i < n; i++)
		cout << "x[" << i << "] = " << floor(A[i][m - 1] * 1000) / 1000 << " " << endl;
	cout << endl;
	system("pause");
	return 0;
}ю.
