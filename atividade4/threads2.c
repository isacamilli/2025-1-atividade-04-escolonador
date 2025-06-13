#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <math.h>

// Thread CPU-bound (cálculo de π com série de Leibniz)
void* cpu_thread(void* arg) {
    long id = (long)arg;
    printf("Thread CPU-bound %ld iniciada (PID: %d)\n", id, getpid());

    double pi = 0.0;
    long iterations = 100000000; // 100 milhões

    for (long k = 0; k < iterations; k++) {
        pi += (k % 2 == 0 ? 1.0 : -1.0) / (2.0 * k + 1.0);
    }
    pi *= 4;

    printf("Thread CPU-bound %ld terminou (π ≈ %.15f)\n", id, pi);
    return NULL;
}

// Thread I/O-bound (simula operação I/O com sleep)
void* io_thread(void* arg) {
    long id = (long)arg;
    printf("Thread I/O-bound %ld iniciada (PID: %d)\n", id, getpid());
    sleep(2);  // Simula operação I/O
    printf("Thread I/O-bound %ld terminou\n", id);
    return NULL;
}

int main() {
    pid_t pid;
    pthread_t thread_cpu1, thread_cpu2, thread_cpu3;
    pthread_t thread_io1, thread_io2, thread_io3;

    // Cria processo filho
    pid = fork();

    if (pid == 0) { // Processo filho
        printf("\nProcesso filho (PID: %d)\n", getpid());

        // Cria threads CPU-bound
        pthread_create(&thread_cpu1, NULL, cpu_thread, (void*)1);
        pthread_create(&thread_cpu2, NULL, cpu_thread, (void*)2);
        pthread_create(&thread_cpu3, NULL, cpu_thread, (void*)3);

        // Cria threads I/O-bound
        pthread_create(&thread_io1, NULL, io_thread, (void*)1);
        pthread_create(&thread_io2, NULL, io_thread, (void*)2);
        pthread_create(&thread_io3, NULL, io_thread, (void*)3);

        // Espera todas as threads terminarem
        pthread_join(thread_cpu1, NULL);
        pthread_join(thread_cpu2, NULL);
        pthread_join(thread_cpu3, NULL);
        pthread_join(thread_io1, NULL);
        pthread_join(thread_io2, NULL);
        pthread_join(thread_io3, NULL);

    } else if (pid > 0) { // Processo pai
        printf("Processo pai (PID: %d)\n", getpid());
        wait(NULL); // Espera o filho terminar
    }

    return 0;
}
