#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

class Car {
    const int id = rand() % 10001 + 1;
    char* name;
    string state;
    const int year = rand() % 32 + 1990;
   
public:

    enum State { great = 1, satisfactory = 2, need_of_repair = 3, scrapped = 4};

    int get_id() {
        return this->id;
    }

    char* get_name() {
        return this->name;
    }

    void set_name(char* new_name) {
        this->name = new_name;
    }

    string get_state() {
        return this->state;
    }

    void set_state(int state) {
        switch (state) {
        case 1:
            //Car::State::great;
            this->state = "great";
            break;
        case 2:
            //Car::State::paralyzed;
            this->state = "satisfactory";
            break;
        case 3:
            //Car::State::need_of_repair;
            this->state = "need_of_repair";
            break;
        case 4:
            //Car::State::scrapped;
            this->state = "scrapped";
            break;
        }
    }

    int get_year() {
        return this->year;
    }

    Car() { }

    Car(/*string new_name*/ char new_name[], int state) {
        // this->name = (char*) new_name.c_str(); // (char*) избавляет от квантификатора const, возвращаемого .c_str() # дикий костыль
        set_state(state);
        this->name = new_name;
        //this->year = year;
    }

    ~Car() {
        cout << "Destructor called for car" << name << endl;
    }

    Car& operator=(Car& other) {
        this->name = other.name;
        this->state = other.state;
        //this->year = car.year; # константное
        return *this;
    }

    bool operator==(Car& other) {
        if (this->state == other.state)
            return true;
        else
            return false;
    }

    friend ostream& operator<< (ostream& out, Car& car) {
        out << "\t" << left << setw(7) << "ID" << setw(10) << "NAME" << setw(15) << "STATE" << setw(10) << "YEAR" << endl;
        out << "\t" << left << setw(7) << car.id << setw(10) << car.name << setw(15) << car.state << setw(10) << car.year << endl << endl;
        return out;
    }
};

class RentalCar : public Car {
    int lease_year;

public:
    RentalCar() : Car() { }

    RentalCar(char new_name[], int state, int lease_year) : Car(new_name, state) {
        this->lease_year = lease_year;
    }

    RentalCar operator=(RentalCar other) {
        RentalCar temp;
        this->lease_year = other.lease_year;
        //this->year = car.year; # константное
        return temp;
    }

    friend ostream& operator<< (ostream& out, RentalCar& car) {
        out << "\t" << left << setw(7) << "ID" << setw(10) << "NAME" << setw(15) << "STATE" << setw(10) << "YEAR" << setw(10) << "LEASE YEAR" << endl;
        out << "\t" << left << setw(7) << car.get_id() << setw(10) << car.get_name() << setw(15) << car.get_state() << setw(10) << car.get_year() << setw(10) << car.lease_year << endl << endl;
        return out;
    }
};

void count_states(Car* array, int n) {
    int great_state_counter = 0,satisfactory_state_counter = 0, need_of_repair_state_counter = 0, scrapped_state_counter = 0;
    for (int i = 0; i < n; i++) {
        if (array[i].get_state() == "great")
            great_state_counter++;
        if (array[i].get_state() == "satisfactory")
            satisfactory_state_counter++;
        if (array[i].get_state() == "need_of_repair")
            need_of_repair_state_counter++;
        if (array[i].get_state() == "scrapped")
            scrapped_state_counter++;
    }

    cout << "\t" << left << setw(7) << "great" << setw(15) << "satisfactory" << setw(15) << "need_of_repair" << setw(10) << "scrapped" << endl;
    cout << "\t" << left << setw(7) << great_state_counter << setw(15) << satisfactory_state_counter << setw(15) << need_of_repair_state_counter << setw(10) << scrapped_state_counter << endl;
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "");

    int year = 2015;
    char car_name[15] = "BMW M5";
    char rental_car_name[15] = "Audi R8";

    cout << "\t\tObject of the Car class:\n";
    Car A(car_name, Car::State::great);
    cout << A;

    cout << "\t\tCopy builder for car:\n";
    Car B(A);
    cout << B;

    cout << "\t\tCar comparison:\n";
    cout <<"\t" << A.operator==(B) << endl << endl;

    cout << "\t\tDescendant of the Car class:\n";
    RentalCar C(rental_car_name, RentalCar::State::satisfactory, 2020);
    cout << C;

    cout << "\t\tCopy builder for rental car:\n";
    RentalCar D(C);
    cout << D;

    cout << "\t\tComparison of objects of both classes:\n";
    cout << "\t" << A.operator==(D) << endl << endl;

    cout << "\t\tCreating an array of class objects:\n";
    int n = 4;

    Car* array = new Car[n];
    array[0] = A;
    array[1] = B;
    array[2] = C;
    array[3] = D;
    //Car E;
   // array[4] = E;

    for (int i = 0; i < n; i++) 
        cout << array[i];
    
    cout << "\t\tCounting vehicle states:\n";
    count_states(array, n);

    return 0;
}