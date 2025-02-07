#include <iostream>
#include <atomic>
#include <pthread.h>
#include <unistd.h>  // Pour usleep()

std::atomic_flag lock = ATOMIC_FLAG_INIT;  // Initialisation du verrou

void* critical_section(void* arg) {
    int id = *reinterpret_cast<int*>(arg);

    while (lock.test_and_set(std::memory_order_acquire)) {
        // Attente active (spinlock)
    }

    // Section critique
    std::cout << "Thread " << id << " entre dans la section critique\n";
    usleep(100000);  // Simulation de travail (100ms)

    // Libération du verrou
    lock.clear(std::memory_order_release);
    std::cout << "Thread " << id << " quitte la section critique\n";

    return nullptr;
}

int main() {
    const int NUM_THREADS = 2;
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS] = {1, 2};

    // Création des threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], nullptr, critical_section, &thread_ids[i]);
    }

    // Attente de la fin des threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], nullptr);
    }

    return 0;
}

