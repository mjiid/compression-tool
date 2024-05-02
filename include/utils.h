#ifndef UTILS_H
#define UTILS_H

#include <string>

// Function to read content of a file and return as string
std::string readFile(const std::string& filename);

// Function to write content to a file
void writeFile(const std::string& filename, const std::string& content);

#endif // UTILS_H

