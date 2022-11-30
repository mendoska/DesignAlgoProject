#include <iostream>
#include<stdlib.h>
#include <vector>
#include <chrono>

class TimeAlg {
public:
	std::vector <int> n; //where i'll store the total of n 
	std::vector <int> j; //iterations
	std::vector <std::chrono::duration<float>> duration;
	std::chrono::duration<float> averageTime;
	std::vector <std::chrono::duration<float>> averageTimeN;
};

//function declarations
void INSERTIONSORT(std::vector<int> &A, int n);
void BUILDMAXHEAP(std::vector<int>& ,int n);
void MAXHEAPIFY(std::vector <int>& A, int i, int n);
void HEAPSORT(std::vector<int>& A, int n);
int PARTITION(std::vector<int>& A, int p, int r);
int RANDOMIZED_PARTITION(std::vector<int>& A, int p, int r);
int RANDOMIZED_SELECT(std::vector <int>& A, int p, int r, int i);
void ALG1(std::vector<int> &A, int n, int i);
void ALG2(std::vector<int> &A, int n, int i);
void ALG3(std::vector<int> &A, int n, int i);


void INSERTIONSORT(std::vector<int>& A, int n) {

	for (int j = 1; j <= n; j++) {
		int key = A[j];
		//insert A[j] into the sorted sequence A[1...j-1]
		int i = j - 1;

		while (i >= 0 && A[i] > key) {
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}

	/*used for testing
	std::cout << "This is the sorted vector \n";
	for (int i = 0; i <= n; i++) {
		std::cout << A[i] << std::endl;
	}*/


}
void BUILDMAXHEAP(std::vector<int>& A,int n) {
	//int n = A.size() - 1;

	for (int i = floor(n / 2); i >= 0; i--) {
		MAXHEAPIFY(A, i, n);
	}
}
void MAXHEAPIFY(std::vector <int>& A, int i, int n) {
	//int n = A.size()-1;
	int l = ((2 * i) + 1); //left, remember index 0
	int r = ((2 * i) + 2);//right
	int largest = NULL;

	if (l <= n && A[l] > A[i]) {
		largest = l;
	}
	else {
		largest = i;
	}
	if (r <= n && A[r] > A[largest]) {
		largest = r;
	}
	if (largest != i) {
		int temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;
		MAXHEAPIFY(A, largest, n);
	}
}
void HEAPSORT(std::vector<int>& A, int n) {
	//int n = (A.size() - 1); //heap-size
	BUILDMAXHEAP(A,n);
	for (int i = n; i > 0; i--) {
		int temp = A[0];
		A[0] = A[i];
		A[i] = temp;
		n--;
		MAXHEAPIFY(A, 0, n);
	}

	////used for testing
	//std::cout << "This is the sorted vector \n";
	//for (int i = 0; i < A.size(); i++) {
	//	std::cout << A[i] << std::endl;
	//}


}
int PARTITION(std::vector<int>& A, int p, int r) {
	int x = A[r];
	int i = p - 1;
	for (int j = p; j < (r - 1); j++) {
		if (A[j] <= x) {
			i++;
			int temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}
	int temp = A[r];
	A[r] = A[i + 1];
	A[i + 1] = temp;
	return i + 1;
}
int RANDOMIZED_PARTITION(std::vector<int>& A, int p, int r) {
	int i = (rand() % (r - p + 1) + p); //rand()%(max-min + 1) + min
	int temp = A[r];
	A[r] = A[i];
	A[i] = temp;
	return PARTITION(A, p, r);
}
int RANDOMIZED_SELECT(std::vector <int>& A, int p, int r, int i) {
	if (p == r) {
		return A[p];
	}
	int q = RANDOMIZED_PARTITION(A, p, r);
	int k = (q - p) + 1;
	if (i == k) {
		return A[q];
	}
	else if (i < k) {
		return RANDOMIZED_SELECT(A, p, q - 1, i);
	}
	else {
		return RANDOMIZED_SELECT(A, q + 1, r, i - k);
	}
}
void ALG1(std::vector<int> &A, int n, int i) {
	INSERTIONSORT(A, n);
	//commenting out display to console because of spam and slower performance
	//std::cout << "Insertion sort: " << A[i]<<"\n";
}

void ALG2(std::vector<int> &A, int n, int i) {
	HEAPSORT(A, n);
	//commenting out display to console because of spam and slower performance
	//std::cout << "heap sort: " << A[i] << "\n";
}

void ALG3(std::vector<int> &A, int n, int i) {
	int x = RANDOMIZED_SELECT(A, 1, n, i);
	//commenting out display to console because of spam and slower performance
	//std::cout << "Randomized select: " << x << "\n";
	
}





int main() {

	//const int MAX = 100000; // size of array
	//int MAX = 30;
	//int* A = new int[MAX]; //located on heap
	int m = 5;
	std::vector<int> A;

	//used for testing
	//std::vector<int> test = {5,2,3,8,7,4};
	//std::vector<int> test = { 4,5,2,14,20,7};
	//std::vector<int> test = { 80,1,54,7,25,48,52,4,64,74,0 };

	/*std::cout << "This is the unsorted vector\n";
	for (int i = 0; i < test.size(); i++) {
		std::cout << test[i] << std::endl;
	}*/

//	ALG1(test,test.size()-1,1);
//	ALG2(test,(test.size()-1),2);
//	ALG3(test, (test.size()-1), 1);


	TimeAlg timeAlg1;
	TimeAlg timeAlg2;
	TimeAlg timeAlg3;

	for (int j = 1; j <= m; j++) {
		A.clear();//clear vector every iteration
		for (int k = 0; k < 10000; k++) {
			A.push_back(rand());
		}
		for (int n = 1000; n <= 10000; n = n + 1000) {
			int i = floor(2 * n / 3);
			
			//ALG1
			std::vector<int> B(n);
			for (int j = 0; j < n; j++) {
				B[j] = A[j];
			}
			std::chrono::time_point<std::chrono::steady_clock> time1 = std::chrono::high_resolution_clock::now();
			//ALG1 Function
			ALG1(B, n-1, i);
			std::chrono::time_point<std::chrono::steady_clock> time2 = std::chrono::high_resolution_clock::now();

			//creating a class to store information needed for calculation.
			std::chrono::duration<float > diff = time2 - time1;
			timeAlg1.n.push_back(n);
			timeAlg1.j.push_back(j);
			timeAlg1.duration.push_back(diff);


			//ALG2
			
			for (int j = 0; j < n; j++) {
				B[j] = A[j];
			}

			 time1 = std::chrono::high_resolution_clock::now();
			//ALG2 Function
			 ALG2(B,n-1,i);
			 time2 = std::chrono::high_resolution_clock::now();
			 diff = time2 - time1;
			timeAlg2.n.push_back(n);
			timeAlg2.j.push_back(j);
			timeAlg2.duration.push_back(diff);


			 //ALG 3
			 for (int j = 0; j < n; j++) {
				 B[j] = A[j];
			 }
			 time1 = std::chrono::high_resolution_clock::now();
			 ALG3(B, n - 1, i);
			 time2 = std::chrono::high_resolution_clock::now();
			 diff = time2 - time1;
			 timeAlg3.n.push_back(n);
			 timeAlg3.j.push_back(j);
			 timeAlg3.duration.push_back(diff);

		}
	}


	///
	//std::cout << "Hi\n";
	
	TimeAlg t1Avg;
	TimeAlg t2Avg;
	TimeAlg t3Avg;

	//computing the average values
	for (int n = 1000; n <= 10000; n = n + 1000) {
		//alg1
		for (int j = 0; j < timeAlg1.n.size(); j++) {
			if (timeAlg1.n[j] == n) {
				//first three lines of code are used so I can reference where I'm getting each value
				//last line of code is to do total calculation
				t1Avg.n.push_back(timeAlg1.n[j]);
				t1Avg.j.push_back(timeAlg1.j[j]);
				t1Avg.duration.push_back(timeAlg1.duration[j]);
				t1Avg.averageTime += timeAlg1.duration[j];
			}
		}
		//this is calculating the average and pushing it onto a vector that will be used for analysis
		t1Avg.averageTime = t1Avg.averageTime / m;
		t1Avg.averageTimeN.push_back(t1Avg.averageTime);
		
		//alg2	
		for (int j = 0; j < timeAlg2.n.size(); j++) {
			if (timeAlg2.n[j] == n) {
				t2Avg.n.push_back(timeAlg2.n[j]);
				t2Avg.j.push_back(timeAlg2.j[j]);
				t2Avg.duration.push_back(timeAlg2.duration[j]);
				t2Avg.averageTime += timeAlg2.duration[j];
			}
		}
		t2Avg.averageTime = t2Avg.averageTime / m;
		t2Avg.averageTimeN.push_back(t2Avg.averageTime);

		//alg3
		for (int j = 0; j < timeAlg3.n.size(); j++) {
			if (timeAlg3.n[j] == n) {
				t3Avg.n.push_back(timeAlg2.n[j]);
				t3Avg.j.push_back(timeAlg3.j[j]);
				t3Avg.duration.push_back(timeAlg3.duration[j]);
				t3Avg.averageTime += timeAlg3.duration[j];
			}
		}
		t3Avg.averageTime = t3Avg.averageTime / m;
		t3Avg.averageTimeN.push_back(t3Avg.averageTime);
	
	}
	
	////used for breakpoint to test values 
	//std::cout << "test\n";

	//displaing average values

	//alg 1
	int inputSz = 0;
	std::cout << "These are the average times for insertion sort: \n";
		for (int l = 0; l < t1Avg.averageTimeN.size(); l++) {
			//used for display purposes
			
			std::cout << "AVG TIME for input size "<<t1Avg.n[inputSz] << ": " << t1Avg.averageTimeN[l].count() * 100 << " milliseconds" << "\n";
			inputSz = inputSz + 5;
		}

	//alg 2
		inputSz = 0;
	std::cout << "\nThese are the average times for heap sort: \n";
		for (int l = 0; l < t2Avg.averageTimeN.size(); l++) {
			std::cout <<"AVG TIME for input size " << t2Avg.n[inputSz] << ": " << t2Avg.averageTimeN[l].count() * 100 << " milliseconds" << "\n";
			inputSz = inputSz + 5;
		}

	//alg 3
		inputSz = 0;
	std::cout << "\nThese are the average times for randomized select: \n";
		for (int l = 0; l < t3Avg.averageTimeN.size(); l++) {
			std::cout << "AVG TIME for input size " << t3Avg.n[inputSz] << ": " << t3Avg.averageTimeN[l].count() * 100 << " milliseconds" << "\n";
			inputSz = inputSz + 5;
		}

	//used for breakpoint to test values 



return 0;
}
