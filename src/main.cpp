#include <iostream>

#include "graphics/GraphicsMain.h"
#include "math/Matrix2D.h"

int main(int argc, char **argv) {
    // GraphicsMain(argc, argv);

    // Matrix2D test1 = Matrix2D(std::vector<float>{1, 1, 1}, std::vector<int>{1,3});
    // Matrix2D test2 = Matrix2D(std::vector<float>{2,3,2,  1,1,1, 1,2,3}, std::vector<int>{3,3});

    // Matrix2D output = (test1*test2).scalarMult(3.5);

    // std::cout << output.toString() << std::endl;
    // std::cout << output.transpose().toString() << std::endl;

    Matrix2D test(std::vector<float>{2,2,3,3,2,1,1,2,50}, std::vector<int>{3,3});
    // Matrix2D test = Matrix2D::identityMat(5);
    std::cout << test.getDeterminant() << std::endl;
    std::cout << "Inital mat:\n" << test.toString() << std::endl;
    Matrix2D inv  = test.getInverse();
    std::cout << "Inverse:\n" << inv.toString() << std::endl;
    std::cout << "Hopefully identity:\n" << (test*inv).toString() << std::endl;

}