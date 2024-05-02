#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>

struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Function declarations for compression and decompression
void compressFile(const std::string& inputFile, const std::string& outputFile);
void decompressFile(const std::string& inputFile, const std::string& outputFile);

#endif // HUFFMAN_H

