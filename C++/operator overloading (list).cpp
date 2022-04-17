#include <iostream>
#include <windows.h>
/*
Задание:
	Определить класс список элементов.
	В определение класса включить два конструктора для определения списка по его размеру и путем копирования другого списка.
	Определить операции над списком: + конкатенация двух списков; & формирование нового списка из двух списков так, 
	что каждый элемент информационного поля нового списка удовлетворяет условию: с = (а > b ) ? a : b
*/

using namespace std;

template<typename T>
class List {

  public:

	List(); // Вызов конструктора списка в классе

	// Объявление и реализация конструктора копирования
	template<typename T>
	List (List <T> &other) {
		this->data = other.data;
		this->ptr_next = other.ptr;
	}
	
	~List(); // Вызов деструктора списка в классе

	void push_back(T data); // Вызов функции добавления элемента

	//void print_list();

	int get_list_size() { return (int)size; } // Метод для вывода размера списка (геттер)

	T& operator[](const int index); // Прототип (вызов) функции оператора итерирования
	
	template<typename T>
	// Объявление и реализация оператора присваивания
	List& operator=(const List<T> &other) {
		if (this->data != nullptr) {
			delete[] this-> data;
		}
	
		this->data = other.data;
		this->ptr_next = other.ptr;
		return* this;
	}
	
	List<T>& operator+(const List<T> & other);

	List<T>& operator&(const List<T>& other);
	
	// Реализация элемента списка
	template<typename T> // Шаблонный тип данных (для хранения любых типов данных в элементах нашего списка)
	class Node { // Элемент списка (node - узел)
	  public:
		
		Node* ptr_next; // Указатель на следующий элемент списка
		T data;

		Node(T data = T(), Node* ptr_next = nullptr) { // Конструктор для элемента списка (узла). По умолчанию в параметр для указателя ставим nullptr...
													   // ... при добавлении последнего элемента принимаем только данные, а указатель останется пустым (nullptr)
			this->data = data;
			this->ptr_next = ptr_next;
		}
	};

	Node<T>* head; // Указатель на начало списка - его первый элемент
	int size; // Количество элементов списка

};


// Объявление конструктора списка
template<typename T> 
List<T>::List() {
	size = 0;
	head = nullptr;
	//T data = NULL;
}

// Объявление деструктора списка
template<typename T>
List<T>::~List(){}

// Объявление и реализация оператора итерирования
template<typename T>
T& List<T>::operator[](const int index) { // При помощи ключевого слова operator указываем, что перегружаем оператор []. В параметры оператора принимаем индекс
	int counter = 0; // Создаём переменную для счёта индекса
	Node<T>* current = this->head; // Создаём переменную, в которую поместим адрес текущего элемента спискаа (узла)
	while (current != nullptr) { // Пока текущий адрес не пуст (пока не достигнется конец списка)
		if (counter == index) { // Ищем индекс равный счётчику индекса. Если Счётчик равен номеру искомого индекса
			return current->data; // Возвращаем данные элемента под номером index
		}
		current = current->ptr_next; // Либо, если счётчик не равен искомому индексу, переходим к следующему элементу списка
		counter++; // Прибавляем к счётчику единицу
	}
}

//Добавление элемента в конец списка
template<typename T> // Объявляем шаблонный класс для метода push_back
void List<T>::push_back(T data) { // Метод выписан отдельно для и определён в простанстве класса ( List<T>:: )
	// Проверяем на начиличие адрес первого элемента списка
	if (head == nullptr) {  // Если список пустой
		head = new Node<T>(data); // Создаём новый элемент списка (узел), и принимаем в него данные
	}
	else {	// Или если первый элемент уже имеет адрес
		Node<T>* current = this->head; // Создаём переменную current (текущий) узел, и указываем, что он является первым элементом списка

		while (current->ptr_next != nullptr) { // Перебираем циклом список элементов, пока не найдём элемент с "пустым" указателем - последний элемент списка

			current = current->ptr_next;
		}

		current->ptr_next = new Node<T>(data); // Создаём новый элемент списка (узел), и принимаем в него данные
	}
	size++; // Увеличиваем размер списка на единицу
}

template<typename T>
List<T>& List<T>::operator+(const List<T>& other) {

	// Создаём временный список
	auto temp_list = new List<int>();

	// Добавляем во временный список элементы первого списка
	auto tmp = this->head;
	while (tmp != nullptr) {
		temp_list->push_back(tmp->data);
		tmp = tmp->ptr_next;
	}
	// Добавляем во временный список элементы второго списка
	tmp = other.head;
	while (tmp != nullptr) {
		temp_list->push_back(tmp->data);
		tmp = tmp->ptr_next;
	}
	return *temp_list;
}

template<typename T>
List<T>& List<T>::operator&(const List<T>& other)
{
	auto temp_list = new List<int>();
	auto current = this->head;
	auto second_current = other.head;

	//if (this->size != other.size) throw new exception( "Error!!!!!!!!!");

	while (current != nullptr && second_current != nullptr) {
		
		temp_list->push_back(/*max(current->data, second_current->data)*/current->data > second_current->data ? current->data : second_current->data);
		current = current->ptr_next;
		second_current = second_current->ptr_next;
	}
	return *temp_list;
}

int main() {
	setlocale(LC_ALL, "");

	List<int> my_list;
	List<int> my_second_list;
	List<int> my_result_list;

	// cout <<"Количество элементов списка" << L.get_list_size() << endl;

	// Заполление списка случайными числами
	int numbers_count; 
	cout << "Введите количество элементов первого списка: ", cin >> numbers_count; // Вводим количество случайно сгенерированных значений списка
	for (int i = 0; i < numbers_count; i++) { 	// Цикл заполнения случайными числами
		my_list.push_back(rand() % 10); // rand() % 10 - ограничение генерации чисел в диапазоне от 0 до 10
	}

	cout << "Введите количество элементов второго списка: ", cin >> numbers_count; // Вводим количество случайно сгенерированных значений списка
	for (int i = 0; i < numbers_count; i++) { 	// Цикл заполнения случайными числами
		my_second_list.push_back(rand() % 10); // rand() % 10 - ограничение генерации чисел в диапазоне от 0 до 10
	}
	
	// Вывод списка
	cout << "\nПервый список:\n";
	for (int i = 0; i < my_list.get_list_size(); i++) {
		cout << my_list[i] << "\t";
	}
	cout << endl;

	cout << "\nВторой список:\n";
	for (int i = 0; i < my_second_list.get_list_size(); i++) {
		cout << my_second_list[i] << "\t";
	}

	cout << endl;

	my_result_list = my_list;
	cout << "\nCписок, созданный, при помощи оператора присваивания:\n";
	for (int i = 0; i < my_result_list.get_list_size(); i++) {
		cout << my_result_list[i] << "\t";
	}

	cout << endl;

	cout << "\nКонкатенация 2-х списков:\n";
	my_result_list = my_list + my_second_list;
	for (int i = 0; i < my_result_list.get_list_size(); i++) {
		cout << my_result_list[i] << "\t";
	}
	cout << endl;

	cout << "\nПобитовое ИЛИ:\n";
	my_list = my_list & my_second_list;
	for (int i = 0; i < my_list.get_list_size(); i++) {
		cout << my_list[i] << "\t";
	}
	cout << endl;

	system("pause");

	return 0;
}
