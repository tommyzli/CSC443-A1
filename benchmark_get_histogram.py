#!/usr/bin/python

import subprocess

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
        print("---- {} ----".format(name))
        subprocess.call(["./get_histogram", "/root/myDocuments/CSC443/tommys/CSC443/big_file", block_size])
        print("------------")
