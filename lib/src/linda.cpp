#include <string>
#include "../include/linda.h"
#include "../include/file_manager.h"

Linda::Linda(const std::string& file_path) {
    FileManager fileManager(file_path);
}

Linda::Linda() {
    FileManager fileManager("C:\\Users\\kubar\\Documents\\Sem6\\UXP1A\\resources");
    for (int i=0;i<2;i++) {
        std::string line = fileManager.readLine();
        std::cout << line << std::endl;
    }
};