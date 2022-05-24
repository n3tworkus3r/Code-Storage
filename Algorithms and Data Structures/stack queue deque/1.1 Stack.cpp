#include <iostream>

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
		cout  << endl << "\t" << "|";
		for (int i = 0; i < size_of_stack; i++)
			cout << "------";
		cout << endl << "\t" << "|";
		for (int i = 0; i < size_of_stack; i++)
			cout << "  " << array[i] << "  ";
		cout << endl << "\t" << "|";
		for (int i = 0; i < size_of_stack; i++)
			cout << "------";
		cout << endl;

	}
};

int main() {

	setlocale(LC_ALL, "");

	Stack<int> stack;

	stack.push(1);
	stack.push(111);

	stack.print();
	stack.push(112);
	stack.push(101);
	stack.print();
	stack.pop();
	stack.print();

	//cout << stack.top() << endl;
	
	return 0;
}