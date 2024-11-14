#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
using namespace std;

/*Дан линейный однонаправленный список L
1. Разработать функцию, которая вставляет перед последним уз-лом два новых узла.
2. Удаляет из списка L первое отрицательное значение, если оно присутствует в списке.
3. Найти в списке L максимальное значение и перенести его узел в конец списка.*/

/*1. Информационная часть узла определена вариантом
2. Разработать функции вставки нового узла перед первым узлом и удаления узла по ключу.
3. Реализуйте возможность а) создания нового списка вручную, а также
б) использования уже готового списка для тестирования заданий индивидуального варианта.
4. Разработать функцию вывода списка в консоль.
5. Разработать функции согласно индивидуальному варианту. При необходимости можно добавлять вспомогательные функции, декомпозируя задачу.
6. Реализуйте текстовое пользовательское меню.
7. В основной программе выполните тестирование каждой функции
(пункты 2-5).*/


struct Node {   // Структура узла списка
    double val; // Информационная строка данных
    Node* next; // Связь
    Node(double _val) : val(_val), next(nullptr) {} // Конструктор экземпляра узла списка
};

struct list {                   // Список
    Node* first;                // Указатель на первый узел
    Node* last;	                // Указатель на последний узел
    list() : first(nullptr), last(nullptr) {} // Конструктор списка

    bool is_empty();            // Метод проверки наличия узлов в списке
    void push_back(double val); // Метод добавления узла в конец списка
    void push_front(double val);// Метод добавления узла в начало списка
    Node* find(double val);     // Метод поиска узла в списке по ключу
    void remove_first();        // Метод удаления первого узла 
    void remove_last();         // Метод удаления последнего узла 
    void remove(double val);    // Метод удаления узла по ключу
    void print();               // Метод печати списка
    void remove_negative();     // Метод удаления первого отрицательного элемента 
    void moveMaxtoEnd();        // Метод перемещения максимального элемента в конец списка
};

bool list::is_empty() { // Метод проверки наличия узлов в списке
    return first == nullptr;
}

void list::push_back(double val) { // Метод добавления узла в конец списка
    Node* temp = new Node(val);
    if (is_empty()) {
        first = temp;
        last = temp;
        return;
    }
    last->next = temp;
    last = temp;
}

void list::push_front(double val) { // Метод добавления узла в начало списка
    Node* temp = new Node(val);
    if (is_empty()) {
        first = temp;
        last = temp;
        return;
    }
    temp->next = first;
    first = temp;
}

Node* list::find(double _val) { // Метод поиска узла в списке по ключевому значению
    Node* temp = first;
    while (temp && temp->val != _val) temp = temp->next;
    if (temp == nullptr) {
        cout << "Нет узла с указанным ключевым значением\n";
    }
    else {
        cout << "Есть узел с указанным ключевым значением\n";
    }
    return (temp && temp->val == _val) ? temp : nullptr;
}

void list::remove_first() { // Метод удаления первого узла в списке
    Node* temp = first;
    first = temp->next;
    delete temp;
}

void list::remove_last() { // Метод удаления последнего узла в списке
    if (first->next == nullptr) {
        delete first;
        first = nullptr;
        last = nullptr;
        return;
    }
    Node* temp = first;
    while (temp->next->next != nullptr) temp = temp->next;
    delete last;
    last = temp;
    temp->next = nullptr;

}

void list::remove(double val) { // Метод удаления узла по ключевому значению в списке
    if (is_empty()) return;
    if (first->val == val) {
        remove_first();
        return;
    }
    else if (last->val == val) {
        remove_last();
        return;
    }
    Node* slow = first;
    Node* fast = first->next;
    while (fast && fast->val != val) {
        fast = fast->next;
        slow = slow->next;
    }

    if (fast == nullptr) {
        cout << "Узел не существует" << endl;
        return;
    }

    slow->next = fast->next;
    delete fast;
}

void list::print() { // Метод печати списка
    if (is_empty()) return;
    Node* temp = first;
    while (temp) {
        cout << setw(5);
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
}

void list::remove_negative() { // Метод удаления первого отрицательного узла в списке
    if (is_empty()) return;
    Node* temp = first;
    while (temp) {
        if(temp->val < 0) {
            break;
        }
        temp = temp->next;
    }
    if (temp) {
        if (temp->val < 0) remove(temp->val);
    }
}

void list::moveMaxtoEnd() { // Метод перемещения узла с максимальным значением в конец списка
    if (is_empty()) return;
    Node* temp = first;
    double max = -10000000;
    while (temp) {
        if (temp->val > max) {
            max = temp->val;
        }
        temp = temp->next;
    }
    temp = first;
    if (first == last) {
        return;
    }
    else if (first->val == max) {
        first = first->next;
        temp->next = nullptr;
        last->next = temp;
        last = last->next;
        return;
    }
    else if (last->val == max) {
        return;
    }
    Node* slow = first;
    Node* fast = first->next;
    while (fast && fast->val != max) {
        fast = fast->next;
        slow = slow->next;
    }
    slow->next = fast->next;
    fast->next = nullptr;
    last->next = fast;
    last = last->next;
}

void write_menu_start() {
	string start_menu;
    
    start_menu += "1 - Создать список вручную\n";
    start_menu += "2 - Готовый спискок\n";

    cout << start_menu;
}
void write_menu() {
	string menu = "Список команд:\n";
	menu += "3 - Добавить узел в начало\n";		
	menu += "4 - Удаление узла по ключу\n";		
    menu += "5 - Вывести список на экран\n";		
	menu += "6 - Добавление двух узлов в конец\n";	
    menu += "7 - Найти первое вхождение отрицательного значения узла и удалить его\n";
    menu += "8 - Найти макисмальное значение узла и поместить в конец списка\n";
    menu += "9 - Проверить список на пустоту\n";
    menu += "10 - Добавить узел в конец списка\n";
    menu += "11 - Поиск узла в списке по ключевому значению\n";
    menu += "12 - Удаление первого узла списка\n";
    menu += "13 - Удаление последнего узла списка\n";
	menu += "0 - Выход из программы\n";

	cout << menu;
}

int get_command() {
	int command;
	cout << "Новая команда: " << endl;
	cin >> command;
	return command;
}

int main() {
    int n = 10, command_start, command;
    double number, number2;

    list L;

    cout << "\nКоманды:\n";

    write_menu_start();

	cout << "\nВыбранная команда:\n";
	cin >> command_start;

    if (command_start == 1) {
        cout << "Введите 10 элементов списка:\n";
        for (int i = 0; i < 10; i++) {
            double num;
		    cin >> num;
            L.push_back(num);
        }
    }
    else if (command_start != 1) {
        for (int i = 0; i < 10; i++) {
            double num;
		    num = rand() % 70;
            L.push_back(num);
        }
        cout << "Ваш список\n";
        L.print();
    }

	write_menu();

	cout << "\nВыбранная команда:\n";
	cin >> command;

	while (command != 0) {
		switch (command) {
		case 3:
			cout << "Введите новое значение узла:\n";
			cin >> number;
            cout << "Лист всех значений узлов до изменений:\n";
            L.print();
            cout << "Полученный список после изменений\n";
            L.push_front(number);
            L.print();
			break;
		case 4:
			cout << "Введите ключевое значение, по которому будет удаляться узел:\n";
			cin >> number;
            cout << "Лист всех значений узлов до изменений:\n";
			L.print();
            L.remove(number);
            cout << "Полученный список после изменений\n";
            L.print();
			break;
		case 5:
            cout << "Список:\n";
            L.print();
			break;
		case 6:
            cout << "Введите новое значение узла:\n";
            cin >> number;
            L.push_back(number);
            cout << "Введите ещё одно новое значение узла:\n";
            cin >> number2;
            L.push_back(number2);
            cout << "Список:\n";
            L.print();
			break;
        case 7:
            cout << "Лист всех значений узлов до изменений:\n";
			L.print();
            L.remove_negative();
			cout << "Лист всех значений узлов после измененения:\n";
			L.print();
            break;
        case 8:
            cout << "Лист всех значений узлов до изменений:\n";
            L.print();
			L.moveMaxtoEnd();
            cout << "Лист всех значений узлов после измененения:\n";
            L.print();
			break;
        case 9:
            cout << "Лист всех значений узлов до изменений:\n";
            L.print();
            L.is_empty();
            if (L.first == nullptr) {
                cout << "Список пустой\n";
            }
            else {
                cout << "Список не пустой\n";
            }
            break;
        case 10:
            cout << "Введите новое значение узла:\n";
            cin >> number;
            cout << "Лист всех значений узлов до изменений:\n";
            L.print();
            L.push_back(number);
            cout << "Полученный список после изменений\n";
            L.print();
            break;
        case 11:
            cout << "Введите ключевое значение, по которому будет происходить поиск узла в списке:\n";
            cin >> number;
            L.find(number);
            break;
        case 12:
            cout << "Лист всех значений узлов до изменений:\n";
            L.print();
            cout << "Полученный список после изменений\n";
            L.remove_first();
            L.print();
            break;
        case 13:
            cout << "Лист всех значений узлов до изменений:\n";
            L.print();
            cout << "Полученный список после изменений\n";
            L.remove_last();
            L.print();
            break;
		default:
			break;
		}
		command = get_command();
	}
    return 0;
}