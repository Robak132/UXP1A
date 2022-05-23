#include "../include/file_manager.h"
#include "../include/utilities.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

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
void FileManager::writeFile(std::vector<std::string> lines) {
    lseek(file, 0, SEEK_SET);
    for (int i=0; i<lines.size(); i++) {
        std::string line = lines.at(i);
        if (i < lines.size() - 1) {
            line += "\n";
        }
        writeLine(line);
    }
    ftruncate(file, lseek(file, 0, SEEK_CUR));
}
void FileManager::appendLine(const std::string& line) {
    lseek(file, 0, SEEK_END);
    writeLine("\n" + line);
}

void FileManager::writeLine(const std::string& line) const {
    const char *buf = line.c_str();
    write(file, buf, strlen(buf));
}
int FileManager::openFile() {
    int fp = open(file_path, O_RDWR | O_CREAT);
    if (!fp) {
        perror("Error opening file");
        exit(1);
    }
    return fp;
}
void FileManager::closeFile() const {
    close(file);
}