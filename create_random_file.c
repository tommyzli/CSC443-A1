#include <stdlib.h>
#include <stdio.h>
#include <sys/timeb.h>

void random_array(char *array, long bytes) {
    long i;
    for (i = 0; i < bytes; i++) {
        char val = 'A' + (rand() % 26);
        array[i] = val;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Invalid amount of arguments, please input the format:\n");
        printf("./create_random_file <filename> <total_bytes> <block_size>\n");
        exit(1);
    }

    char* file_name = argv[1];

    char *other = NULL;
    long total_bytes = strtol(argv[2], &other, 10);

    if (*other) {
        printf("Invalid total bytes.\n");
        exit(1);
    }

    long block_size = strtol(argv[3], &other, 10);

    if (*other || block_size > total_bytes) {
        printf("Invalid block size.\n");
        exit(1);
    }

    char *buffer = malloc(block_size * sizeof(char));

    FILE *fp = fopen(file_name, "w");

    long execution_time_in_ms = 0;
    long start_time_in_ms;
    long time_diff;
    struct timeb t;

    int pages = total_bytes / block_size;
    long written_bytes = total_bytes;
    int i;
    for (i = 0; i < pages; i++) {
        random_array(buffer, block_size);

        ftime(&t);
        start_time_in_ms = t.time * 1000 + t.millitm;
        
        fwrite(buffer, sizeof(char), block_size, fp);
        fflush(fp);

        ftime(&t);
        time_diff = t.time * 1000 + t.millitm - start_time_in_ms;
        execution_time_in_ms += time_diff;

        written_bytes -= block_size;
    }

    if (written_bytes > 0) {
        random_array(buffer, written_bytes);

        ftime(&t);
        start_time_in_ms = t.time * 1000 + t.millitm;

        fwrite(buffer, sizeof(char), written_bytes, fp);
        fflush(fp);

        ftime(&t);
        time_diff = t.time * 1000 + t.millitm - start_time_in_ms;
        execution_time_in_ms += time_diff;
    }

    fclose(fp);
    remove(file_name);

    printf("Total bytes written: %ld\n", total_bytes);
    printf("Block size: %ld\n", block_size);
    printf("Total write time in ms: %ld\n", execution_time_in_ms);
    printf("Rate in bytes/s: %ld\n", total_bytes / execution_time_in_ms / 1000);
    return 0;
}
