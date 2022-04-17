/*
	Реализовать работу с элементами односвязного списка
*/

//#include<list>
#include <iostream>
using namespace std;

struct node {
	int data;	// Поле данных в списке
	struct node*next;	// Указатель на следующий элемент
};

void push_back( node**head,int new_data) {
	node* new_node = new node; // Создаём новый узел
	new_node->data = new_data; // Данные нового узла заполняем переменной, которую принимаем в параметры функции
	new_node->next = NULL; // Указатель на следубщий элемент пока оставим пустым
	if (*head != NULL) {	// Если в списке есть елементы

		node* current; // Создаём ссылку на текущий элемент
		current = *head; // Текущий делаем первым элементом в списке
		while (current->next!=NULL) { // Пока следующий элемент существует
			current = current->next; // Переходим к следующему
		}
		current->next = new_node; // После того как перебрали все элементы добавляем в конец новый элемент
	}
	else {
		*head = new_node; // Или создаём новый узел в начале списка, если элементов не было
	}
}

void print(node** head) {
	node* current;
	current = *head;
	cout << "Все элементы списка:\n ";
	if (current == NULL)
		cout << "Список пуст" << endl;
	else {
		while (current != nullptr) {
			cout << current->data<<" ";
			current = current->next;
		}
	}
}


void after_even(int new_data, node **head) {
	bool avalability_even;
	node* current;
	current = *head;// current-тукущий узел,он равен указателю на первый элемент

	if (*head != NULL) {
		while (current != NULL) {
			if (current->data % 2 == 0) {//если поле данных текущего элемента четное 
				node* new_node = new node;
				new_node->data = new_data;
				new_node->next = current->next;
				current->next = new_node;//то следующий узел равен новому добовляемогу узлу
				avalability_even = true;
				break;
			}
			current = current->next;
		}
		if (avalability_even == false) cout << "Нет четных элементов  в списке.\n ";
	}
	else cout<<"Список пуст" << endl;
}



void before_even(int new_data, node** head) {
	bool avalability_even; // Переменая для проверки на начичие чётных
	node* current;	// Создаём указатель на текущий элемент
	node* changeable; // И указатель на изменяемый
	
	if (*head != NULL) { // Если список не пуст

		current = *head; // Текущий равен первому элементу в списке 
		if (current->data % 2 == 0) { // Если первый элемент списка чётный
			node* new_node = new node; // Создаём новый узел
			new_node->data = new_data;
			new_node->next = current; // Указатель на следующий будет равен текущему
			*head = new_node; // Первый элемент в списке становится ноым узлом
			changeable = *head; // Изменяемый также - первому
		}
		else { // Если первый - нечётный
			changeable = *head; // Изменяемый равен первому
			while (current != NULL) { // Пока существует ссылка на текущий элемент
				if (current->data % 2 != 0) { // Если после данных равно нечётному числу 
					current = current->next; // Переходим к следующему элементу

					if (current->data % 2 != 0) { // Если текущий также является нечётным (на данный момент он следующий для изменяемого)
						changeable = changeable->next; // Также делаем изменяемый следующим
					}
				}
				else { // Если следующий для текущего равен чётному
					node* new_node = new node; // Создаём новый узел
					new_node->data = new_data;
					new_node->next = changeable->next; // Помещаем его на позицию после изменяемого (перед текущим)
					changeable->next = new_node; // Изменяемый ссылается на новый
					avalability_even = true; // Чётный жлемент в списке существует
					break; // Выходим из цикла
				}
			}
			if (avalability_even == false) cout << "Нет четных элементов  в списке.\n ";
		}		
	}
	else cout << "Список пуст" << endl;
}

// Удаляем каждый чётный
void delete_each_even(node** head) {
	if (*head != NULL) {
		node* current = *head;

		while (current->data % 2 == 0) { // Проверяем первый элемент в списке. Если первый - чётный.
			*head = current->next;	//  Делаем первый следующим
			if (current->next != nullptr) 
				current = current->next;
			else { // Если в нашем списке добавлены только чётные элементы, то мы не можем сделать первый следующим, так как все элементы удалены (пропущены)
				*head = NULL; // Первый элемент делаем равным NULL, так как в списке у нас только чётные элементы
				break; // Выходим из цикла
			}
		}

		while (current->next != nullptr) { // Пока следующий не равен nullptr (текущий - последний элемент)
			if (current->next->data % 2 == 0) { // Если данные следующего чётные 
				node* temp = current->next; // Создаём временный элемент равный чётному
				if (temp->next != nullptr)  // Если следующий после временного существует
					current->next = temp->next; // Изменяем ссылку следующего на послеследующий
				else 
					current->next = nullptr; // В противном случае текущий становится последним элементом в списке
				delete temp; // Удаляем временный.
			}
			else current = current->next; // Если следующий нечётный, переходим к нему
		}
	}
	else cout << "Список пуст" << endl; // Если первый элемент списка равен NULL
}

void sum_all_even(node** head) {

	int sum = 0;
	node* current;
	current = *head;
	if (current == NULL) 
		cout << "Список пуст" << endl;
	else {
		cout << "Сумма всех чётных элементов списка: ";
		while (current != nullptr) {
			if (current->data % 2 == 0) 
				sum += current->data;
			current = current->next;
		}
	}
	cout << sum << endl;
}

void del_before_even(node** head) {
	if (*head != NULL) {
		node* current = *head;
		node* temp = current->next;

		if (current->next->data % 2 == 0) {
			while (current->next->data % 2 == 0) {
				*head = current->next;
				current = current->next;
				temp = current->next;
			}
		}

		while (current->next->next != nullptr) {

			if (current->next->next->data % 2 == 0) {
				node* temp = current->next;
				current->next = temp->next;
				delete temp;
			}
			else {
				current = current->next;
				temp = temp->next;
			}
		}
	}
	else cout << "Список пуст" << endl; // Если первый элемент списка равен NULL
}

int main() {
	setlocale(LC_ALL, "");
	int choice =0;
	int new_element = 0;
	node** head = new node*;
	*head = NULL;
	cout << "Выберите действие:";
	do {
		cout << "\n1) Вывод всех элементов списка ";
		cout << "\n2) Добавление элемента в конец списка";
		cout << "\n3) Добавление элемента после первого четного элемента; ";
		cout << "\n4) Добавление элемента перед первым четным элементом; ";
		cout << "\n5) Удаление всех четных элементов списка; ";
		cout << "\n6) Нахождение суммы четных элементов списка";
		cout << "\n7) Удаление элемента перед каждым четным";
		cout << "\n0) Завершение работы;\n ";
		cin >> choice;

		switch (choice) {
		case 1:
			print(head);
			break;
		case 2:
			cout << "Введите добаляемый элемент: ";
			cin >> new_element;
			push_back(head, new_element);
			break;
		case 3:
			cout << "Введите добаляемый элемент: ";
			cin >> new_element;
			after_even(new_element, head);
			break;
		case 4:
			cout << "Введите добаляемый элемент: ";
			cin >> new_element;
			before_even(new_element, head);
			break;
		case 5:
			delete_each_even(head);
			break;
		case 6:
			sum_all_even(head);
			break;
		case 7:
			del_before_even(head);
			break;
		}
	} while (choice != 0);
	return 0;
}