#include <iostream>
#include <cstring>
#include <string>
#include "../include/linda.h"
#include "../include/parser.h"

int main(int argc, char *argv[]) {
    Linda linda = Linda();
    switch(argc) {
        case 3:
            if (strcmp(argv[1], "-o") == 0) {
                std::cout << argv[1] << std::endl << argv[2];
//                linda.output(Parser().parse(argv[2]));
            } else {
                std::cout << "Wrong syntax" << std::endl;
            }
            break;
        case 5:
            break;
        default:
            std::cout << "Wrong syntax" << std::endl;
            break;
    }
}