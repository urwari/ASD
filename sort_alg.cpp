// 0qt.1 Алгоритмы сортировок.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include <fstream>

using namespace std;
void view(int *, int*);
void vibor(int *, int*);
void vstavka(int *, int*);
void fast(int *, int, int);
void sliyanie(int*, int, int);
void random_set(int*, int*const);
// Корчагин И. С. ФТ-260008

int main()
{
	setlocale(LC_CTYPE, "rus");
	unsigned int time_start[5];
	unsigned int time_end[5];
	int *N = new int;
	cout << "N:";
	cin >> *N;
	int *m = new int[*N];
	time_start[4] = clock();
	random_set(m, N);
	time_end[4] = clock();
	int *m2 = new int[*N];

	memcpy(m2, m, sizeof(int)*(*N));
	cout << "\nЗапуск сортировки ВЫБОРОМ";
	time_start[0] = clock();
	vibor(m, N);
	time_end[0] = clock();

	memcpy(m, m2, sizeof(int)*(*N));
	cout << "\nЗапуск сортировки ВСТАВКОЙ";
	time_start[1] = clock();
	vstavka(m2, N);
	time_end[1] = clock();
	memcpy(m2, m, sizeof(int)*(*N));
	cout << "\nЗапуск сортировки СЛИЯНИЕМ";
	time_start[2] = clock();
	sliyanie(m, 0, *N);
	time_end[2] = clock();;
	//memcpy(m, m2, sizeof(int)*(*N));
	cout << "\nЗапуск БЫСТРОЙ сортировки";
	time_start[3] = clock();
	fast(m2, 0, *N);
	time_end[3] = clock();
	cout << "\n\t\t---\nРезультаты:\n\tВЫБОРОМ:\t"
		<< time_end[0] - time_start[0]
		<< "ms\n\tВСТАВКОЙ:\t"
		<< time_end[1] - time_start[1]
		<< "ms\n\tСЛИЯНИЕМ:\t"
		<< time_end[2] - time_start[2]
		<< "ms\n\tБЫСТРАЯ:\t"
		<< time_end[3] - time_start[3] << "ms\nСоздание массива: " << time_end[4] - time_start[4] << "ms";
	
	_getch();
	return 0;
}

void view(int *m, int *n) {
	cout << "\n=============================";
	for (int i = 0; i < *n; i++)
		cout << "\n[" << i << "]\t" << m[i];
}
//Сортировка выбором
void vibor(int *m, int *n) {
	for (int j = 0; j < *n - 1; j++) {
		int k = j;
		for (int i = j + 1; i <*n; i++)
			if (m[i] < m[k])
				k = i;
		if (k != j)
			swap(m[k], m[j]);
	}
}
//Сортировка вставками
void vstavka(int *m, int *n) {
	for (int j = 1; j<*n; j++) {
		int i = j;
		while (i>0 && m[i]<m[i - 1]) {
			swap(m[i], m[i - 1]);
			i--;
		}
	}
}

//Быстрая сортировка
void fast(int *m, int p, int n) {
	if (p >= n)
		return;
	int q = p;
	for (int u = p; u <= n - 1; u++)
		if (m[u] <= m[n]) {
			swap(m[q], m[u]);
			q++;
		}
	swap(m[q], m[n]);
	fast(m, p, q - 1);
	fast(m, q + 1, n);
}

// Стортировка слиянием
void sliyanie(int* a, int p, int n){
	if (p >= n)
		return;
	int q = (p + n) / 2;
	sliyanie(a, p, q);
	sliyanie(a, q + 1, n);

	int n1 = q - p + 1;
	int n2 = n - q;
	int* b = new int[n1 + 1];
	int* c = new int[n2 + 1];
	for (int i = 0; i < n1; i++)
		b[i] = a[p + i];
	for (int i = 0; i < n2; i++)
		c[i] = a[q + 1 + i];
	b[n1] = c[n2] = INT32_MAX;
	int i = 0;
	int j = 0;
	for (int k = p; k <= n; k++)
	{
		if (b[i] <= c[j]) {
			a[k] = b[i];
			i++;
		} else {
			a[k] = c[j];
			j++;
		}
	}
}

void random_set(int *m, int *const n) {
	cout << "\n# Инициализация массива";
	srand(time(NULL));
	ofstream fo("log_massiv.txt");
	fo << "N: " << *n;
	for (int i = 0; i < *n; i++) {
		m[i] = rand() % 1000;
		fo << "\n[" << i << "] = " << m[i];
	}
	fo.close();
	cout << "\n# Массив из " << *n << " элементов проинициализирован #" << sizeof(m);
}
