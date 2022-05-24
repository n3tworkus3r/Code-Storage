#include <iostream>

using namespace std;

// Динамическая структура данных "очередь"
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
	
		for (int i = 0; i < count; i++) 
			cout << "------";
		cout << endl;
		for (int i = 0; i < count; i++) 
			cout << "  " << array[i] << "  ";
		cout << endl;
		for (int i = 0; i < count; i++)
			cout << "------";
		cout << endl;
		
	}
};

void main() {

	Queue<int> queue;
	
	queue.push(8);
	queue.push(11);
	queue.push(17); // Q = {8,11,17}
	queue.print();

	queue.push(111);
	queue.print();
	queue.pop();
	queue.print();
	
}