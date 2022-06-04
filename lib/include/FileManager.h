#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>

class FileManager {
public:
    explicit FileManager(std::string file_path);
    ~FileManager();

    std::string readFile();
    void appendLine(const std::string& line);
    void writeFile(std::vector<std::string> lines);

    void create();
    void openFile();
    void closeFile();

    void lockFile(flock &lock);
    void unlockFile(flock &lock);
    
private:
    std::string file_path;
    int file = -1;
    
    void writeLine(const std::string &line) const;
};
#endif /* FILE_MANAGER_H */
