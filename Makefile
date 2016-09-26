CC = gcc

all: create_random_file get_histogram

create_random_file: create_random_file.c create_random_file.o
	$(CC) -Wall -o $@ create_random_file.o

get_histogram: get_histogram.c get_histogram.o
	$(CC) -Wall -o $@ get_histogram.o

clean:
	-rm *.o
