#ifndef MAIN_FILE_MANAGER_H
#define MAIN_FILE_MANAGER_H

#include <fstream>
#include <iostream>
#include <string>

class FileManager {
public:
    FileManager(std::string file_path);
    ~FileManager();
    std::string readLine();
    void writeLine(const std::string& line);
private:
    std::string file_path;
    std::fstream file;

    void openFile();
    void closeFile();
};


#endif //MAIN_FILE_MANAGER_H
