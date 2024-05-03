#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *array;
    int start;
    int end;
} ThreadData;

void *write_random_numbers(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    for (int i = data->start; i < data->end; i++) {
        data->array[i] = rand();
    }
    int size = data->end - data->start +1;
    int x;
    while(1){
            for( int i=data->start; i<data->end; i++ ){
                x = data->array[i];
            }
    }
    

    return NULL;
}

int main(int argc, char *argv[]) {
    int i=0;
    if (argc != 3) {
        printf("Usage: %s <memory size in MB> <number of threads>\n", argv[0]);
        return 1;
    }

    int memory_size = atoi(argv[1]) * 1024 * 1024 / sizeof(int); // Convert MB to number of integers
    int num_threads = atoi(argv[2]);

    int *array = malloc(memory_size * sizeof(int));
    if (array == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    ThreadData *thread_data = malloc(num_threads * sizeof(ThreadData));

    int chunk_size = memory_size / num_threads;

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].array = array;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == num_threads - 1) ? memory_size : (i + 1) * chunk_size;

        if (pthread_create(&threads[i], NULL, write_random_numbers, &thread_data[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

   
    free(array);
    free(threads);
    free(thread_data);

    return 0;
}