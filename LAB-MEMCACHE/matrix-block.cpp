#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

// Función para multiplicar matrices por bloques
void multiplyMatricesBlocked(const std::vector<std::vector<int>>& A, 
                             const std::vector<std::vector<int>>& B, 
                             std::vector<std::vector<int>>& C, int N, int blockSize) {
    for (int iBlock = 0; iBlock < N; iBlock += blockSize) {
        for (int jBlock = 0; jBlock < N; jBlock += blockSize) {
            for (int kBlock = 0; kBlock < N; kBlock += blockSize) {
                // Multiplicación de bloques
                for (int i = iBlock; i < std::min(iBlock + blockSize, N); ++i) {
                    for (int j = jBlock; j < std::min(jBlock + blockSize, N); ++j) {
                        int sum = 0;
                        for (int k = kBlock; k < std::min(kBlock + blockSize, N); ++k) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }
}

// Función para inicializar las matrices con valores aleatorios
void initializeMatrix(std::vector<std::vector<int>>& matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 10;  // Números aleatorios entre 0 y 9
        }
    }
}

int main() {
    // Tamaños de matrices a evaluar
    std::vector<int> sizes = {64, 128, 256, 512}; 

    // Tamaño del bloque para la multiplicación por bloques
    int blockSize = 64;  // Puedes ajustar este valor para optimizar

    for (int N : sizes) {
        // Crear matrices A, B y C de tamaño NxN
        std::vector<std::vector<int>> A(N, std::vector<int>(N));
        std::vector<std::vector<int>> B(N, std::vector<int>(N));
        std::vector<std::vector<int>> C(N, std::vector<int>(N));

        // Inicializar matrices A y B con valores aleatorios
        initializeMatrix(A, N);
        initializeMatrix(B, N);

        // Evaluar la multiplicación por bloques
        std::cout << "Evaluando la multiplicación por bloques con matrices de tamaño " << N << "x" << N << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        multiplyMatricesBlocked(A, B, C, N, blockSize);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = end - start;
        std::cout << "Tiempo para la multiplicación por bloques: " << elapsed.count() << " segundos" << std::endl;
    }
    return 0;
}