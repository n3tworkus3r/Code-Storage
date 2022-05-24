#include <iostream>
#include <iomanip>
#include <vector>
#include <mpi.h>

/*
	Вариант 1
	Для введенной матрицы A размера n×n подсчитайте сумму среди всех максимумов по строкам значений в столбцах с нечетными номерами.
*/


/*
	path = [C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x86] 
	sec_path = [C:\Program Files (x86)\Microsoft SDKs\MPI\Include]

	Проект -> Свойства -> Компоновщик -> Ввод -> Дополнительные зависимости -> [msmpi.lib]
	Проект -> Свойства -> Общие -> Дополнительные каталоги библиотек -> [path]
	Проект -> Свойства -> C/C++ -> Дополнительные каталоги включаемых -> [sec_path]

	Execution: cmd-> mpiexec -n [process_number] [filename].exe
*/

using namespace std;

int process_number = 0; // Number of available processes 
int process_rank = 0; //Process rank of current process 


#pragma region SingleProcessCalculation
void single_process_calculation(int** array, int n) {
	int sum = 0, max;
	clock_t start, end;
	vector <int> useful_row;

	////////// FILLING AND OUTPUT ///////////

	//int value = 1;
	for (int i = 1; i <= n; i++) {
		array[i] = new int[n];
		for (int j = 1; j <= n; j++) {
			//array[i][j] = value;
			array[i][j] = rand() % 10 + 1;
			//value++;
			std::cout << setw(5) << array[i][j] << " ";
		}
		std::cout << endl;
	}

	////// ALGORITHM (SINGLE THREAD) ////////

	start = clock();

	int* columns = new int[n];

	for (int j = 1; j <= n; j++) {
		std::cout << "\n" << j << " row elements:\n";

		vector <int> useful_row; // Вектор для объединения искомых элементов (костыль, конечно, но так было проще :3 )
		for (int i = 1; i <= n; i += 2) {
			std::cout << array[j][i] << " ";
			useful_row.push_back(array[j][i]);
		}

		max = useful_row.at(0);
		for (int i = 0; i < useful_row.size(); i++)
			if (useful_row.at(i) > max)
				max = useful_row.at(i);
		std::cout << "\nmax[" << j << "] = " << max << endl;

		//////////// FIND SUM /////////////

		sum += max;
		end = clock();
	}
	double execution_time = (end - start);
	std::cout << "\n\nsum = " << sum << "\nexecution time " << execution_time << " ms" << endl;

}
#pragma endregion

#pragma region DataInitialization
void data_initialization(int* matrix, int size) {
	for (int i = 0; i < size * size; i++)
		matrix[i] = rand() % 10;//i + 1;
}

#pragma endregion

#pragma region ProcessInitialization

void process_initialization(int*& matrix, int*& result, int*& process_rows, int*& process_result, int& size, int& row_number) {
	int rest_rows;
	int i;
	if (process_rank == 0) {
		do {
			if (size < process_number) 
				cout << "Size of the objects must be greater than number of processes!\n ";
		} while (size < process_number);
	}

	/*
	int MPIAPI MPI_Bcast(
			void        *buffer,   # Указатель на буфер данных. В процессе, указанном параметром root, буфер содержит данные, подлежащие трансляции.
			int          count,    # Количество элементов данных в буфере.
			MPI_Datatype datatype, # Тип данных.
			int          root,     # Ранг процесса, отправляющего данные.
			MPI_Comm     comm      # Дескриптор коммуникатора MPI_Comm.
	);
	*/
	MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
	rest_rows = size;
	for (i = 0; i < process_rank; i++)
		rest_rows = rest_rows - rest_rows / (process_number - i);

	row_number = rest_rows / (process_number - process_rank);

	process_rows = new int[row_number * size];
	process_result = new int[row_number];
    result = new int[size];
	if (process_rank == 0) {
		matrix = new int[size * size];
		data_initialization(matrix, size);
	}
}
#pragma endregion

#pragma region DataDistribution
void data_distribution(int* matrix, int* process_rows, int size, int row_number) {
	int* send_counts; 
	int* displs;
	int rest_rows = size;

	send_counts = new int[process_number];
	displs = new int[process_number];

	send_counts[0] = row_number * size;
	row_number = (size / process_number);

	displs[0] = 0;

	for (int i = 1; i < process_number; i++) {
		rest_rows -= row_number;
		row_number = rest_rows / (process_number - i);
		send_counts[i] = row_number * size;
		displs[i] = displs[i - 1] + send_counts[i - 1];
	}

	/*
	int MPIAPI MPI_Scatterv(
	  _In_  void         *sendbuf,    # Указатель на буфер, содержащий данные, которые будут отправлены корневым процессом.
	  _In_  int          *sendcounts, # Количество элементов для отправки в каждый процесс.
	  _In_  int          *displs,     # Расположение данных для отправки в каждый процесс коммуникатора. Каждое местоположение в массиве относится к соответствующему элементу массива sendbuf.
			MPI_Datatype sendtype,    # Тип данных MPI каждого элемента в буфере.
	  _Out_ void         *recvbuf,    # Указатель на буфер, содержащий данные, полученные в каждом процессе. Количество и тип данных элементов в буфере указываются в параметрах recvcount и recvtype.
			int          recvcount,   # Количество элементов в буфере приема. Если количество равно нулю, то часть данных в сообщении пуста.
			MPI_Datatype recvtype,    # Тип данных элементов в буфере приема.
			int          root,        # Ранг в процессе отправки в указанном коммуникаторе.
			MPI_Comm     comm         # Дескриптор коммуникатора MPI_Comm.
	);
	*/
	MPI_Scatterv(matrix, send_counts, displs, MPI_INT, process_rows, send_counts[process_rank], MPI_INT, 0, MPI_COMM_WORLD);

	delete[] send_counts;
	delete[] displs;
}
#pragma endregion

#pragma region ParallelCalculation
void parallel_calculation(int* process_rows, int* process_result, int size, int row_number) {
	for (int i = 0; i < row_number; i++) {
        int max = process_rows[0];
		for (int j = 0; j < size; j++) {
			if ((j%2 ==0) && (process_rows[i * size + j] > max)) {
				max = process_rows[i * size + j];
			}
		}
		cout << "\nmax = " << max << endl << endl;
		process_result[i] = max;
	}
}
#pragma endregion

#pragma region ResultExtraction
void result_extraction(int* process_result, int* result, int size, int row_number) {
	int* receive_number;  
	int* receive_index;
	int rest_rows = size;
	receive_number = new int[process_number];
	receive_index = new int[process_number];
	receive_index[0] = 0;
	receive_number[0] = size / process_number;
	for (int i = 1; i < process_number; i++) {
		rest_rows -= receive_number[i - 1];
		receive_number[i] = rest_rows / (process_number - i);
		receive_index[i] = receive_index[i - 1] + receive_number[i - 1];
	}
	MPI_Allgatherv(process_result, receive_number[process_rank], MPI_INT, result ,receive_number, receive_index, MPI_INT, MPI_COMM_WORLD);
	delete[] receive_number;
	delete[] receive_index;
}
#pragma endregion

#pragma region DataPresentaion
void view_matrix(int* matrix, int n) {
	cout << endl;
	for (int i = 0; i < n * n; i++) {
		cout << matrix[i] << " ";
		if ((i+1) % n == 0)
			cout << endl;
	}

}
#pragma endregion

int main(int argc, char** argv) {

	vector <int> max_elements;

	srand(time(NULL));
	double start_time = 0, end_time = 0; // Будем использовать средства MPI Для подсчёта времени
	int n, sum = 0, max;

	int row_number;
	int* matrix = NULL;
	int* result = NULL;
	int* process_rows = NULL;
	int* process_result = NULL;

	MPI_Init(&argc, &argv); std::cout << "\nMPI was initialized\n";
	//Определение общего числа параллельных процессов в группе comm.
	MPI_Comm_size(MPI_COMM_WORLD, &process_number);
	//Определение ранга корневого процесса
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank); // process_rank - ранг (индекс процесса)
    if (process_rank == 0)
        std::cout << "Array amount: ", cin >> n;
    

	start_time = MPI_Wtime();
    cerr << "#" << process_rank << " : " << "About to start process_initialization" << endl;
	process_initialization(matrix, result, process_rows, process_result, n, row_number);
    cerr << "#" << process_rank << " : " << "process_initialization finished" << endl;
    cerr << "#" << process_rank << " : " << "About to start data_distribution" << endl;
	data_distribution(matrix, process_rows, n, row_number);
    cerr << "#" << process_rank << " : " << "data_distribution finished" << endl;
    cerr << "#" << process_rank << " : " << "About to start parallel_calculation" << endl;
	parallel_calculation(process_rows, process_result, n, row_number);
    cerr << "#" << process_rank << " : " << "parallel_calculation finished" << endl;
    cerr << "#" << process_rank << " : " << "About to start result_extraction" << endl;
	result_extraction(process_result, result, n, row_number);
    cerr << "#" << process_rank << " : " << "result_extraction finished" << endl;
	end_time = MPI_Wtime();
	double time = end_time - start_time;

	for (int i = 0; i < n; i++)
		sum += result[i];

	if (process_rank == 0) {
		view_matrix(matrix, n);
		cout << "\nAnswer: " << sum << endl;
		cout << "Execution time = " << time << endl;
	}

	MPI_Finalize(); cout << "\nMPI was finalized\n";

	return 0;
}

