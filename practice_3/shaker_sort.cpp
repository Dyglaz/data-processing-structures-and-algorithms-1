#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
using namespace std;

int *mass_rand(int n) // функция случайного заопления массива 
{
    int *mass = new int[n];
    for (int i = 0; i < n; i++)
    {
        // int num = rand() % 10 + 1;
        mass[i] = i;
    }
    return mass;
}

void shakerSort(int *mass, int size, long long int* comp, long long int* per) // функция шейкерной сортировки 
{
    int low = 0, up = size-1;
    int last, tmp;
    comp++;
    while (low < up) {
        comp++;
        last = -1;
        comp++;
        for (int i = low; i < up; i++) {
            comp++;
            comp++;
            if (mass[i] > mass[i + 1]) {
                tmp = mass[i];
                mass[i] = mass[i + 1];
                mass[i + 1] = tmp;
                per += 2;
                last = i;
            }
        }
        up = last;
        comp++;
        if (last == -1) break;
        last = size;
        comp++;
        for (int i = up - 1; i >= low; i--) {
            comp++;
            comp++;
            if (mass[i] > mass[i + 1]) {
                tmp = mass[i];
                mass[i] = mass[i + 1];
                mass[i + 1] = tmp;
                per += 2;
                last = i;
            }
        }
        low = last + 1;
    }
}

void Vivod_time(int n, int *mass) // функция вывода времени компиляции, компилиции и перемещения
{
    long long int comp = 1, per = 1;
    cout << "Размер проверяемого массива = " << n;

    auto start_time = chrono ::steady_clock ::now();
    shakerSort(mass, n, &comp, &per);
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
    cout << "\nC = " << comp << "; per = " << per << "; comp + per = " << comp + per << endl;
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

