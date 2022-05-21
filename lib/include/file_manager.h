#ifndef MAIN_FILE_MANAGER_H
#define MAIN_FILE_MANAGER_H

#include <fstream>
#include <iostream>
#include <string>

class FileManager {
public:
    FileManager(const std::string& file_path);
    ~FileManager();
    std::string readLine();
    void writeLine(const std::string& line);
private:
    const char *file_path;
    FILE *file;

    FILE * openFile();
    void closeFile();
};


#endif //MAIN_FILE_MANAGER_H
