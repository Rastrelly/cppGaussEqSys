#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main() {
	int n, m;

	//make array
	ifstream f("matrix.txt");
	f >> n;
	m = n + 1;                  //Ext matrix
	double **A = new double *[n + 1]; //Memory for rows
	for (int i = 1; i <= n; i++)
		A[i] = new double[m + 1];    //Memory for columns
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			f >> A[i][j];
		}
	}
	f.close();

	//Output
	cout << "Matrix A: " << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
	cout << endl;

/*GAUSS*/
/*---------------------------------Direct----------------------------------*/

	double tmp;
	double *x = new double[n + 1];
	for (int k = 1; k < n; k++) 
	{
		for (int i = k + 1; i <= n; i++)
		{
			tmp = A[i][k] / A[k][k];
			for (int j = m; j >= k; j--) //Count from last element in a row
				A[i][j] -= tmp * A[k][j]; //
		}
	}

	cout << "Matrix after direct pass: " << endl;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (abs(A[i][j]) < 0.000001) A[i][j] = 0.0f;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
	cout << endl;

	/*-------------------------------Reverse-------------------------------*/


	x[n] = A[n][m] / A[n][n];
	for (int i = n - 1; i >= 1; i--) {
		x[i] = A[i][m];
		for (int j = i + 1; j <= n; j++)
			x[i] -= A[i][j] * x[j];
		x[i] = x[i] / A[i][i];
	}

	for (int i = 1; i <= n; i++)
		if (abs(x[i]) < 0.00000001) x[i] = 0.0f;


	/*-------------------------------Solution output-------------------------------*/
	cout << "Result:" << endl;
	for (int i = 1; i <= n; i++)
		cout << x[i] << " ";
	cout << endl;

	ofstream out("answer.txt");
	for (int i = 1; i <= n; i++)
	{
		out << x[i] << ' ';
	}

	out.close();
	delete[] A;
	return 0;
}