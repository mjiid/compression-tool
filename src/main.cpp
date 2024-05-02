#include <iostream>
#include "huffman.h"
#include "utils.h"

using namespace std;

int main() {
    string inputFile = "input/input.txt";
    string compressedFile = "compressed.bin";
    string decompressedFile = "decompressed.txt";

    // Compress input file
    compressFile(inputFile, compressedFile);
    cout << "File compressed successfully." << endl;

    // Decompress the compressed file
    decompressFile(compressedFile, decompressedFile);
    cout << "File decompressed successfully." << endl;

    return 0;
}
