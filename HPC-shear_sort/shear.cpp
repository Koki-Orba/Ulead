/**
 * LEAD University
 * Data Science Program
 * BCD-9218: Parallel and Distributed Computing
 * Instructor Diego Jimenez, Eng. (diego.jimenez@ulead.ac.cr)
 *  OpenMP parallel shear sort.
 */

#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <math.h>
#include "timer.h"
#include "io.h"

#define MAX_VALUE 10000

// Shear sort function
void shear_sort(int **A, int M){
#pragma omp parallel for
        for (int i = 0; i < M-1; i++) {

            //Normal (bubble sort)
            for (int j = 0; j < M-1; j++) {
                int m = i;
                int n = j + 1;
                while (true) {
                    if (n == M-1) {
                        n = 0;
                        m++;
                        if (m == M-1) break; //stop
                    }

                    if (A[i][j] > A[m][n]) std::swap(A[i][j], A[m][n]);

                    n++;
                }
            }
           // }

            // Reverse (bubble sort)
            for (int j = 0; j > M-1; j++) {
                int m = i;
                int n = j - 1;
                while (true) {
                    if (n == M-1) {
                        n = 0;
                        m++;
                        if (m == M-1) break; //stop
                    }
                    if (A[i][j] > A[m][n]) std::swap(A[i][j], A[m][n]);
                    n++;
                }
            }
        }
    }

// Main method
int main(int argc, char* argv[]) {
	int N, M;
	int **A;
	double elapsedTime;

	// checking parameters
	if (argc != 2 && argc != 3) {
		cout << "Parameters: <N> [<file>]" << endl;
		return 1;
	}
	N = atoi(argv[1]);
	M = (int) sqrt(N);
	if(N != M*M){
		cout << "N has to be a perfect square!" << endl;
		exit(1);
	}

	// allocating matrix A
	A = new int*[M];
	for (int i=0; i<M; i++){
		A[i] = new int[M];
	}

	// reading files (optional)
	if(argc == 3){
		readMatrixFile(A,M,argv[2]);
	} else {
		srand48(time(NULL));
		for(int i=0; i<M; i++){
			for(int j=0; j<M; j++){
				A[i][j] = lrand48() % MAX_VALUE;
			}
		}
	}

	// starting timer
	timerStart();

	// calling shear sort function
	shear_sort(A,M);

	// testing the results is correct
	if(argc == 3){
		printMatrix(A,M);
	}

	// stopping timer
	elapsedTime = timerStop();

	cout << "Duration: " << elapsedTime << " seconds" << std::endl;

	// releasing memory
	for (int i=0; i<M; i++) {
		delete [] A[i];
	}
	delete [] A;

	return 0;
}
