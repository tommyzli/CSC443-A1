#!/usr/bin/python

import subprocess
import os


BLOCK_SIZES = [
    ("100", "100B"),
    ("2048", "2KB"),
    ("8192", "8KB"),
    ("16384", "16KB"),
    ("32768", "32KB"),
    ("65536", "64KB"),
    ("262144", "256KB"),
    ("524288", "512KB"),
    ("1048576", "1MB"),
    ("3145728", "3MB"),
]

# FILE_SIZE = "10485760"  # 10 MB
FILE_SIZE = "104857600"  # 100 MB

if __name__ == "__main__":
    for block_size, name in BLOCK_SIZES:
        print("-------- {} --------".format(name))

        for i in range(0, 5):
            subprocess.call(["./create_random_file", "big_file", FILE_SIZE, "4096", "--persist-file", "--no-output"])
            code = subprocess.call(["./get_histogram", "big_file", block_size, "--no-histogram"])
            if code != 0:
                print("error occurred")
            os.remove("big_file")

        print("--------------------")
