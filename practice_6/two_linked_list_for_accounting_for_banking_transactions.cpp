#include <iostream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <random>
#include <iomanip>
#include <algorithm>

/*Разработайте функции для выполнения операции над линейным
двунаправленным динамическим списком:
• создание списка;
• вставку узла;
• удаление узла;
• вывод списка в двух направлениях (слева направо и справа налево);
• поиск узла с заданным значением*/

/*
    Вставка нового узла перед первым
узлом.
    Удаление сведений по счету (всех узлов), у которого общая сумма
вклада равна нулю (сумма по приходу, минус сумма по расходу).
    Создать новый список из исходного, которого будет содержать остаток по всем видам
операций одного счета, указав вид операции – приход, и текущую дату. */

/*Номер счета в банке (20-значное число), дата, вид операции (приход или расход), сумма вклада.*/
using namespace std;

struct Operation {
    string accountNumber;
    string date;
    string type;
    int amount;
    Operation* next;
    Operation* prev;
    Operation(string _accountNumber, string _date, string _type, int _amount) :
    accountNumber(_accountNumber), date(_date), type(_type), amount(_amount), next(nullptr), prev(nullptr) {}
};

struct List {
    Operation* first;
    Operation* last;
    List() : first(nullptr), last(nullptr) {}
    bool is_empty();
    void push_back(string accountNumber, string date, string type, int amount);
    void push_front(string accountNumber, string date, string type, int amount);
    Operation* find(string accountNumber);
    int count_total_deposit(string accountNumber);
    vector<string> get_accounts_list();
    List make_balance_list();
    void remove_empty_accounts();
    void remove(string accountNumber);
    void print(bool reverse=false);
};

bool List::is_empty() {
    return first == nullptr;
}

void List::push_back(string accountNumber, string date, string type, int amount) {
    Operation* p = new Operation(accountNumber, date, type, amount);
    if (is_empty()) {
        first = p;
        last = p;
        return;
    }
    p->prev = last;
    last->next = p;
    last = p;
}

void List::push_front(string accountNumber, string date, string type, int amount) {
    Operation* p = new Operation(accountNumber, date, type, amount);
    if (is_empty()) {
        first = p;
        last = p;
        return;
    }
    p->next = first;
    first->prev = p;
    first = p;
}

string get_current_date() {
    char buffer[20];
    struct tm buf;
    time_t t = time(NULL);
    std::strftime(buffer, 20, "%Y/%m/%d", localtime(&t));
    return buffer;
}

Operation* List::find(string accountNumber) {
    if (is_empty()) { return nullptr; }
    Operation* p = first;
    while (p && p->accountNumber != accountNumber) p = p->next;
    return (p && p->accountNumber == accountNumber) ? p : nullptr;
}

int List::count_total_deposit(string accountNumber) {
    int total = 0;
    Operation* p = first;
    while (p) {
        if (p->accountNumber == accountNumber)
            total += (p->type == "приход" ? p->amount : -p->amount);
        p = p->next;
    }
    return total;
}

vector<string> List::get_accounts_list() {
    Operation* p = first;
    vector <string> accountsList;
    while (p) {
        if (std::find(accountsList.begin(), accountsList.end(), p->accountNumber) == accountsList.end()) {
            accountsList.push_back(p->accountNumber);
        }
        p = p->next;
    }
    return accountsList;
}

List List::make_balance_list() {
    List result;
    vector <string> accountsList = get_accounts_list();
    for (string accountNumber : accountsList) {
        result.push_front(accountNumber, get_current_date(), "+", count_total_deposit(accountNumber));
    }
    return result;
}

void List::remove_empty_accounts() {
    vector <string> accountsList = get_accounts_list();
    for (string accountNumber : accountsList) {
        if (count_total_deposit(accountNumber) != 0) continue;
        while (find(accountNumber)) {
            remove(accountNumber);
        }
    }
}

void List::remove(string accountNumber) {
    if (is_empty()) return;
    if (first == last && first->accountNumber == accountNumber) {
        delete first;
        first = nullptr;
        last = nullptr;
    }
    else if (first->accountNumber == accountNumber) {
        Operation* p = first;
        first = p->next;
        p->next->prev = nullptr;
        delete p;
        return;
    }
    else if (last->accountNumber == accountNumber) {
        Operation* p = last;
        last = p->prev;
        p->prev->next = nullptr;
        delete p;
        return;
    }
    Operation* p = find(accountNumber);
    if (p == nullptr) {
        cout << "В списке нет элемента со значением " << accountNumber << endl;
        return;
    }

    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
}


void List::print(bool reverse) {
    Operation* p = reverse ? last : first;
    while (p) {
        cout << p->accountNumber << " " << p->date << " " << p->type << " " << p->amount << endl;
        p = reverse ? p->prev : p->next;
    }
}


void testOp() {
    List l;
}

int main()
{
    srand(time(0));
    setlocale(0, "");
    List arr;
    int n;
    int cmd;
    cout << "Введите количество элементов в списке: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        string accountNumber, date, type;
        int amount;
        cout << "Введите номер банковского счета, дату, тип операции и сумму вклада:\n";
        cin >> accountNumber >> date >> type >> amount;
        arr.push_front(accountNumber, date, type, amount);
    }

    cout << "Список доступных комманд:" << endl;
    cout << "0) Завершение работы" << endl;
    cout << "1) Вставить ключ в список" << endl;
    cout << "2) Удалить узел с заданным значением" << endl;
    cout << "3) Найти узел с заданным значением" << endl;
    cout << "4) Вывести список слева направо" << endl;
    cout << "5) Вывести список справа налево" << endl;
    cout << "6) Удалить сведения по счетам с нулевым балансом" << endl;
    cout << "7) Сформировать список, содержащий остаток по всем видам операций" << endl;

    while (true) {
        while (true) {
            cin >> cmd;
            if (0 <= cmd && cmd <= 6) break;
            cout << "Неверная команда. Попробуйте снова." << endl;
        }
        switch (cmd)
        {
        case 0:
            return 0;
        case 1: {
            string accountNumber, date, type;
            int amount;
            cout << "Введите номер банковского счета, дату, тип операции и сумму вклада:\n";
            cin >> accountNumber >> date >> type >> amount;
            arr.push_front(accountNumber, date, type, amount);
            break;
        }
        case 2: {
            string accountNumber;
            cout << "Введите номер банковского счета: ";
            cin >> accountNumber;
            arr.remove(accountNumber);
            break;
        }
        case 3: {
            string accountNumber;
            cout << "Введите номер банковского счета: ";
            cin >> accountNumber;
            Operation* tmp = arr.find(accountNumber);
            if (tmp == nullptr)
                cout << "Данный элемент отсутствует в списке" << endl;
            else
                cout << "Элемент найден" << endl;
            break;
        }

        case 4:
            arr.print();
            break;
        case 5:
            arr.print(true);
            break;
        case 6:
            arr.remove_empty_accounts();
            break;
        case 7: {
            List result = arr.make_balance_list();
            cout << "Получившийся список: " << endl;
            result.print();
        }
        default:
            break;
        }
        cout << "Следующая команда: " << endl;
    }
}