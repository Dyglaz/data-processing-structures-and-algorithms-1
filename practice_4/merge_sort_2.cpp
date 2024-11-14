#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <map>
using namespace std;

bool operator <(string s1, string s2) {
    map <string, int> weekdays = { {"Понедельник" , 1}, {"Вторник" , 2}, {"Среда" , 3}, {"Четверг" , 4}, {"Пятница" , 5}, {"Суббота" , 6}, {"Воскресенье" , 7} };
    if (weekdays[s1] < weekdays[s2]) {
        return true;
    }
    return false;
}

bool operator <=(string s1, string s2) {
    map <string, int> weekdays = { {"Понедельник" , 1}, {"Вторник" , 2}, {"Среда" , 3}, {"Четверг" , 4}, {"Пятница" , 5}, {"Суббота" , 6}, {"Воскресенье" , 7} };
    if (weekdays[s1] <= weekdays[s2]) {
        return true;
    }
    return false;
}

bool operator >(string s1, string s2) {
    map <string, int> weekdays = { {"Понедельник" , 1}, {"Вторник" , 2}, {"Среда" , 3}, {"Четверг" , 4}, {"Пятница" , 5}, {"Суббота" , 6}, {"Воскресенье" , 7} };
    if (weekdays[s1] > weekdays[s2]) {
        return true;
    }
    return false;
} 

struct student {
    string group = "";
    string discipline = "";
    string view = "";
    string office = "";
    string weekdays = "";
    int number = 0;
};

ifstream& operator>>(ifstream& in, student& st) {
    in >> st.group >> st.discipline >> st.view >> st.office >> st.weekdays >> st.number;
    return in;
}

ofstream& operator<<(ofstream& out, student& st) {
    out << st.group << " " << st.discipline << " " << st.view << " " << st.office << " " << st.weekdays << " " << st.number;
    return out;
}


void split(int p) { // Алгоритм разделения для простого слияния
    ifstream a("A.txt");
    ofstream b("B.txt"), c("C.txt");
    student x;
    a >> x;
    while(!a.eof()) {
        for (int i = 0; !a.eof() && i < p; i++) {
            b << x << endl;
            a >> x;
        }
        for (int i = 0; !a.eof() && i < p; i++) {
            c << x << endl;
            a >> x;
        }
    }
    a.close(); b.close(); c.close();
}

bool nat_split() { // Алгоритм разделения для естественного слияния
    ifstream a("A.txt");
    ofstream b("B.txt"), c("C.txt");
    student x, y;
    bool c_empty = true;
    a >> y;
    while (!a.eof()) {
        do {
            x = y;
            b << x << endl;
            a >> y;
        } while (x.weekdays <= y.weekdays && !a.eof());
        if (a.eof()) { 
            if (c_empty) {
                b << y << endl;
                a.close(); b.close(); c.close();
                return false;
            }
        }
        else {
            do {
                c_empty = false;
                x = y;
                c << x << endl;
                a >> y;
            } while (x.weekdays <= y.weekdays && !a.eof());
        }
    }
    a.close(); b.close(); c.close();
    return true;
}

void merge(int p) { // Алгоритм слияния для простого слияния
    ofstream a("A.txt");
    ifstream b("B.txt"), c("C.txt");
    student x, y;
    b >> x;
    c >> y; 
    while (!b.eof() && !c.eof()) {
        int i = 0, j = 0;
        while (!b.eof() && !c.eof() && i < p && j < p) {
            if (x.weekdays < y.weekdays) {
                a << x << endl;
                b >> x;
                i++;
            }
            else {
                a << y << endl;
                c >> y;
                j++;
            }
        }
        while (!b.eof() && i < p) {
            a << x << endl;
            b >> x;
            i++;
        }
        while (!c.eof() && j < p) {
            a << y << endl;
            c >> y;
            j++;
        }
    }
    while (!b.eof()) {
        a << x << endl;
        b >> x;
    }
    while (!c.eof()) {
        a << y << endl;
        c >> y;
    }
    a.close(); b.close(); c.close();
}

void nat_merge() { // Алгоритм слияния для естественного слияния
    ofstream a("A.txt");
    ifstream b("B.txt"), c("C.txt");
    student x1, x2, y1, y2;
    b >> x1;
    c >> y1;
    while (!b.eof() && !c.eof()) {
        if (x1.weekdays < y1.weekdays) {
            a << x1 << endl;
            b >> x2;
            if (!b.eof() && x1.weekdays > x2.weekdays) {
                a << y1 << endl;
                c >> y2;
                while (!c.eof() && y1.weekdays <= y2.weekdays) {
                    y1 = y2;
                    a << y1 << endl;
                    c >> y2;
                }
                y1 = y2;
            }
            x1 = x2;
        }
        else {
            a << y1 << endl;
            c >> y2;
            if (!c.eof() && y1.weekdays > y2.weekdays) {
                a << x1 << endl;
                b >> x2;
                while (!b.eof() && x1.weekdays < x2.weekdays) {
                    x1 = x2;
                    a << x1 << endl;
                    b >> x2;
                }
                x1 = x2;
            }
            y1 = y2;

        }
    }
    while (!b.eof()) {
        a << x1 << endl;
        b >> x1;
    }
    while (!c.eof()) {
        a << y1 << endl;
        c >> y1;
    }
    a.close(); b.close(); c.close(); 
}

void merge_sort(int n /*Количество записей*/) { // Сортировка простого слияния
    for (int p = 1; p < n; p *= 2) {
        split(p);
        merge(p);
    }
}

void nat_merge_sort() { // Cортировка естесвенного слияния
    while (nat_split()) {
        nat_merge();
    }
}

int main()
{
    setlocale(0, "");
    int n = 32;
    auto start = chrono::high_resolution_clock::now();
    //merge_sort(n);
    nat_merge_sort();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> du = end - start;
    cout << "Время выполнения " << du.count() << " s " << endl;
}
