#include <iostream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <random>
#include <iomanip>

/*Разработайте функции для выполнения операции над линейным
двунаправленным динамическим списком:
• создание списка;
• вставку узла;
• удаление узла;
• вывод списка в двух направлениях (слева направо и справа налево);
• поиск узла с заданным значением
*/

/*
    1) Упорядочить список по правилу: сначала проданные, но не возвращенные, а затем возвращенные.
    2) Переформировать список следующим образом: часть списка, содержащая возвращенный товар перенести в начало исходного списка.
    3) Удалить товар, который продан до указанной даты.
*/

/*Код товара (буквенно-цифровой), дата продажи, цена, отметка о возврате, дата возврата.*/

using namespace std;

struct Node {
    Node* next;
    Node* prev;
    string productNumber;
    int daySale;
    int monthSale;
    string price;
    string returnMark;
    string returnDate;
    Node(string _productNumber, int _daySale, int _monthSale, string _price, string _returnMark, string _returnDate) :
    productNumber(_productNumber), daySale(_daySale), monthSale(_monthSale), price(_price),
    returnMark(_returnMark), returnDate(_returnDate), next(nullptr), prev(nullptr) {}
};

struct List {
    Node* first;
    Node* last;
    List() : first(nullptr), last(nullptr) {}
    bool is_empty();
    void push_back(string productNumber, int daySale, int monthSale, string price, string returnMark, string returnDate);
    void push_front(string productNumber, int daySale, int monthSale, string price, string returnMark, string returnDate);
    Node* find(string productNumber);
    void remove(string productNumber);
    void print(bool reverse = false);
    Node* find_date(int dateDelete);
    void delete_item_before_specified_date(int dateDelete);
	void move_noReturned_returned();
    void move_returned_notReturned();

};

bool List::is_empty() {
    return first == nullptr;
}

void List::push_back(string productNumber, int daySale, int monthSale, string price, string returnMark, string returnDate) {
    Node* p = new Node(productNumber, daySale, monthSale, price, returnMark, returnDate);
    if (is_empty()) {
        first = p;
        last = p;
        return;
    }
    p->prev = last;
    last->next = p;
    last = p;
}

void List::push_front(string productNumber, int daySale, int monthSale, string price, string returnMark, string returnDate) {
    Node* p = new Node(productNumber, daySale, monthSale, price, returnMark, returnDate);
    if (is_empty()) {
        first = p;
        last = p;
        return;
    }
    p->next = first;
    first->prev = p;
    first = p;
}

Node* List::find(string productNumber) {
    if (is_empty()) { return nullptr; }
    Node* p = first;
    while (p && p->productNumber != productNumber) p = p->next;
    return (p && p->productNumber == productNumber) ? p : nullptr;
}

void List::remove(string productNumber) {
    if (is_empty()) return;
    if (first == last && first->productNumber == productNumber) {
        delete first;
        first = nullptr;
        last = nullptr;
    }
    else if (first->productNumber == productNumber) {
        Node* p = first;
        first = p->next;
        p->next->prev = nullptr;
        delete p;
        return;
    }
    else if (last->productNumber == productNumber) {
        Node* p = last;
        last = p->prev;
        p->prev->next = nullptr;
        delete p;
        return;
    }
    Node* p = find(productNumber);
    if (p == nullptr) {
        cout << "В списке нет товара с кодом: " << productNumber << endl;
        return;
    }

    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
}

void List::print(bool reverse) {
    Node* p = reverse ? last : first;
    while (p) {
        cout << p->productNumber << " " << p->daySale <<"."<< p->monthSale <<".2022 "<< p->price << " " << p->returnMark << " " << p->returnDate << endl;
        p = reverse ? p->prev : p->next;
    }
}

Node* List::find_date(int dateDelete) {
    if (is_empty()) { return nullptr; }
    Node* p = first;
    int date;
    int day = p->daySale;
    int month = p->monthSale;
    if (month == 1) {
        date = day;
    }
    else {
        date = day + ((month - 1) * 31);
    }
    while (p && date > dateDelete) {
        p = p->next;
        day = p->daySale;
        month = p->monthSale;
        if (month == 1) {
            date = day;
        }
        else {
            date = day + ((month - 1) * 31);
        }
    }
    return (p && date < dateDelete) ? p : nullptr;
}

void List::delete_item_before_specified_date(int dateDelete) {
    if (is_empty()) return;

    int dateF, dateL;
    int dayF = first->daySale;
    int monthF = first->monthSale;
    if (monthF == 1) {
        dateF = dayF;
    }
    else {
        dateF = dayF + ((monthF - 1) * 31);
    }

    int dayL = last->daySale;
    int monthL = last->monthSale;
    if (monthL == 1) {
        dateL = dayL;
    }
    else {
        dateL = dayL + ((monthL - 1) * 31);
    }
    
    if (first == last && dateF < dateDelete) {
        delete first;
        first = nullptr;
        last = nullptr;
    }
    else if (dateF < dateDelete) {
        Node* p = first;
        first = p->next;
        p->next->prev = nullptr;
        delete p;
        return;
    }
    else if (dateL < dateDelete) {
        Node* p = last;
        last = p->prev;
        p->prev->next = nullptr;
        delete p;
        return;
    }
    Node* p = find_date(dateDelete);
    if (p == nullptr) {
        cout << "\nВ списке нет товара, который продан до указанной дате"  << endl;
        return;
    }

    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
}


void List::move_noReturned_returned() {
    if (is_empty()) { return; }
    Node *p = first->next;
    if (first == last) {
        return;
    }
    while (p) {
        if (p->returnMark == "returned") { 
            p = p->next;
            continue;
        }
        if (p == last) {
            last = p->prev;
            last->next = nullptr;
            first->prev = p;
            p->next = first;
            p->prev = nullptr;
            first = p;
            break;
        }
        Node *v = p->next;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        first->prev = p;
        p->next = first;
        first = p;
        first->prev = nullptr;
        p = v;
    }
}

void List::move_returned_notReturned() {
    if (is_empty()) { return; }
    Node *p = first->next;
    if (first == last) {
        return;
    }
    while (p) {
        if (p->returnMark == "notReturned") { 
            p = p->next;
            continue;
        }
        if (p == last) {
            last = p->prev;
            last->next = nullptr;
            first->prev = p;
            p->next = first;
            p->prev = nullptr;
            first = p;
            break;
        }
        Node *v = p->next;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        first->prev = p;
        p->next = first;
        first = p;
        first->prev = nullptr;
        p = v;
    }
}

int main()
{
    setlocale(0, "");
    List L;
    string productNumber, price, returnMark, returnDate;
    int daySale, monthSale, day, month, dateDelete;
    int n, cmd;
    cout << "Введите количество элементов в списке: ";
    cin >> n;
    cout << endl;


    for (int i = 0; i < n; i++) {
        cout << "Введите код товара (буквенно-цифровой), день продажи, месяц продажи, цену, отметку о возврате (returned или not returned), дата возврата (полностью):\n";
        cin >> productNumber >> daySale >> monthSale >> price >> returnMark >> returnDate;
        L.push_front(productNumber, daySale, monthSale, price, returnMark, returnDate);
    }
    cout << endl;

    cout << "Список доступных комманд:" << endl;
    cout << "0) Завершение работы" << endl;
    cout << "1) Добавление узла в начало списка" << endl;
    cout << "2) Добавление узла в конец списка" << endl;
    cout << "3) Удалить узел по ключевому значению" << endl;
    cout << "4) Найти узел по ключевому значению" << endl;
    cout << "5) Вывести список слева направо" << endl;
    cout << "6) Вывести список справа налево" << endl;
    cout << "7) Удалить товар, который продан до указанной даты" << endl;
    cout << "8) Упорядочить список по правилу, где сначала идут проданные, но не возвращённые, а затем возвращённые" << endl;
    cout << "9) Упорядочить список по правилу, где сначала идёт возвращённые товар" << endl;
    cout << "Выберите команду: ";


    while (true) {
        while (true) {
            cin >> cmd;
            if (0 <= cmd && cmd <= 9) break;
            cout << "Неверная команда. Попробуйте снова." << endl;
        }
        switch (cmd) {
        case 0:
            return 0;
        case 1: {
            cout << "Введите код товара (буквенно-цифровой), день продажи, месяц продажи, цену, отметку о возврате (returned или notReturned), дата возврата (полностью):\n";
            cin >> productNumber >> daySale >> monthSale >> price >> returnMark >> returnDate;
            L.push_front(productNumber, daySale, monthSale, price, returnMark, returnDate);
            break;
        }
        case 2: {
            cout << "Введите код товара (буквенно-цифровой), день продажи, месяц продажи, цену, отметку о возврате (returned или notReturned), дата возврата (полностью):\n";
            cin >> productNumber >> daySale >> monthSale >> price >> returnMark >> returnDate;
            L.push_back(productNumber, daySale, monthSale, price, returnMark, returnDate);
            break;
        }
        case 3: {
            cout << "Введите код товара: ";
            cin >> productNumber;
            L.remove(productNumber);
            break;
        }
        case 4: {
            cout << "Введите код товара: ";
            cin >> productNumber;
            Node* tmp = L.find(productNumber);
            if (tmp == nullptr)
                cout << "Указанный товар отсутствует в списке" << endl;
            else
                cout << "Товар найден" << endl;
            break;
        }
        case 5: {
            L.print();
            break;
        }
        case 6: {
            L.print(true);
            break;
        }
        case 7: {
            cout << "Список до удаления товара из списка:\n";
            L.print();
            cout << "\nВведите дату (день и месяц), по которую будет удален товар из списка: ";
            while (true) {
                cin >> day;
                if (day < 31 && day > 0) {
                    break;
                }
                cout << "\nДень введён неправильно, повторите попытку: ";
            }
            while (true) {
                cin >> month;
                if (month < 13 && month > 0) {
                    break;
                }
                cout << "\nМесяц введён неправильно, повторите попытку: ";
            }
            cout << "Введённая дата: " << day << "." << month << "." << "2022" << endl;
            if (month == 1) {
                dateDelete = day;
            }
            else {
                dateDelete = day + ((month - 1) * 31);
            }
            L.delete_item_before_specified_date(dateDelete);
            break;
        }
        case 8: {
            cout << "\nСписок до удаления товара из списка:\n";
            L.print();
            L.move_noReturned_returned();
            cout << "\nСписок после упорядочения:\n";
            L.print();
            break;
        }
        case 9: {
            cout << "\nСписок до удаления товара из списка:\n";
            L.print();
            L.move_returned_notReturned();
            cout << "\nСписок после упорядочения:\n";
            L.print();
            break;
        }
        default:
            break;
        }
        cout << "\nСледующая команда: " << endl;
    }
}