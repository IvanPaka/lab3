#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;


double lagrange(double* x, double* y, int n, double a){
	double result = 0;
	for (int i = 0; i < n; i++)
	{
		double P = 1;
		for (int j = 0; j < n; j++)
			if (j != i)
				P *= (a - x[j])/ (x[i] - x[j]);

		result += P * y[i];
	}
	return result;
}

int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

double kr(double* y, int i, int n){
	if(!n)
		return y[i];
	else
		return kr(y, i+1, n-1) - kr(y, i, n-1);
}

double newton1(double* x, double* y, int n, double a){
	double p = 0;
	double q = 1;
	for(int i = 0; i < n; i++){
		p += kr(y, 0, i)*q/factorial(i);
		q *= (a - x[i]);
	}
	return p;
}

double newton2(double* x, double* y, int n, double a){
	double p = y[n-1];
	double q = a - x[n-1];
	int j = 1;
	for(int i = n-1; i > -1; i--){
		p += kr(y, i, j)*q/factorial(j);
		q *= a - x[i];
		j++;
	}
	return p;
}

double appr(vector<double> appr_x, vector<double> appr_y, double* x, double** a, int m, int n){
    
	
	for(int i = 0; i < m; i++){
		for(int j = i; j < m+i; j++){
			double s = 0;
			for(int k = 0; k < n; k++)
				s += pow(appr_x[k], j);
			a[i][j-i] = s;
		}
		double s = 0;
		for(int l = 0; l < n; l++)
			s += appr_y[l]*pow(appr_x[l], i);
		a[i][m] = s;
	}
	
	for(int k = 1; k < m; k++){
		for(int j = k; j < m; j++){
			double h = a[j][k-1]/a[k-1][k-1];
			for(int i = 0; i < m+1; i++)
				a[j][i] -= h*a[k-1][i];
		}
		for(int i = m-1; i >= 0; i--){
			x[i] = a[i][m]/a[i][i];
			for(int c = m-1; c > i; c--)
				x[i] -= a[i][c]*x[c]/a[i][i];
		}
	}
}

int main(){

	double data[154][14];
    // Создаем файловый указатель
    fstream fin;

    // Открываем существующий файл
    fin.open("21.csv", ios::in);

    string line, word, temp;

    // Пропускаем заголовок (первую строку без данных)
    getline(fin, line);
    int k = 0;
    while (!fin.eof()) {
        // Считываем строку целиком и сохраняем её в строковой переменной 'line'
        getline(fin, line);
        // Будем использовать stringstream для того, чтобы разбить строку на элементы (слова)
        stringstream s(line);

        // Считываем каждый элемент строки (слово) и сохраняем его в строковой переменной 'word'

		int l = 0;
        while (getline(s, word, ',')) {
			data[k][l] = stod(word);
			l++;
        }
		k++;
    }
	
	fstream outf;
	
	vector<double> appr_x;
	vector<double> appr_y;
	double j = 0;
	for(int i = 0; i < 154; i++){
		if(data[i][8] < 999){
			appr_y.push_back(data[i][8]);
			appr_x.push_back(j);
			j++;
		}
	}
    
    outf.open("./data_lagr.csv", ios_base::out);
	double lagr_y[12];
	double lagr_x[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	for(int i = 0; i < 12; i++){
		lagr_y[i] = data[i+44][6];
	}
	while(outf.is_open()){
		for(int i = 0; i < 111; i++){
		 	outf << 0.1*i << "," << lagrange(lagr_x, lagr_y, 12, 0.1*i) << endl;
		}
		break;
	}
	outf.close();
	
	outf.open("./data_n1.csv", ios_base::out);
	double n1_y[6];
	double n1_x[6] = {0, 1, 2, 3, 4, 5};
	for(int i = 0; i < 6; i++){
		n1_y[i] = data[i+44][6];
	}
	while(outf.is_open()){
		for(int i = 0; i < 51; i++)
		 	outf << 0.1*i << "," << newton1(n1_x, n1_y, 6, 0.1*i) << endl;
		break;
	}
	outf.close();
	
	outf.open("./data_n2.csv", ios_base::out);
	double n2_y[6];
	double n2_x[6] = {0, 1, 2, 3, 4, 5};
	for(int i = 0; i < 6; i++){
		n2_y[i] = data[i+49][6];
	}
	while(outf.is_open()){
		for(int i = 0; i < 51; i++)
		 	outf << 0.1*i << "," << newton2(n2_x, n2_y, 6, 0.1*i) << endl;
		break;
	}
	outf.close();
	int n = appr_x.size();
	const int m = 5;
	
    double **a = new double*[m];
    for(int i = 0; i < m; i++)
        a[i] = new double[m+1];
    
    double x[m] = {0};
    appr(appr_x, appr_y, x, a, m, n);
	outf.open("./data_appr.csv", ios_base::out);
    
	while(outf.is_open()){
		for(int i = 0; i < n; i++){
			double p = 0;
			for(int j = 0; j < m; j++)
				p += x[j]*pow(appr_x[i], j);
			outf << appr_x[i] << "," << appr_y[i] << "," << p << endl;
		}
		break;
	}
	outf.close();
	return 0;
}