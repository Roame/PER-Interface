
#include <string>
#include <vector>

class Matrix2D
{
private:
    std::vector<float> data;
    std::vector<int> dims;
public:
    Matrix2D(){}
    Matrix2D(std::vector<float> data, std::vector<int> dims);
    ~Matrix2D(){}
    Matrix2D operator*(Matrix2D const &matB);
    Matrix2D scalarMult(float scalar);
    Matrix2D transpose();

    double getDeterminant();
    Matrix2D getInverse();

    static Matrix2D identityMat(int size);
    std::string toString();


};