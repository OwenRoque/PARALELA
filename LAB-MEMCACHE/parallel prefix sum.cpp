#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Sequential version of prefix sum
void sequential_prefix_sum(vector<int> &A) {
    int n = A.size();
    for (int i = 1; i < n; i++) {
        A[i] += A[i - 1];
    }
}

// Parallel version of prefix sum (simulated PRAM approach)
void parallel_prefix_sum(vector<int> &A) {
    int n = A.size();
    int logN = ceil(log2(n));

    // Outer loop simulating the number of iterations
    for (int i = 0; i < logN; i++) {
        // Inner loop, processing elements in parallel
        #pragma omp parallel for
        for (int j = pow(2, i); j < n; j++) {
            A[j] += A[j - pow(2, i)];
        }
    }
}

int main() {
    int n = 1000000; // Example size
    vector<int> A_seq(n, 1); // Sequential array
    vector<int> A_par(n, 1); // Parallel array

    // Run sequential version
    auto start_seq = high_resolution_clock::now();
    sequential_prefix_sum(A_seq);
    auto end_seq = high_resolution_clock::now();
    auto duration_seq = duration_cast<milliseconds>(end_seq - start_seq).count();
    cout << "Sequential Prefix Sum took " << duration_seq << " ms" << endl;

    // Run parallel version
    auto start_par = high_resolution_clock::now();
    parallel_prefix_sum(A_par);
    auto end_par = high_resolution_clock::now();
    auto duration_par = duration_cast<milliseconds>(end_par - start_par).count();
    cout << "Parallel (Simulated PRAM) Prefix Sum took " << duration_par << " ms" << endl;

    /* 
    // Display results
    cout << "Sequential Prefix Sum: ";
    for (int i = 0; i < n; i++) {
        cout << A_seq[i] << " ";
    }
    cout << endl;

    cout << "Parallel Prefix Sum: ";
    for (int i = 0; i < n; i++) {
        cout << A_par[i] << " ";
    }
    cout << endl;
    */
    return 0;
}
