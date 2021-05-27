
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

    std::vector<int> getDims(){return dims;}
    std::vector<float> getData(){return data;}

    Matrix2D operator*(Matrix2D const &matB);
    Matrix2D scalarMult(float scalar);
    Matrix2D transpose();

    float getDeterminant();
    Matrix2D getInverse();

    static Matrix2D identityMat(int size);
    std::string toString();


};