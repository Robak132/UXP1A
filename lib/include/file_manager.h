#ifndef MAIN_FILE_MANAGER_H
#define MAIN_FILE_MANAGER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class FileManager {
public:
    explicit FileManager(const std::string& file_path);
    ~FileManager();
    std::string readFile() const;
    std::vector<std::string> readSplitFile() const;
    void writeLine(const std::string& line);
private:
    const char *file_path;
    int file;

    int openFile();
    void closeFile() const;
};


#endif //MAIN_FILE_MANAGER_H
