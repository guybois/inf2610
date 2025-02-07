#include <iostream>
#include <atomic>
#include <pthread.h>

std::atomic<int> counter(0); // Compteur atomique

void* increment(void*) {
    for (int i = 0; i < 1000; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed);   // Avec memory_order_relaxed, chaque thread incrémente counter indépendamment.
    }
    return nullptr;
}

int main() {
    const int NUM_THREADS = 2;
    pthread_t threads[NUM_THREADS];

    // Création des threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], nullptr, increment, nullptr);
    }

    // Attente de la fin des threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], nullptr);
    }

    // Affichage du résultat final
    std::cout << "Counter: " << counter.load() << std::endl; // Affichera toujours 2000
    return 0;
}


