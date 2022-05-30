#include <iostream>
#include <cstring>
#include <string>
#include "../include/Linda.h"
#include "../include/Parser.h"

int main(int argc, char *argv[]) {
    Linda linda = Linda("../resources/tuples.csv", "../resources/sleeping.csv");

    switch(argc) {
        case 3:
            if (strcmp(argv[1], "-o") == 0) {
                linda.output(argv[2]);
            } else {
                std::cout << "Wrong syntax" << std::endl;
                exit(0);
            }
            break;
        case 5:
            if (strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-t") == 0) {
                Tuple* result = linda.input(argv[2], std::stoi(argv[4]));
                std::cout<<result->toCSV()<<std::endl;
            } else if (strcmp(argv[1], "-r") == 0 && strcmp(argv[3], "-t") == 0) {
                Tuple* result = linda.read(argv[2], std::stoi(argv[4]));
                std::cout<<result->toCSV()<<std::endl;
            } else {
                std::cout << "Wrong syntax" << std::endl;
                exit(0);
            }
            break;
        default:
            std::cout << "Wrong syntax" << std::endl;
            exit(0);
    }
}