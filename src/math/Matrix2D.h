
#include <string>
#include <vector>

class Matrix2D
{
private:
    std::vector<int> dims;
    int dataSize;
public:
    std::vector<float> data;
    Matrix2D(){}
    Matrix2D(std::vector<float> data, std::vector<int> dims);
    ~Matrix2D(){}
    static Matrix2D identityMat(int size);
    std::string toString();


};