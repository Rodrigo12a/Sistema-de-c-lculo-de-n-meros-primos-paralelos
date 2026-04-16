#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <omp.h>

// Base primes
std::vector<int> getBasePrimes(int limit) {
    std::vector<char> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    std::vector<int> primes;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) primes.push_back(i);
    }

    return primes;
}

// SECUENCIAL
int countPrimesSequential(int N, int M, const std::vector<int>& base_primes) {
    const int segment_size = 10000;
    int total_count = 0;

    for (int low = N; low <= M; low += segment_size) {
        int high = std::min(low + segment_size - 1, M);
        std::vector<char> is_prime(high - low + 1, true);

        for (int p : base_primes) {
            int start = std::max(p * p, ((low + p - 1) / p) * p);
            for (int j = start; j <= high; j += p) {
                is_prime[j - low] = false;
            }
        }

        for (int i = 0; i < is_prime.size(); i++) {
            if (is_prime[i]) total_count++;
        }
    }

    return total_count;
}

// PARALELO
int countPrimesParallel(int N, int M, const std::vector<int>& base_primes) {
    const int segment_size = 10000;
    int total_count = 0;

    #pragma omp parallel for reduction(+:total_count) schedule(static)
    for (int low = N; low <= M; low += segment_size) {
        int high = std::min(low + segment_size - 1, M);
        std::vector<char> is_prime(high - low + 1, true);

        for (int p : base_primes) {
            int start = std::max(p * p, ((low + p - 1) / p) * p);
            for (int j = start; j <= high; j += p) {
                is_prime[j - low] = false;
            }
        }

        for (int i = 0; i < is_prime.size(); i++) {
            if (is_prime[i]) total_count++;
        }
    }

    return total_count;
}

int main() {
    int N, M;

    std::cout << "Ingrese N: ";
    std::cin >> N;

    std::cout << "Ingrese M: ";
    std::cin >> M;

    if (N > M) {
        std::cerr << "Error: N > M\n";
        return 1;
    }

    if (M < 2) {
        std::cout << "No hay primos\n";
        return 0;
    }

    if (N < 2) N = 2;

    int limit = std::sqrt(M);
    std::vector<int> base_primes = getBasePrimes(limit);

    // --- SECUENCIAL ---
    auto start_seq = std::chrono::high_resolution_clock::now();
    int seq_count = countPrimesSequential(N, M, base_primes);
    auto end_seq = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> time_seq = end_seq - start_seq;

    // --- PARALELO ---
    auto start_par = std::chrono::high_resolution_clock::now();
    int par_count = countPrimesParallel(N, M, base_primes);
    auto end_par = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> time_par = end_par - start_par;

    // --- RESULTADOS ---
    std::cout << "\nResultados:\n";
    std::cout << "Secuencial: " << seq_count << " primos\n";
    std::cout << "Paralelo:   " << par_count << " primos\n";

    if (seq_count != par_count) {
        std::cerr << "ERROR: resultados diferentes\n";
        return 1;
    }

    // --- MÉTRICAS ---
    double speedup = time_seq.count() / time_par.count();

    std::cout << "\nTiempos:\n";
    std::cout << "Secuencial: " << time_seq.count() << " ms\n";
    std::cout << "Paralelo:   " << time_par.count() << " ms\n";

    std::cout << "\nSpeedup: " << speedup << "x\n";
    std::cout << "Hilos: " << omp_get_max_threads() << "\n";

    return 0;
}