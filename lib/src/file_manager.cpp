#include "../include/file_manager.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include <iterator>
#include <cstring>

FileManager::FileManager(const std::string& file_path) {
    this -> file_path = file_path.c_str();
    this -> file = openFile();
}

FileManager::~FileManager() {
    closeFile();
}

std::string FileManager::readFile() const {
    char buf[4096] = "";
    std::string result;
    lseek(file, 0, SEEK_SET);
    while (read(file, buf, sizeof buf) > 0) {
        result.append(buf);
    }
    return result;
}

void FileManager::writeLine(const std::string& line) const {
    std::string strBuff = "\n" + line;
    const char *buf = strBuff.c_str();
    lseek(file, 0, SEEK_END);
    write(file, buf, strlen(buf));
}

int FileManager::openFile() {
    int fp = open(file_path, O_RDWR);
    if (!fp) {
        perror("Error opening file");
        exit(1);
    }
    return fp;
}

void FileManager::closeFile() const {
    close(file);
}

std::vector<std::string> FileManager::readSplitFile() const {
    std::vector<std::string> result;
    std::string allFile = readFile();
    std::string temp;

    for (char character : allFile) {
        if (character != '\n' && character != '\r') {
            temp += character;
        } else {
            if (!temp.empty()) {
                result.push_back(temp);
                temp = "";
            }
        }
    }
    if (!temp.empty()) {
        result.push_back(temp);
    }
    return result;
}
