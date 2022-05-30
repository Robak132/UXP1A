#include <iostream>
#include <cstring>
#include <string>
#include "../include/Linda.h"
#include "../include/Parser.h"

int main(int argc, char *argv[]) {
    switch(argc) {
        case 4:
            if (strcmp(argv[2], "-o") == 0) {
                // <data> -o <tuple>
                Linda linda = Linda(argv[1]);
                linda.output(argv[3]);
            } else if (strcmp(argv[2], "-i") == 0) {
                // <data> -i <template>
                Linda linda = Linda(argv[1]);
                Tuple* result = linda.input(argv[3], 0);
                std::cout<<result->toCSV()<<std::endl;
            } else if (strcmp(argv[2], "-r") == 0) {
                // <data> -r <template>
                Linda linda = Linda(argv[1]);
                Tuple* result = linda.read(argv[3], 0);
                std::cout<<result->toCSV()<<std::endl;
            } else {
                std::cout << "Wrong syntax" << std::endl;
                exit(0);
            }
            break;
        case 5:
            if (strcmp(argv[3], "-o") == 0) {
                // <data> <processes> -o <tuple>
                Linda linda = Linda(argv[1], argv[2]);
                linda.output(argv[3]);
            } else if (strcmp(argv[3], "-i") == 0) {
                // <data> <processes> -i <tuple>
                Linda linda = Linda(argv[1], argv[2]);
                Tuple* result = linda.input(argv[4], 0);
                std::cout<<result->toCSV()<<std::endl;
            } else if (strcmp(argv[3], "-r") == 0) {
                // <data> <processes> -r <tuple>
                Linda linda = Linda(argv[1], argv[2]);
                Tuple* result = linda.read(argv[4], 0);
                std::cout<<result->toCSV()<<std::endl;
            } else {
                std::cout << "Wrong syntax" << std::endl;
                exit(0);
            }
            break;
        case 6:
            if (strcmp(argv[2], "-i") == 0 && strcmp(argv[4], "-t") == 0) {
                // <data> -i <tuple> -t <timeout>
                Linda linda = Linda(argv[1]);
                Tuple* result = linda.input(argv[3], std::stoi(argv[5]));
                std::cout<<result->toCSV()<<std::endl;
            } else if (strcmp(argv[2], "-r") == 0 && strcmp(argv[4], "-t") == 0) {
                // <data> -r <tuple> -t <timeout>
                Linda linda = Linda(argv[1]);
                Tuple* result = linda.read(argv[3], std::stoi(argv[5]));
                std::cout<<result->toCSV()<<std::endl;
            } else {
                std::cout << "Wrong syntax" << std::endl;
                exit(0);
            }
            break;
        case 7:
            if (strcmp(argv[3], "-i") == 0 && strcmp(argv[5], "-t") == 0) {
                // <data> <processes> -i <tuple> -t <timeout>
                Linda linda = Linda(argv[1], argv[2]);
                Tuple* result = linda.input(argv[4], std::stoi(argv[6]));
                std::cout<<result->toCSV()<<std::endl;
            } else if (strcmp(argv[3], "-r") == 0 && strcmp(argv[5], "-t") == 0) {
                // <data> <processes> -r <tuple> -t <timeout>
                Linda linda = Linda(argv[1], argv[2]);
                Tuple* result = linda.read(argv[4], std::stoi(argv[6]));
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