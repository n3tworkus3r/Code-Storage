#include <iostream>
#include <ctime>

/*
	Беляев Максим Сергеевич
	АиСД
	Лабораторная работа 6.2 
    Приложение, моделирующее работу конвейера, по производству салатов:
	 - имеется склад продуктов, состоящих из 3 больших контейнеров (3 стека), в которые периодически доставляют 3 вида продукта по отдельности в каждый (по несколько единиц каждого продукта).
	 - периодически на склад приезжают 5 роботов, образуя очередь, и, если  в наличии имеются все 3 продукта, первый робот в очереди забирает по 1 ед. продукта из каждой коробки,
	   смешивает их в салат, упаковывает и направляет в сортировочный цех. После доставки в сортировочный цех робот возвращается обратно в конец очереди.
	 - сортировочный цех представляет из себя ленту (дек), где в любой конец складываются упакованные салаты. С 2 концов ленты стоят 2 робота, которые готовые салаты складывают в машину
	   (удаляют из дека по 1 единице салата), которая увозит продукцию в магазин.
*/

using namespace std;

template <typename Template>
class Stack {
private:
	unsigned int size_of_stack;
	Template* array;

public:
	Stack() {
		size_of_stack = 0;
		array = new Template[1];
	}

	~Stack() {
		delete[] array;
	}

	void push(Template item) {
		Template* temp_pointer; // Объявить дополнительный указатель
		temp_pointer = array; // Перенаправить дополнительный указатель на array

		try {
			// Попытка выделить новый фрагмент памяти для array, но на 1 больше
			array = new Template[size_of_stack + 1];

			// Скопировать данные из участка на который указывает temp_pointer (старые данные)
			// В участок, на который указывает array
			for (int i = 0; i < size_of_stack; i++)
				array[i] = temp_pointer[i];

			// Скопировать последний (добавляемый) элемент
			array[size_of_stack] = item;

			// Увеличить количество элементов на 1
			size_of_stack++;

			// Освободить предварительно выделенную память
			if (size_of_stack > 1)
				delete[] temp_pointer;
		}
		catch (bad_alloc e) {
			// Если память не выделена
			cout << e.what() << endl; // Вывести сообщение об ошибке

			// Вернуть старый указатель на array
			array = temp_pointer;
		}
	}

	Template pop() {
		if (size_of_stack == 0)
			return 0;

		// Запомнить элемент, который удаляется из очереди
		Template item;

		item = array[0];

		// Сформировать новый участок памяти, который на 1 меньше
		try {
			Template* temp_pointer;

			// Попытка выделить память
			temp_pointer = new Template[size_of_stack - 1];

			size_of_stack--; // Уменьшается количество элементов в стеке

			// array=>temp_pointer
			for (int i = 0; i < size_of_stack; i++)
				temp_pointer[i] = array[i]; // Копируются все кроме последнего элемента

			  // Освободить участок, на который указывает array
			if (size_of_stack > 0)
				delete[] array;

			// Перенаправить array на temp_pointer
			array = temp_pointer;

			// Вернуть item (удаляемый элемент)
			return item;
		}
		catch (bad_alloc e) {
			// Если память не выделилась, то вернуть 0
			cout << e.what() << endl;
			return 0;
		}
	}

	Template top() {
		return array[size_of_stack - 1];
	}

	unsigned int size() {
		return size_of_stack;
	}

	void print() {
		cout << endl << "\t" << "|";
		for (int i = 0; i < size_of_stack; i++)
			cout << "-----";
		cout << endl << "\t" << "|";
		for (int i = 0; i < size_of_stack; i++)
			cout << "  " << array[i] << "  ";
		cout << endl << "\t" << "|";
		for (int i = 0; i < size_of_stack; i++)
			cout << "-----";
		cout << endl;

	}
};

template <typename Template>
class Queue {
private:
	Template* array; // Динамический массив
	int count; // Количество элементов в очереди

public:
	// Конструктор по умолчанию
	Queue() {
		count = 0;
	}

	// Конструктор копирования
	Queue(const Queue& obj) {
		// скопировать obj в текущий объект
		count = obj.count;

		try {
			// Попытка выделить память для array
			array = new Template[count];
			// Заполнить значениями
			for (int i = 0; i < count; i++)
				array[i] = obj.array[i];
		}
		catch (bad_alloc e) {
			// Если память не выделена, то вывести текст ошибки
			cout << e.what() << endl;
			count = 0; // Создать пустую очередь
		}
	}

	// Добавить элемент в очередь
	void push(Template item) {
		Template* temp_pointer; // Объявить дополнительный указатель
		temp_pointer = array; // Перенаправить дополнительный указатель на array

		try {
			// Попытка выделить новый фрагмент памяти для array, но на 1 больше
			array = new Template[count + 1];

			// Скопировать данные из участка на который указывает temp_pointer (старые данные)
			// В участок, на который указывает array
			for (int i = 0; i < count; i++)
				array[i] = temp_pointer[i];

			// Скопировать последний (добавляемый) элемент
			array[count] = item;

			// Увеличить количество элементов на 1
			count++;

			// Освободить предварительно выделенную память
			if (count > 1)
				delete[] temp_pointer;
		}
		catch (bad_alloc e) {
			// Если память не выделена
			cout << e.what() << endl; // Вывести сообщение об ошибке

			// Вернуть старый указатель на array
			array = temp_pointer;
		}
	}

	// Удалить первый элемент из очереди
	Template pop() {
		if (count == 0)
			return 0;

		// Запомнить элемент, который удаляется из очереди
		Template item;

		item = array[0];

		// Сформировать новый участок памяти, который на 1 меньше
		try {
			Template* temp_pointer;

			// Попытка выделить память
			temp_pointer = new Template[count - 1];

			count--; // Уменьшить количество элементов в очереди

			// array=>temp_pointer
			for (int i = 0; i < count; i++)
				temp_pointer[i] = array[i + 1]; // копируются все кроме первого элемента

			  // Освободить участок, на который указывает array
			if (count > 0)
				delete[] array;

			// Перенаправить array на temp_pointer
			array = temp_pointer;

			// Вернуть item (удаляемый элемент)
			return item;
		}
		catch (bad_alloc e) {
			// Если память не выделилась, то вернуть 0
			cout << e.what() << endl;
			return 0;
		}
	}

	// Перегрузка operator=(),
	Queue& operator=(const Queue & obj) {
		Template* temp_pointer; // Указатель на дополнительную память

		try {
			// Попытка выделить новый участок памяти для temp_pointer
			temp_pointer = new Template[obj.count];

			// Если память выделена успешно, можно освобождать предварительно выделенную память для array
			if (count > 0)
				delete[] array;

			// Скопировать obj в текущий объект
			array = temp_pointer; // Перенаправить array на temp_pointer
			count = obj.count;

			// Заполнить значениями
			for (int i = 0; i < count; i++)
				array[i] = obj.array[i];
		}
		catch (bad_alloc e) {
			// Если память не выделилась, то вывести соответствующее сообщение
			cout << e.what() << endl;
		}
		return *this; // Вернуть текущий объект
	}

	// Деструктор
	~Queue() {
		if (count > 0)
			delete[] array;
	}

	// Взять первый элемент из очереди не вытягивая его
	Template top() {
		if (count > 0)
			return array[0];
		else
			return 0;
	}

	// Очистка очереди
	void clear() {
		if (count > 0) {
			delete[] array;
			count = 0;
		}
	}

	// Проверка существования элементов в очереди
	bool is_empty() {
		return count == 0;
	}

	// Количество элементов в очереди
	int size() {
		return count;
	}

	// Метод, выводящий очередь
	void print() {
		cout << endl << "\t";
		for (int i = 0; i < count; i++)
			cout << "------";
		cout << endl << "\t";
		for (int i = 0; i < count; i++)
			cout << "  " << array[i] << "  ";
		cout << endl << "\t";
		for (int i = 0; i < count; i++)
			cout << "------";
		cout << endl;
	}
};

template <typename Template>
class Deque {
private:
	Template* array; // Динамический массив
	int count; // Количество элементов в очереди

public:
	// Конструктор по умолчанию
	Deque() {
		count = 0;
	}

	// Конструктор копирования
	Deque(const Deque& obj) {
		// скопировать obj в текущий объект
		count = obj.count;

		try {
			// Попытка выделить память для array
			array = new Template[count];
			// Заполнить значениями
			for (int i = 0; i < count; i++)
				array[i] = obj.array[i];
		}
		catch (bad_alloc e) {
			// Если память не выделена, то вывести текст ошибки
			cout << e.what() << endl;
			count = 0; // Создать пустую очередь
		}
	}

	// Добавить элемент в конец очереди
	void push_back(Template item) {
		Template* temp_pointer; // Объявить дополнительный указатель
		temp_pointer = array; // Перенаправить дополнительный указатель на array

		try {
			// Попытка выделить новый фрагмент памяти для array, но на 1 больше
			array = new Template[count + 1];

			// Скопировать данные из участка на который указывает temp_pointer (старые данные)
			// В участок, на который указывает array
			for (int i = 0; i < count; i++)
				array[i] = temp_pointer[i];

			// Скопировать последний (добавляемый) элемент
			array[count] = item;

			// Увеличить количество элементов на 1
			count++;

			// Освободить предварительно выделенную память
			if (count > 1)
				delete[] temp_pointer;
		}
		catch (bad_alloc e) {
			// Если память не выделена
			cout << e.what() << endl; // Вывести сообщение об ошибке

			// Вернуть старый указатель на array
			array = temp_pointer;
		}
	}

	// Добавить элемент в начало очереди
	void push_front(Template item) {
		Template* temp_pointer; // Объявить дополнительный указатель
		temp_pointer = array; // Перенаправить дополнительный указатель на array

		try {
			// Попытка выделить новый фрагмент памяти для array, но на 1 больше
			array = new Template[count + 1];

			// Скопировать данные из участка на который указывает temp_pointer (старые данные)
			// В участок, на который указывает array
			for (int i = 0; i < count; i++)
				array[i + 1] = temp_pointer[i];

			// Скопировать последний (добавляемый) элемент
			array[0] = item;

			// Увеличить количество элементов на 1
			count++;

			// Освободить предварительно выделенную память
			if (count > 1)
				delete[] temp_pointer;
		}
		catch (bad_alloc e) {
			// Если память не выделена
			cout << e.what() << endl; // Вывести сообщение об ошибке

			// Вернуть старый указатель на array
			array = temp_pointer;
		}
	}

	// Удалить последний элемент из очереди
	Template pop_back() {
		if (count == 0)
			return 0;

		// Запомнить элемент, который удаляется из очереди
		Template item;

		item = array[count - 1];

		// Сформировать новый участок памяти, который на 1 меньше
		try {
			Template* temp_pointer;

			// Попытка выделить память
			temp_pointer = new Template[count - 1];

			count--; // Уменьшить количество элементов в очереди

			// array=>temp_pointer
			for (int i = 0; i < count; i++)
				temp_pointer[i] = array[i]; // Копируются все элементы, кроме последнего

			  // Освободить участок, на который указывает array
			if (count > 0)
				delete[] array;

			// Перенаправить array на temp_pointer
			array = temp_pointer;

			// Вернуть item (удаляемый элемент)
			return item;
		}
		catch (bad_alloc e) {
			// Если память не выделилась, то вернуть 0
			cout << e.what() << endl;
			return 0;
		}
	}

	// Удалить первый элемент из очереди
	Template pop_front() {
		if (count == 0)
			return 0;

		// Запомнить элемент, который удаляется из очереди
		Template item;

		item = array[0];

		// Сформировать новый участок памяти, который на 1 меньше
		try {
			Template* temp_pointer;

			// Попытка выделить память
			temp_pointer = new Template[count - 1];

			count--; // Уменьшить количество элементов в очереди

			// array=>temp_pointer
			for (int i = 0; i < count; i++)
				temp_pointer[i] = array[i + 1]; // копируются все кроме первого элемента

			  // Освободить участок, на который указывает array
			if (count > 0)
				delete[] array;

			// Перенаправить array на temp_pointer
			array = temp_pointer;

			// Вернуть item (удаляемый элемент)
			return item;
		}
		catch (bad_alloc e) {
			// Если память не выделилась, то вернуть 0
			cout << e.what() << endl;
			return 0;
		}
	}

	// Перегрузка operator=(),
	Deque& operator=(const Deque & obj) {
		Template* temp_pointer; // Указатель на дополнительную память

		try {
			// Попытка выделить новый участок памяти для temp_pointer
			temp_pointer = new Template[obj.count];

			// Если память выделена успешно, можно освобождать предварительно выделенную память для array
			if (count > 0)
				delete[] array;

			// Скопировать obj в текущий объект
			array = temp_pointer; // Перенаправить array на temp_pointer
			count = obj.count;

			// Заполнить значениями
			for (int i = 0; i < count; i++)
				array[i] = obj.array[i];
		}
		catch (bad_alloc e) {
			// Если память не выделилась, то вывести соответствующее сообщение
			cout << e.what() << endl;
		}
		return *this; // Вернуть текущий объект
	}

	// Деструктор
	~Deque() {
		if (count > 0)
			delete[] array;
	}

	// Взять первый элемент из очереди не вытягивая его
	Template top() {
		if (count > 0)
			return array[0];
		else
			return 0;
	}

	// Очистка очереди
	void clear() {
		if (count > 0) {
			delete[] array;
			count = 0;
		}
	}

	// Проверка существования элементов в очереди
	bool is_empty() {
		return count == 0;
	}

	// Количество элементов в очереди
	int size() {
		return count;
	}

	// Метод, выводящий очередь
	void print() {
		cout << endl << "\t";
		for (int i = 0; i < count; i++)
			cout << "-----";
		cout << endl << "\t";
		for (int i = 0; i < count; i++)
			cout << "  " << array[i] << "  ";
		cout << endl << "\t";
		for (int i = 0; i < count; i++)
			cout << "-----";
		cout << endl;
	}
};


void main() {
	
	setlocale(LC_ALL, "");
	srand(time(NULL));

	auto choice = 0;

	Stack <int> first_container;
	Stack <int> second_container;
	Stack <int> third_container;


	Queue <string> robots;
	robots.push("R1");
	robots.push("R2");
	robots.push("R3");
	robots.push("R4");
	robots.push("R5");

	Deque <int> sorting_shop;


	do {
		system("cls");

		/////

		cout << "\tWarehouse:" << endl;
		for(int i = 0; i < rand()%2;i++)
			first_container.push(rand() % 10);
		for (int i = 0; i < rand() % 2; i++)
			second_container.push(rand() % 10);
		for (int i = 0; i < rand() % 2; i++)
			third_container.push(rand() % 10);

		first_container.print();
		second_container.print();
		third_container.print();

		/////

		cout << "\n\tWorking robots:" << endl;
		robots.print();

		/////

		cout << "\n\tSorting shop:" << endl;
		sorting_shop.print();

		/////

		if (first_container.size() > 1 && second_container.size() > 1 && third_container.size() > 1) {
			string worker = robots.pop();
			int item1 = first_container.pop();
			int item2 = second_container.pop();
			int item3 = third_container.pop();

			sorting_shop.push_front((item1 + item2 + item3)/(rand()%10+1));
			
			switch (choice) {
			case 0:
				break;
			case 1:
				sorting_shop.pop_back();
				break;
			case 2:
				sorting_shop.pop_front();
				break;
			case 3:
				sorting_shop.pop_front();
				sorting_shop.pop_back();
				break;
			}
			choice = rand() % 5;

			robots.push(worker);
		}
	
	} while (true);
}