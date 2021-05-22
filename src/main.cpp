#include <iostream>

#include "math/test.h"

int main(int argc, char **argv) {
    std::cout << "Hello World" << std::endl;
    if(argc > 1) std::cout << argv[1] << std::endl;
    test myTest;
}