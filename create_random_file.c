#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/timeb.h>

void random_array(char *array, long bytes) {
    long i;
    for (i = 0; i < bytes; i++) {
        char val = 'A' + (rand() % 26);
        array[i] = val;
    }
}

int main(int argc, char* argv[]) {
    int remove_file_after_completion = 1;
    int print_result = 1;
    if (argc >= 5) {
        // check for optional arguments
        int index;
        for (index = 4; index < argc; index++) {
            if (strcmp(argv[index], "--persist-file") == 0) {
                remove_file_after_completion = 0;
            } else if (strcmp(argv[index], "--no-output") == 0) {
                print_result = 0;
            }
        }
    } else if (argc != 4) {
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
    if (remove_file_after_completion) {
        remove(file_name);
    }

    if (print_result) {
        printf("BLOCK_SIZE: %ld    RATE IN BYTES/S: %ld    TIME IN MS: %ld\n", block_size, total_bytes / execution_time_in_ms / 1000, execution_time_in_ms);
    }
    return 0;
}
