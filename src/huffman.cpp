#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <bitset>
#include "huffman.h"

using namespace std;

// Comparison struct to order priority queue
struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) const {
        return a->frequency > b->frequency;
    }
};

// Global variable to track number of padding bits
int numPaddingBits = 0;

// Helper function to build Huffman tree from frequency map
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;

    // Create leaf nodes for each character and add to min-heap
    for (const auto& pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // Build tree by merging nodes until only one node remains
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* merged = new HuffmanNode('$', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;
        minHeap.push(merged);
    }

    return minHeap.top();
}



// Generate Huffman codes using DFS traversal of Huffman tree
void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& codes) {
    if (root == nullptr) return;

    if (root->data != '$') {
        codes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", codes);
    generateHuffmanCodes(root->right, code + "1", codes);
}

// Compress input file using Huffman coding
void compressFile(const string& inputFile, const string& outputFile) {
    // Step 1: Calculate character frequencies
    unordered_map<char, int> freqMap;
    ifstream inFile(inputFile);
    char ch;
    while (inFile.get(ch)) {
        freqMap[ch]++;
    }
    inFile.close();

    // Step 2: Build Huffman tree and generate codes
    HuffmanNode* root = buildHuffmanTree(freqMap);
    unordered_map<char, string> codes;
    generateHuffmanCodes(root, "", codes);

    // Step 3: Write compressed data to output file
    ifstream inFile2(inputFile);
    ofstream outFile(outputFile, ios::binary);
    string encodedBits;
    while (inFile2.get(ch)) {
        encodedBits += codes[ch];
    }
    int numPaddingBits = (8 - encodedBits.length() % 8) % 8; // Calculate padding bits
    outFile << numPaddingBits << " "; // Store number of padding bits

    // Write encoded data as bytes to output file
    for (size_t i = 0; i < encodedBits.length(); i += 8) {
        string byte = encodedBits.substr(i, 8);
        outFile << bitset<8>(byte).to_ulong(); // Write as byte
    }

    inFile2.close();
    outFile.close();
}

// Decompress input file using Huffman coding
void decompressFile(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error: Unable to open input or output file." << endl;
        return;
    }

    char ch;
    inFile >> numPaddingBits; // Read number of padding bits

    // Build Huffman tree from a sample frequency map (you may need to pass the actual frequency map)
    unordered_map<char, int> freqMap; // Placeholder for actual frequency map
    HuffmanNode* root = buildHuffmanTree(freqMap);
    HuffmanNode* current = root;

    // Decode the encoded data bit by bit
    while (inFile.get(ch)) {
        bitset<8> bits(ch);
        for (int i = 7; i >= numPaddingBits; --i) {
            if (bits[i]) {
                current = current->right;
            } else {
                current = current->left;
            }
            // Check if leaf node is reached (decoded character)
            if (current->left == nullptr && current->right == nullptr) {
                outFile << current->data; // Output decoded character
                current = root; // Reset to root for next character
            }
        }
    }

    inFile.close();
    outFile.close();
    
}
