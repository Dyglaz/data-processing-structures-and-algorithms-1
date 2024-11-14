#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
using namespace std;

void Insertion_sort(int n, int* massiv) {
    long long int c_comp = 0, c_perm = 0;
    cout << "Размерность проверяемого массива " << n;
    auto start_time = chrono :: steady_clock :: now();
    for(int i = 0; i < n; i++) { 
        c_comp += 1;                                
        int key = massiv[i];
        int j = i - 1;  
        while(j > 0 && massiv[j] > key) {
            c_comp += 1;  
            c_perm += 1; 
            massiv[j + 1] = massiv[j];
            j--;
        }
        massiv[j + 1] = key;
    }
    auto end_time = chrono :: steady_clock :: now();
    auto interval = chrono :: duration_cast < chrono :: nanoseconds > (end_time - start_time);
    if (n <= 10) {    
        cout << '\n';
        for(int i = 0; i < n; i++) {
            cout << massiv[i] << ' ';
        }
    }
    cout << "\nC = " << c_comp << "; M = " << c_perm << "; C + M = " << c_comp + c_perm << endl;
    cout << "Время компиляции " << interval.count() / pow(10, 6) << " ms\n\n";
}

int* mas_random_gen(int n) {
    int* massiv = new int[n];
    int num = n;
    for (int i = 0; i < n; i++){
        massiv[i] = --num;
    }
    return massiv;
}


int main() {    
    const int n = 10; 
    int massiv_[n];
    cout << "Введите значения массива через пробел \n";
    for(int i = 0; i < n; i++) {
        cin >> massiv_[i];
    }   
    cout << "Проверка программы для рамера массива n = 10 \n(Элементы введены с клавиатуры) \n"; 
    Insertion_sort(n, massiv_);
    
    const int n1 = 100, n2 = 1000, n3 = 10000, n4 = 100000, n5 = 1000000;
    int *massiv1 = mas_random_gen(n1);
    int *massiv2 = mas_random_gen(n2);
    int *massiv3 = mas_random_gen(n3);
    int *massiv4 = mas_random_gen(n4);
    int *massiv5 = mas_random_gen(n5);

    Insertion_sort(n1, massiv1);

    Insertion_sort(n2, massiv2);

    Insertion_sort(n3, massiv3);

    Insertion_sort(n4, massiv4);

    Insertion_sort(n5, massiv5);   


    return 0;
}


