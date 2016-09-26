CC = gcc

create_random_file: create_random_file.c create_random_file.o
	$(CC) -Wall -o $@ create_random_file.o

# get_histogram: get_histogram.c library.o
#     $(CC) -Wall -o $@ $< library.o


clean:
	-rm *.o
