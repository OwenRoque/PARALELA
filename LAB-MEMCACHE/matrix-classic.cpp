#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

// Función para multiplicar matrices clásicamente
void multiplyMatrices(const std::vector<std::vector<int>>& A, 
                      const std::vector<std::vector<int>>& B, 
                      std::vector<std::vector<int>>& C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
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

        // Evaluar la multiplicación clásica
        std::cout << "Evaluando la multiplicación clásica con matrices de tamaño " << N << "x" << N << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        multiplyMatrices(A, B, C, N);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Tiempo para la multiplicación clásica: " << elapsed.count() << " segundos" << std::endl;
    }
    return 0;
}
