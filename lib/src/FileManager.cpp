#include "../include/FileManager.h"
#include "../include/Utilities.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <utility>

FileManager::FileManager(std::string file_path) {
    this -> file_path = std::move(file_path);
    create();
}
FileManager::~FileManager() {
    closeFile();
}

void FileManager::create() {
    openFile();
    closeFile();
}

void FileManager::lockFile(flock &lock){
    if (file == -1) openFile();
    if ((fcntl(file,F_SETLKW,&lock))==-1){
        perror("Error while locking file");
        exit(1);
    }
}

void FileManager::unlockFile(flock &lock){
    if (file == -1) openFile();
    lock.l_type = F_UNLCK;
    if ((fcntl(file,F_SETLKW,&lock))==-1){
        perror("Error while unlocking file");
        exit(1);
    }
}

std::string FileManager::readFile() {
    if (file == -1) openFile();

    char buf[4096] = "";
    std::string result;
    lseek(file, 0, SEEK_SET);
    while (read(file, buf, sizeof buf) > 0) {
        result.append(buf);
    }
    closeFile();
    return result;
}
void FileManager::writeFile(std::vector<std::string> lines) {
    if (file == -1) openFile();

    lseek(file, 0, SEEK_SET);
    for (int i=0; i<lines.size(); i++) {
        std::string line = lines.at(i);
        if (i < lines.size() - 1) {
            line += "\n";
        }
        writeLine(line);
    }
    ftruncate(file, lseek(file, 0, SEEK_CUR));
    closeFile();
}
void FileManager::appendLine(const std::string& line) {
    if (file == -1) openFile();


    long set = lseek(file, 0, SEEK_SET);
    long end = lseek(file, 0, SEEK_END);
    if (set != end) {
        writeLine("\n" + line);
    } else {
        writeLine(line);
    }


    closeFile();
}

void FileManager::writeLine(const std::string& line) const {
    const char *buf = line.c_str();
    write(file, buf, strlen(buf));
}
void FileManager::openFile() {
    int fp = open(file_path.c_str(), O_RDWR | O_CREAT, 0777);
    if (!fp) {
        perror("Error opening file");
        exit(1);
    }
    file = fp;
}
void FileManager::closeFile() {
    if (file != -1) {
        close(file);
        file = -1;
    }
} 
