/*
                    TASK:

    Create a class "prioritized queue of integers" based on a unidirectional linear list.
    When an item is inserted, its priority is set, which has three fixed values: low, medium, high.
    Once an item has been placed in the queue, # the priority of the item cannot be changed.

    Provide the following methods:
      * constructor without parameters, copying.
      * assignment operator.
      * determination of the number of elements in the queue with the specified priority, total number of elements.
      * check on the emptiness of the queue.
      * removing an element from the queue.
      * receiving information about the priority and value of an element in the head of the queue.


                    �������:

    # ������� ����� "������� � ������������ �� ����� �����" 
    #   �� ������ ����������������� ��������� ������. 
    # ��� ������� �������� ������� ��� ���������, ������� ��� �������������
    #   ��������: ������, �������, �������. 
    # ����� ��������� � ������� ��������� ��-�� �������� ������.

    # ������������� ��������� ������:
      * ����������� ��� ����������, �����������.
      * �������� ������������.
      * ����������� ���-�� ��������� � ������� � �������� �����������, ����� ���-�� ��-�.
      * ���������� �� ������� �������.
      * �������� �������� �� �������.
      * ���������� ����������� � ���������� � �������� ��������, �������� � ������ �������.

*/

#include <iostream>
#include <string>

using namespace std;

class PriorityQueue {

    struct Node {
        int data;
        short priority;
        struct Node* prev;
    };

    Node* back = NULL;
    Node* front = NULL;

public:

    PriorityQueue() { }

    PriorityQueue(PriorityQueue&q) { // ����������� �����������

        Node* current = q.back;

        if (front == NULL) {
            Node* new_node = new Node;
            new_node->data = current->data;
            new_node->priority = current->priority;
            new_node->prev = NULL;
            front = new_node;
            back = new_node;

            current = current->prev;
        }
       
        while (current != NULL) {
            Node* new_node = new Node;
            new_node->data = current->data;
            new_node->priority = current->priority;
            new_node->prev = NULL;
            front->prev = new_node;
            front = new_node;

            current = current->prev;
        }
    }

    PriorityQueue& operator=(PriorityQueue& q) { // �������� ������������
        // �������� � ���������� ����
        Node* current = q.back;

        if (front == NULL) {
            Node* new_node = new Node;
            new_node->data = current->data;
            new_node->priority = current->priority;
            new_node->prev = NULL;
            front = new_node;
            back = new_node;

            current = current->prev;
        }

        while (current != NULL) {
            Node* new_node = new Node;
            new_node->data = current->data;
            new_node->priority = current->priority;
            new_node->prev = NULL;
            front->prev = new_node;
            front = new_node;

            current = current->prev;
        }
        return *this;
    }

    void count_priority() {
        int my_priority, counter = 0;
        cout << "������� ���������: ", cin >> my_priority;
        Node* current = back;

        while (current != NULL) {
            if (current->priority == my_priority)
                counter++;
            current = current->prev;
           
        }
        cout << "��������� � ����������� " << my_priority << " -> " << counter << endl;
    }

    void count_all() {
        int counter = 0;
       
        Node* current = back;

        while (current != NULL) {
            current = current->prev;
            counter++;
        }
        cout << "��������� � ������� -> " << counter << endl;
    }

    bool empty() {
        if (front == NULL) {
            cout << "������� �����!\n";
            return true;
        }
        else {
            cout << "������� �� �����!\n";
            return false;
        }
    }

    void get_front() {
        cout << "..";
        cout << "front data ->" << front->data << " front priority -> " << front->priority << endl;
    }

    void pop() { // �������� ��������
        Node* current = back; // current - �������� �������
        if (current->prev != NULL) {
            while (current->prev != front) {
                current = current->prev;
            }
            front = current;
            current->prev = NULL;
        }
        else {
            front = NULL;
            back = NULL;
        }

    }

    void add(int new_data, int new_priority) {
        // ��������������� �����
        Node* temp = NULL;
        Node* tail = NULL;

        // �������� � ���������� ����
        Node* new_node = new Node;
        new_node->data = new_data;
        new_node->priority = new_priority;
        new_node->prev = NULL;

        if (front != NULL) { // ���� � ������ ���������� ��������
            new_node->prev = back; // ����� ������� ����������� ����� ����������
            back = new_node; // ����������� ���������� ���������
            Node* current = back; // current (�������� �������) ��������������� � ����� �������

            switch (new_node->priority) {
            case 1:
                while (current->prev->priority < 1) {// 3 -> low priority
                    if (current->prev == front) {
                        if (current == back)
                            back = current->prev;

                        /// ����� ����� ///
                        temp = current->prev;
                        current->prev = current->prev->prev; // 1 -> 3
                        temp->prev = current; // 2 -> 1
                        ////////////////////

                        front = current;
                    }
                    else {
                        if (current == back)
                            back = current->prev;

                        /// ����� ����� ///
                        temp = current->prev;
                        current->prev = current->prev->prev; // 1 -> 3
                        temp->prev = current; // 2 -> 1
                        ////////////////////
                    }

                    if (current->prev == NULL)
                        break;
                }
            case 2:
                while (current->prev->priority < 2) {// 2 -> middle rear
                    if (current->prev == front) {
                        if (current == back)
                            back = current->prev;

                        /// ����� ����� ///
                        temp = current->prev;
                        current->prev = current->prev->prev; // 1 -> 3
                        temp->prev = current; // 2 -> 1
                        ////////////////////

                        front = current;
                    }
                    else {
                        if (current == back)
                            back = current->prev;

                        /// ����� ����� ///
                        temp = current->prev;
                        current->prev = current->prev->prev; // 1 -> 3
                        temp->prev = current; // 2 -> 1
                        ////////////////////
                    }

                    if (current->prev == NULL)
                        break;
                }
                break;
            case 3:
                while (current->prev->priority < 3) {// 3 -> high priority
                    if (current->prev == front) {
                        if (current == back)
                            back = current->prev;

                        /// ����� ����� ///
                        temp = current->prev;
                        current->prev = current->prev->prev; // 1 -> 3
                        temp->prev = current; // 2 -> 1
                        ////////////////////

                        front = current;
                    }
                    else {
                        if (current == back) {
                            back = current->prev;
                            tail = back; // tail - �������, ������� ����� ������������ 
                        }

                        temp = current->prev;
                        current->prev = current->prev->prev; // 1 -> 3
                        temp->prev = current; // 2 -> 1

                        tail->prev = temp; // tail "���������" �� �������, ����� ������������
                        tail = temp; // tail ���������� ����� ������������
                    }

                    if (current->prev == NULL)
                        break;
                }
                break;
            }
        }
        else { // ���� ������ ����, ������� ����� �������� ����������� �������
            front = new_node;
            back = new_node;
        }
    }

    void push() {
        int new_data = 0, new_priority = 0;
        cout << "Enter some data (int number)\n-> ", cin >> new_data;
        cout << "Enter priority (1/2/3)\n-> ", cin >> new_priority;
        add(new_data, new_priority);
    }
   
    void print() {
        Node* current = back;
        cout << "\n��� �������� ������:\n";
        if (current == NULL) {
            cout << "������ ����";
        }
        else {
            //while (current->next != NULL)
            cout << "back -> ";
            while (current != nullptr) {
                cout << current->data << "("<<current->priority << ") " << " -> ";
                current = current->prev;
            }
            cout << "front\n";
        }
    }
};


