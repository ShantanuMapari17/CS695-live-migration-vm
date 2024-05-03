#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>

#define PAGE_SIZE 4096 // Assume page size is 4KB

int main(int argc, char *argv[]) {
    // Allocate memory for NUM_PAGES pages
    if (argc != 3) {
        printf("Usage: %s <number of pages> <write rate>\n", argv[0]);
        return 1;
    }

    /*FILE *file = fopen("dirty-output.txt", "w");
    if(file == NULL) {
        printf("Error opening file\n");
        return 1;
    }*/

    time_t now = time(NULL);
    char timestamp[100];
    int NUM_PAGES = atoi(argv[1]);
    int WRITE_RATE = atoi(argv[2]);

    // Allocate memory for NUM_PAGES pages
    size_t total_size = NUM_PAGES * PAGE_SIZE;
    void *memory = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED) {
        perror("Failed to allocate memory");
        return 1;
    }
    int dirty_pages = 0;

    printf("Simulating dirty page rate of %d pages per second...\n", WRITE_RATE);

    while (1) {
        // Simulate writing to multiple pages per second
        for (int i = 0; i < WRITE_RATE; i++) {
            // We'll randomly choose a page index to mark as dirty
            int page_index = rand() % NUM_PAGES;
            void *page_address = memory + (page_index * PAGE_SIZE);

            // Mark the page as dirty
            *(int *)page_address = rand();
            dirty_pages++;
        }

        // Simulate processing or other activity
        // Here, we're just sleeping for one second
        sleep(1);

        // Print current status
        printf("Dirty pages: %d/%d\n", dirty_pages, NUM_PAGES);
        // strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

        // fprintf(file, "%s Dirty pages: %d/%d\n", timestamp, dirty_pages, NUM_PAGES);
        // fflush(file);
    }

    // Unmap the memory
    if (munmap(memory, total_size) == -1) {
        perror("Failed to deallocate memory");
        return 1;
    }

    //fclose(file);
    return 0;
}