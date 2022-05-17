#include "../include/file_manager.h"

#include <fstream>
#include <iostream>
#include <utility>

FileManager::FileManager(std::string file_path) {
    this -> file_path = std::move(file_path);
    openFile();
}

FileManager::~FileManager() {
    this -> closeFile();
}

std::string FileManager::readLine() {
    std::string line;
    getline(this -> file, line);
    return line;
}

void FileManager::writeLine(const std::string& line) {

}

void FileManager::openFile() {
    this -> file.open(this -> file_path, std::fstream::in | std::fstream::out | std::fstream::app);
}

void FileManager::closeFile() {
    this -> file.close();
}
