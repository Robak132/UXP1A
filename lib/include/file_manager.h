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
    void appendLine(const std::string& line);
    void writeFile(std::vector<std::string> lines);
private:
    const char* file_path;
    int file;

    int openFile();
    void closeFile() const;

    void writeLine(const std::string &line) const;
};


#endif //MAIN_FILE_MANAGER_H
