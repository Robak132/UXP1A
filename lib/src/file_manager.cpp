#include "../include/file_manager.h"

#include <fstream>
#include <iostream>
#include <utility>

FileManager::FileManager(const std::string& file_path) {
    this -> file_path = file_path.c_str();
    this -> file = openFile();
}

FileManager::~FileManager() {
    closeFile();
}

std::string FileManager::readLine() {
    char *line_buf = nullptr;
    size_t line_buf_size = 0;
    getline(&line_buf, &line_buf_size, file);
    return line_buf;
}

void FileManager::writeLine(const std::string& line) {
}

FILE * FileManager::openFile() {
    FILE *fp = fopen(file_path, "r");
    if (!fp) {
        perror("Error opening file");
        exit(1);
    }
    return fp;
}

void FileManager::closeFile() {
    fclose(file);
}
