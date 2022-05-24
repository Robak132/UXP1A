#include <string>
#include "../include/linda.h"
#include "../include/file_manager.h"
#include "../include/parser.h"

Linda::Linda(const std::string& file_path) {
    Parser parser;
    FileManager fileManager(file_path);
}

Linda::Linda() : Linda("../resources/tuples.csv") {}