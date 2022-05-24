#include <mpi.h>
#include <iostream>

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

#define SIZE 5
#define ROOT 0
#define FROM_ROOT 1
#define FROM_WORKER 2

int process_number = 0; // Number of available processes 
int process_rank = 0; //Process rank of current process 


#pragma region DataPresentation
void view_matrix(double** matrix, const int rows, const int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
#pragma endregion

#pragma region DataAllocation
double** allocate_array(int rows, int cols) {
	double* data = new double[rows * cols];
	double** result = new double* [rows];
	for (int i = 0; i < rows; i++)
		result[i] = data + i * cols;
	return result;
}
#pragma endregion

#pragma region DataTranspose
double** transpose(double** matrix, int rows, int cols) {
	double** result = allocate_array(cols, rows);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			result[j][i] = matrix[i][j];
	return result;
}
#pragma endregion

#pragma region DataRemovimg
void delete_array(double** array) {
	delete[] array[0];
	delete[] array;
}
#pragma endregion

/*
int MPIAPI MPI_Sendrecv(
  _In_  void         *sendbuf,
		int          sendcount,
		MPI_Datatype sendtype,
		int          dest,
		int          sendtag,
  _Out_ void         *recvbuf,
		int          recvcount,
		MPI_Datatype recvtype,
		int          source,
		int          recvtag,
		MPI_Comm     comm,
  _Out_ MPI_Status   *status
);
*/


int main(int argc, char* argv[]) {
	int process_number;
	int process_rank;
	double** matrix;
	double sum = 0;
	int rc = 1;
	int num_workers;
	int averow, extra, offset;
	int rows;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &process_number);
	if (process_number < 2) {
		cout << "Need at least 2 mpi tasks" << endl;
		MPI_Abort(MPI_COMM_WORLD, rc);
		exit(rc);
	}
	num_workers = process_number - 1;

	//////////// ROOT /////////////
	if (process_rank == ROOT) {
		matrix = allocate_array(SIZE, SIZE);

		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				matrix[i][j] = rand() % 5;

		view_matrix(matrix, SIZE, SIZE);

		double start = MPI_Wtime();

		averow = SIZE / num_workers;
		extra = SIZE % num_workers;
		offset = 0;
		//////////// SEND DATA TO WORKERS ///////////////
		//int** transposal = transpose(matrix, SIZE, SIZE); // на случай, если нужно по столбцам, можно транспонировать
		for (int dest = 1; dest <= num_workers; dest++) {
			rows = (dest <= extra) ? averow + 1 : averow;

			MPI_Send(&offset, 1, MPI_INT, dest, FROM_ROOT, MPI_COMM_WORLD);
			MPI_Send(&rows, 1, MPI_INT, dest, FROM_ROOT, MPI_COMM_WORLD);
			MPI_Send(&matrix[offset][0], rows * SIZE, MPI_DOUBLE, dest, FROM_ROOT, MPI_COMM_WORLD);
			offset += rows;
		}
		//////////// RECIVE FROM WORKERS AND CALCULATE ///////////////
		double result = 0;
		for (int src = 1; src <= num_workers; src++) {
			MPI_Recv(&offset, 1, MPI_INT, src, FROM_WORKER, MPI_COMM_WORLD, &status);
			MPI_Recv(&rows, 1, MPI_INT, src, FROM_WORKER, MPI_COMM_WORLD, &status);
			MPI_Recv(&sum, 1, MPI_DOUBLE, src, FROM_WORKER, MPI_COMM_WORLD, &status);
			result += sum;
		}

		double finish = MPI_Wtime();
		printf("Done in %f seconds.\n", finish - start);
		cout << "result: " << result << endl;
	}

	//////////// WORKER /////////////
	if (process_rank != ROOT) {
		MPI_Recv(&offset, 1, MPI_INT, ROOT, FROM_ROOT, MPI_COMM_WORLD, &status);
		MPI_Recv(&rows, 1, MPI_INT, ROOT, FROM_ROOT, MPI_COMM_WORLD, &status);
		matrix = allocate_array(rows, SIZE);

		MPI_Recv(&matrix[0][0], rows * SIZE, MPI_DOUBLE, ROOT, FROM_ROOT, MPI_COMM_WORLD, &status);
		
		for (int i = 0; i < rows; i++) {
			int max = matrix[i][0];
			for (int j = 0; j < SIZE; j++) {
				cout << " #" << matrix[i][j] << " ";
				if ((j % 2 == 0) && (matrix[i][j] > max))
					max = matrix[i][j];
			}
			cout << " max = " << max << " process = " << process_rank << endl;
			sum += max;
		}
		MPI_Send(&offset, 1, MPI_INT, ROOT, FROM_WORKER, MPI_COMM_WORLD);
		MPI_Send(&rows, 1, MPI_INT, ROOT, FROM_WORKER, MPI_COMM_WORLD);
		MPI_Send(&sum, 1, MPI_DOUBLE, ROOT, FROM_WORKER, MPI_COMM_WORLD);
	}
	MPI_Finalize();

	return 0;
}
