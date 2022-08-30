# file-compression-and-decompression-based-on-huffman-code

## Introduction
Compression software has been used more and more frequently in our daily lives. However, few people knows how compression software works to help us compress the files and save the memory.In this program, we implement the huffman algorithm in C++ which could help you learn and understand the secrets behind compression/decompression. Without losing any bits in the original files, huffman algorithm is a strong and efficient way to compress/decompress files. We will explain the methodology behind this project below.

## Implementation Details
In this project, we strictly follow the huffman algorithm. Below are the procedures for compressing and decompressing. Please check Compression.cpp and Decompression.cpp if you have any questions for the inner work of huffman algorithm.

### Compression
- Read the input files and generate the frequency table for each characters.
- Build the huffman tree by using priority queue.
- Using the huffman tree to genrate a hash map where key is the character in input file and value is the huffman code.
- Put header which contain the compressed huffman tree to the out put file.
- Read one byte step by step and transfrom it into huffman-code we generated.

### Decompression
- Read the header from the file we wanna decompressed, and generate the huffman tree from it.
- Read one byte step by step and decompressed the whole files.

## Performance
- TXT files

- DOC files

- Multiple files


