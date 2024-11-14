#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
using namespace std;

void merge(int* arr, int left, int mid, int right, long long int* C, long long int* M) { // функция слияния двух массивов 
    int siz1 = mid - left + 1;
    int siz2 = right - mid;
    *M += 2;

    int *leftArr = new int[siz1], *rightArr = new int[siz2];
    *M += 2;

    for (int i = 0; i < siz1; i++) {
        *C+=1;
        leftArr[i] = arr[left + i];
        *M+=1;
    }
    for (int j = 0; j < siz2; j++) {
        *C+=1;
        rightArr[j] = arr[mid + 1 + j];
        *M+=1;
    }

    int i, j, k;
    i = 0;
    j = 0;
    k = left;
    *M += 3;

    while (i < siz1 && j < siz2) {
        *C += 2;
        *C+=1;
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            *M+=1;
            i++;
        }
        else {
            arr[k] = rightArr[j];
            *M+=1;
            j++;
        }
        k++;
    }
    *C+=1;

    while (i < siz1) {
        *C+=1;
        arr[k] = leftArr[i];
        *M+=1;
        i++;
        k++;
    }
    *C+=1;
    while (j < siz2) {
        *C+=1;
        arr[k] = rightArr[j];
        *M+=1;
        j++;
        k++;
    }
    *C+=1;
    delete[] leftArr, rightArr;
}


void SortMerge (int* arr, int right, int left, long long int* C, long long int* M) { // функция сортировки 
    *C+=1;
    if (left < right) {
        int mid = (right + left) / 2;
        *M+=1;
        SortMerge(arr, mid, left, C, M);
        SortMerge(arr, right, mid + 1, C, M);
        merge(arr, left, mid, right, C, M);
    }
}


int *mass_rand(int n) // функция случайного заопления массива 
{
    int *mass = new int[n];
    for (int i = 0; i < n; i++)
    {
        // int num = rand() % 10 + 1;
        mass[i] = n - i;
    }
    return mass;
}

void Vivod_time(int n, int *mass) // функция вывода времени компиляции, компилиции и перемещения
{
    long long int comp = 1, per = 1;
    cout << "Размер проверяемого массива = " << n;

    auto start_time = chrono ::steady_clock ::now();
    SortMerge(mass, n - 1, 0, &comp, &per);
    auto end_time = chrono ::steady_clock ::now();
    auto interval = chrono ::duration_cast<chrono ::nanoseconds>(end_time - start_time);
    if (n <= 10)
    {
        cout << '\n';
        for (int i = 0; i < n; i++)
        {
            cout << mass[i] << ' ';
        }
    }
    cout << "\nC = " << comp << "; M = " << per << "; C + M = " << comp + per << endl;
    cout << "Время компиляции " << interval.count() / pow(10, 6) << " ms\n\n";
}

int main() // мейн :)
{
    const int n = 10;
    int mass0[n];
    cout << "Введите значения массива через пробел \n";
    for (int i = 0; i < n; i++)
    {
        cin >> mass0[i];
    }
    cout << "Проверка программы для рамера массива n = 10 \n(Элементы введены с клавиатуры) \n";

    Vivod_time(n, mass0);

    const int n1 = 100, n2 = 1000, n3 = 10000, n4 = 100000, n5 = 1000000;
    int *mass1 = mass_rand(n1);
    int *mass2 = mass_rand(n2);
    int *mass3 = mass_rand(n3);
    int *mass4 = mass_rand(n4);
    int *mass5 = mass_rand(n5);

    Vivod_time(n1, mass1);
    Vivod_time(n2, mass2);
    Vivod_time(n3, mass3);
    Vivod_time(n4, mass4);
    Vivod_time(n5, mass5);

    return 0;
}