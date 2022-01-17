#include <iostream>
#include <list>

using namespace std;
// List ** head - весь список
// *head  - первый элемент списка
struct List {
	int number;
	struct List* next; //указатель на следующий элемент
	//struct List* prev;
};

void push_back(List** head,int new_number ){

	////// СОЗДАЁМ НОВЫЙ УЗЕЛ
	List* new_node = new List;
	////// ЗАПОЛНЯЕМ СОЗДАННЫЙ УЗЕЛ ЗНАЧЕНИЯМИ
	new_node->number = new_number; //помещаем добовляемое значение в поле number
	new_node->next = NULL; //т.к. добавляем в конец списка, следующий элемент будет пустым
	////// АЛГОРИМ ЗАПОЛЕНИЯ
	if (*head != NULL) { //если в списке уже есть эелементы
		List* current;
		current = *head;
			while (current->next != NULL) {//пока не конец списка
				current = current->next;
			}
			current->next = new_node;
	}
	else {
		*head = new_node;
	}
}

void show(List** head) {
	List* current;
	current = *head;

	//cout << "Все элементы списка:\n";
	if (current == NULL) {
		cout << "Список пуст\n";
	}
	else {
		while (current != nullptr) {
			
 			cout << current->number << " -> ";
			if (current->next == NULL)
				cout << "NULL";
			current = current->next;
		}
	}
	cout << endl << endl;
}

void show_thirds(List** head) {
	List* current;
	current = *head;
	int counter = 0;

	//cout << "Все элементы списка:\n";
	if (current == NULL) {
		cout << "Список пуст\n";
	}
	else {
		while (current != nullptr) {
			if (counter % 3 == 0)
				cout << " ";

			cout << current->number << " ";
			current = current->next;
			counter++;
		}
	}
}

void remove_even(List** head)
{
	if (*head != NULL) { //если список не пуст
		bool need_link = true;
		List* current = *head; // Создаём узел для итерирования элементов списка
		List* preremovable = *head; // Создаём итерируемый узел для удаления элемнта следующего за собой
		if (current->number%2 == 0) {// Проверка первого элемента
			if (current->next != NULL) {
				List* removable = current;
				*head = current->next;
				current = current->next;
				preremovable = preremovable->next;
				delete removable;
			}
		}
		while (current != nullptr && need_link == true) { // Пока не дойдём до конца списка и пока нужен линк
			if (current->number%2 == 0) {  // пока значение рассматриемого узла равно удаляемому значению
				if (current->next != NULL) { // Если существует следующий узел

					while (current->number%2 == 0) {

						List* removable = current; // ПОМЕЩАЕМ УДАЛЯЕМЫЙ ЭЛЕМЕНТ В ОТДЕЛЬНУЮ ПЕРЕМЕННУЮ (для последующего удаления)

						if (current->next != nullptr) //если существует следующий узел
							current = current->next;// переход на следующий узел
						else {
							preremovable->next = NULL;
							need_link = false;
							delete removable;
							break;
						}
						delete removable;
						//if (current == NULL) { // Проверяем существование элемента 
						//	preremovable->next = NULL;
						//}
						//
					}

					if (need_link) {
						preremovable->next = current;
						current = current->next;
					}


					//break;
				}
				else {
					preremovable->next = NULL;
				}
			}
			else {
				preremovable = current;
				current = current->next;
			}
		}
	}
	else {
		cout << "Список пуст\n";
	}
}

void remove_element(List** head, List * element) {
	if (*head != NULL) { //если список не пуст
		bool need_link = true;
		List* current = *head; // Создаём узел для итерирования элементов списка
		List* preremovable = *head; // Создаём итерируемый узел для удаления элемнта следующего за собой

		if (&current == &element) {// Проверка первого элемента
			if (current->next != NULL) {
				List* removable = current;
				*head = current->next;
				current = current->next;
				preremovable = preremovable->next;
				delete removable;
			}
		}

		while (current != nullptr ) { // Пока не дойдём до конца списка и пока нужен линк
			if (&current == &element) {  // пока значение рассматриемого узла равно удаляемому значению
				if (current->next != NULL) { // Если существует следующий узел

					

						List* removable = current; // ПОМЕЩАЕМ УДАЛЯЕМЫЙ ЭЛЕМЕНТ В ОТДЕЛЬНУЮ ПЕРЕМЕННУЮ (для последующего удаления)

						if (current->next != nullptr) //если существует следующий узел
							current = current->next;// переход на следующий узел
						else {
							preremovable->next = NULL;
							need_link = false;
							delete removable;
							break;
						}
						

					if (need_link) {
						preremovable->next = current;
						current = current->next;
					}
				}
				else {
					preremovable->next = NULL;
				}
			}
			else {
				preremovable = current;
				current = current->next;
			}
		}
	}
	else {
		cout << "Список пуст\n";
	}
}

void remove_all_elements(List** head, int value/* List* preremovable */)
{
	///// ЕСЛИ СПИСОК НЕ ПУСТ
	if (*head != NULL) { //если список не пуст
		bool need_link = true;
		List* current = *head; // Создаём узел для итерирования элементов списка
		List* preremovable = *head; // Создаём итерируемый узел для удаления элемнта следующего за собой
		while (current->number == value) {// Проверка первого элемента
			if (current->next != NULL) {
				List* removable = current;
				*head = current->next;
				current = current->next;
				preremovable = preremovable->next;
				delete removable;
			}
		}
			while (current != nullptr && need_link == true) { // Пока не дойдём до конца списка и пока нужен линк
			if (current->number == value) {  // пока значение рассматриемого узла равно удаляемому значению
				if (current->next != NULL) { // Если существует следующий узел
					
					while (current->number == value) {

						List* removable = current; // ПОМЕЩАЕМ УДАЛЯЕМЫЙ ЭЛЕМЕНТ В ОТДЕЛЬНУЮ ПЕРЕМЕННУЮ (для последующего удаления)

						if (current->next != nullptr) //если существует следующий узел
							current = current->next;// переход на следующий узел
						else {
							preremovable->next = NULL;
							need_link = false;
							delete removable;
							break;
						}
						//delete removable;
						//if (current == NULL) { // Проверяем существование элемента 
						//	preremovable->next = NULL;
						//}
						//
					}

					if (need_link) {
						preremovable->next = current;
						current = current->next;
					}
				}
				else {
					preremovable->next = NULL;
				}
			}
			else {
				preremovable = current;
				current = current->next;
			}
		}
	}
	else {
		cout << "Список пуст\n";
	}
}

void remove_before_odd(List** head) {
	List* preremovable = *head;
	List* current = *head;
	if (*head != NULL) {
		while (current->next != NULL ) {
			if (current->next->number % 2 != 0 && current == *head && current->number%2==0) {
				List* removable = current;
				current = current->next;
				preremovable = preremovable->next;
				*head = current;
				delete removable;
			}
			if (current->number % 2 == 0) {
				if (current->next->number % 2 != 0) {
										List* removable = current;  // ставим метку "удаляемый"
					current = current->next;	// перемещаем метку текущий
					preremovable->next = current; // перенаправляем линк
					delete removable;
					
				}

					
			}
			if (preremovable->next != NULL) {
				preremovable = current;
				current = current->next;
			}

			if (current == NULL)
				break;
			

		}
	}
	else
		cout << "Список пуст";
}

void delete_sequence(List** head) {
	List* preremovable = *head;
	List* current = *head;
	int udalaemoje = 0;
	if (head != NULL) {
		while (current->next != NULL) {
			while (current->number == current->next->number && current == *head) {
				List* removable = current;
				udalaemoje = current->number;
				current = current->next;
				*head = current;
				preremovable = preremovable->next;
				delete removable;
			}
			if (current->number == udalaemoje) {
					List* removable = current;
					current = current->next;
					*head = current;
					preremovable = current;
					delete removable;
				}
			while (current->number == current->next->number) {
				List* removable = current;
				udalaemoje = current->number;
				current = current->next;
				preremovable->next = current;
				delete removable;
				if (current->number == udalaemoje) {
					List* removable = current;
					current = current->next;
					preremovable->next = current;
					delete removable;
				}
			}
			
			current = current->next;
		}
	}
	else
		cout << "Список пуст";

}

void ascention_insert(List** head, int number) {
	if (*head != NULL) { //если список не пуст
		List* current = new List;//создаём новый узел
		current = *head; // Устанавливаем метку "текущий" на первый эл-т списка

		/////////// УСЛОВИЕ ВСТАВКИ В НАЧАЛО СПИСКА ///////////

		if (current == *head && current->number > number) {//если метка "текущий" стоит на head и значение текущего узла БОЛЬШЕ вставляемого значения
			List* node = new List;//создаём новый узел
			*head = node;//вставлем новый узел на место head
			node->number = number;//присваиваем значение новому узлу
			node->next = current;//перенаправляем линк
			current = *head;
		}

		/////////// ПОИСК ЭЛЕМЕНТА ПЕРЕД КОТОРЫМ НУЖНО ВСТАВИТЬ ///////////

		while (current->number < number && current!=*head) { //пока следующее значение после текущего меньше вставляемого числа                                         3 4 6     5

			//////// ЕСЛИ ДОШЛИ ДО КОНЦА СПИСКА (НЕ НАЙДЯ УЗЕЛ)
			if (current->next == NULL) {//если конец списка
				List* node = new List;//создаём новый узел
				current->next=node;//вставлеям новый узел после текущего
				node->number = number;//заполняем новый узел значением
				node->next = NULL;//конец списка
				current = current->next;
				break;
			}
			current = current->next;//переход на новый элемент
		}

		/////////// ВСТАВКА ПОСЛЕ НАЙДЕННОГО УЗЛА (ЕСЛИ РАНЕЕ НЕ ДОШЛИ ЛО КОНЦА СПИСКА) ///////////
		if (current->next != NULL && current!=*head) {//если не конец списка
			List* node = new List;//создаём новый узел
			node->next = current->next;//перенаправляем линк
			current->next = node;//вставляем новый узел
			node->number = number;//присваиваем значение новому узлу
		}
	}
	else {
		/////////// ЕСЛИ СПИСОК БЫЛ ПУСТ ///////////
		List* node = new List;//создаём новый узел
		*head = node;//вставлем новый узел на первую позицию
		node->number = number;//присваиваем значение новому узлу
		node->next = NULL;//конец списка
	}
		
}

void descention_insert(List** head, int number) {
	if (*head != NULL) {//если список не пуст
		List* current = new List;//создаём новый узел
		current = *head; // Устанавливаем метку "текущий" на первый эл-т списка
		List* precurrent = new List;
		precurrent = *head;

		//если нам нужно вставить в начало списка
		if (current == *head && current->number < number) {//если метка "текущий" стоит на head и значение текущего узла меньше вставляемого значения
			List* node = new List;//создаём новый узел
			*head = node;//вставлем новый узел на место head
			node->number = number;//присваиваем значение новому узлу
			node->next = current;//перенаправляем линк
			current = *head;
		}
		//если вставлем в конец списка
		bool need_node = true;
		while (current->number > number && current!=*head) {//пока текущее значение больше вставляемого числа
			if (current->next == NULL) {//когда дошли до последнего элемента
					List* node = new List; // создаём новый узел
					current->next = node;
					node->number = number;//заполняем значением                                                                       9 9 7 5       2
					node->next = NULL;//конец списка
					current = current->next;
					need_node = false;
					break;
			}
			precurrent = current;
			current = current->next;
		}
		if (precurrent->next != NULL && need_node && current!=*head) {//если не конец списка
			List* node = new List;//создаём новый узел
			node->next = current;//перенаправляем линк
			precurrent->next = node;//вставляем новый узел
			node->number = number;//присваиваем значение новому узлу
		}
	}
	else {
		//если список пуст
		List* node = new List;//создаём новый элемент
		*head = node;//устанавливаем элемент на место head
		node->number = number;//присваиваем значение
		node->next = NULL;//конец списка
	}

}

void del_from_thirds(List** head) {
	if (*head != NULL) {
		List* current = *head;
		List* third = current; // создаём метку на начале предполагаемой тройки
		List* old_third = current; // 
		int counter_thirds = 0;

		while (current->next != NULL || current != NULL) {
			/////////// ПРОВЕРКА НА СУЩЕСТВОВАНИЕ ТРОЙКИ ///////////
			int counter = 1;
			current = third;

			while (current->next != NULL) { // считаем до трёх
				if (counter == 3)
					break;
				// переходим к следующему элеементу и прибавляем к счётчику
				current = current->next;
				counter++;
			}

			if (counter < 2)
				break;

			if (counter == 2) {
				List* one = third;
				List* two = third->next;

				bool living_one = true;
				bool living_two = true;

				if (one->number > two->number) {
					old_third->next = two;
					two->next = NULL;
					delete one;
					break;
					living_one = false;
				}
				if (living_one) {
					if (two->number > one->number) {

						one->next = NULL;
						old_third->next = one;
						break;
						delete two;
					}
				}
				
			}

			if (counter == 3) {// ЕСЛИ ТРОЙКА СУЩЕСТВУЕТ
				// для удобства отмечаем три её элемента
				List* one = third;
				List* two = third->next;
				List* three = third->next->next;
				List* four = third->next->next->next;

				///// ДОПУСТИМ, ПЕРВЫЙ - МИНИМАЛЬНЫЙ /////
				int min = third->number;

				/*if (two->number < min)
					min = two->number;
				if (three->number < min)
					min = three->number;*/

					//////////  АЛГОРИТМ ПОИСКА МИНИМАЛЬНОГО В ТРОЙКЕ //////////
				List* current = third;
				counter = 1;
				while (counter <= 3) {
					if (current == NULL)
						break;

					if (current->number < min)
						min = current->number;
					counter++;
					current = current->next;
				}
				////////////////////////////////////////////////////////////

				bool need_link = false;
				if (four != NULL)
					need_link = true;

				///////// ЕСЛИ НУЖЕН ЛИНК
				if (need_link) {
				///////// ЕСЛИ ПЕРВАЯ ТРОЙКА
					if (third == *head) {
						bool living_three = true;
						if (one->number > min) {
							*head = two;
							delete one;
							if (two->number > min) {
								*head = three;
								delete two;
							}
							old_third = three;
						}
						else {
							if (two->number > min) {
								one->next = three;
								delete two;
								if (three->number > min) {
									one->next = four;
									delete three;
									living_three = false;
									old_third = one;
									*head = one;
								}
							}
						}
						if (living_three) {
							if (three->number > min) {
								two->next = four;
								delete three;
								old_third = two;
							}
						}
						
					}///////// ИЛИ ЕСЛИ НЕ ПЕРВАЯ ТРОЙКА
					else {
						bool living_one = true;
						bool living_two = true;
						bool living_three = true;

						if (one->number > min) {
							old_third->next = two;
							delete one;
							if (two->number > min) {
								old_third->next = three;
								delete two;
							}
							old_third = three;
						}
						else {
							if (two->number > min) {
								one->next = three;
								old_third = three;
								delete two;
								if (three->number > min) {
									one->next = four;
									delete three;
									living_three = false;
									old_third = one;
								}
							}
						}
						
						if (living_three) {
							if (three->number > min) {
								two->next = four;
								delete three;
								old_third = two;
							}
						}
					}
				}

				//////// ЕСЛИ ЛИНК НЕ НУЖЕН ////////
				else { 
					///////// ЕСЛИ ПЕРВАЯ ТРОЙКА
					if (third == *head) {
						if (one->number > min) {
							*head = two;
							delete one;
							if (two->number > min) {
								*head = three;
								delete two;
							}
						}
						else {
							if (two->number > min) {
								one->next = three;
								delete two;
								if (three->number > min) {
									one->next = NULL;
									delete three;
								}
							}
							
							if (three->number > min) {
								two->next = NULL;
								delete three;
							}
							
						}
					}
					///////// ЕСЛИ НЕ ПЕРВАЯ ТРОЙКА
					else {
						bool living_one = true;
						bool living_two = true;
						bool living_three = true;


						// ПЕРВЫЙ ИЛИ ПЕРВЫЙ И ВТОРОЙ
						if (one->number > min) {
							old_third->next = two;
							delete one;
							living_one = false;
							if (two->number > min) {
								old_third->next = three;
								delete two;
								living_two = false;
							}
						}
						// ВТОРОЙ ИЛИ ВТОРОЙ И ТРЕТИЙ
						else {
							if (two->number > min) {
								one->next = three;
								old_third->next = one;
								old_third = third;
								delete two;
								living_two = false;
								if (three->number > min) {
									one->next = NULL;
									old_third = one;
									living_three = false;
									delete three;
								}
							}
						}
						// УДАЛЯЕМ ТРЕТИЙ
						
						if (living_three) {
							if (three->number > min) {
								delete three;

								// ЕСЛИ ВТОРОЙ УДАЛЕН, КОНЦОМ СПИСКА БУДЕТ ПЕРВЫЙ
								if(living_two == false)
									one->next = NULL;
								//если второй существует
								else
									two->next = NULL;


							}
						}						
					}
				}
				counter_thirds++;
				
				third = four;

				if (third == NULL)
					break;
			}
			//////////////////////////////////////////////////////////

			
		}
	}
	else
		cout << "Список пуст";
}

void kollokvium_task(List** head) {

	if (*head != NULL) {
		List* current = *head;
		List* third = current; // создаём метку на начале предполагаемой тройки
		List* old_third = current;
		
		int counter_thirds = 0;

		while (true) {
			/////////// ПРОВЕРКА НА СУЩЕСТВОВАНИЕ ТРОЙКИ ///////////
			int counter = 1;
			current = third;

			while (current->next != NULL) { // считаем до трёх
				if (counter == 3)
					break;
				// переходим к следующему элеементу и прибавляем к счётчику
				current = current->next;
				counter++;
			}

			if (counter < 3)
				break;

			if (counter == 3) {// ЕСЛИ ТРОЙКА СУЩЕСТВУЕТ
				
				// для удобства отмечаем три её элемента
				List* one = third;
				List* two = third->next;
				List* three = third->next->next;
				List* four = third->next->next->next;
				
				bool without_remainder = false;

				if (four == NULL)
					without_remainder = true;

				int remainder = 0;
				int sum = one->number + two->number + three->number;
				
				if(without_remainder != true)
					remainder = sum % four->number;

				///////// ЕСЛИ ПЕРВАЯ ТРОЙКА
				if (third == *head) {

					
					if (remainder % 2 == 0 && without_remainder == false) {
						delete one;
						delete two;
						delete three;
						*head = four;
						old_third = four;
					}


					if(without_remainder || remainder % 2 != 0) {
						two->next = four;
						old_third = two;
						delete three;
					}
				}
				///////// ЕСЛИ НЕ ПЕРВАЯ ТРОЙКА
				else {
					if (remainder % 2 == 0 && without_remainder == false) {
						delete one;
						delete two;
						delete three;
						old_third->next = four;
					}


					if (without_remainder || remainder % 2 != 0) {
						two->next = four;
						delete three;
					}
				}

				third = four;
			
			}

			if (third == NULL)
				break;
		}
	}
}
int main() {
	setlocale(LC_ALL, "");
	List** head = new List*;
	*head = NULL;
	
	push_back(head, 2);
	push_back(head, 3);
	push_back(head, 4);

	push_back(head, 3);
	push_back(head, 3);
	push_back(head, 3);

	push_back(head, 3);
	
	show(head);

	kollokvium_task(head);
		
	show(head);
	
	

	system("pause");
	return 0;
}
