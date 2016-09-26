#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/timeb.h>

int histogram_length = 26;

int get_position_in_alphabet(char c) {
    return c - 'A';
}

int get_histogram(FILE *file_ptr,
                  long hist[],
                  long block_size,
                  long *miliseconds,
                  long *total_bytes_read) {

    char *buffer = malloc(block_size * sizeof(char));

    int j;
    for (j = 0; j < histogram_length; j++) {
        hist[j] = 0;
    }

    fseek(file_ptr, 0, SEEK_END);
    long file_size = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_SET);

    *total_bytes_read = 0;

    while (*total_bytes_read != file_size) {
        bzero(buffer, block_size * sizeof(char));
        int chunk_read = fread(buffer, sizeof(char), block_size * sizeof(char), file_ptr);

        int i;
        for (i = 0; i < histogram_length; i++) {
            char c = buffer[i];
            hist[get_position_in_alphabet(c)]++;
        }

        *total_bytes_read += chunk_read;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Invalid amount of arguments, please input the format:\n");
        printf("./get_histogram <filename> <block_size>\n");
        exit(1);
    }

    char* file_name = argv[1];

    char *other = NULL;

    long block_size = strtol(argv[2], &other, 10);
    if (*other) {
        printf("Invalid block size.\n");
        exit(1);
    }

    FILE *fp = fopen(file_name, "r");
    long hist[histogram_length];
    long miliseconds;
    long filelen;

    get_histogram(fp, hist, block_size, &miliseconds, &filelen);

    int i;
    for (i = 0; i < histogram_length; i++) {
        printf("%c %ld\n", i + 'A', hist[i]);
    }

    fclose(fp);
    return 0;
}
