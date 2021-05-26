#include <iostream>

#include "graphics/GraphicsMain.h"
#include "math/Matrix2D.h"

int main(int argc, char **argv) {
    // GraphicsMain(argc, argv);
    // std::array<float, 4> data{1,1,1,1};
    // std::array<int, 1> dims{1};
    // const size_t test1 = 4, test2= 1;
    // Matrix2D test = Matrix2D::fromArray<test1, test2>(data, dims);

    Matrix2D test = Matrix2D::identityMat(12);
    std::cout << test.toString() << std::endl;

}