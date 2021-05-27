#include "Matrix2D.h"

#include <sstream>
#include <iostream>
#include <iomanip>

Matrix2D::Matrix2D(std::vector<float> data, std::vector<int> dims):
data(data), dims(dims){}

// Dot product
Matrix2D Matrix2D::operator*(Matrix2D const &matB){
    std::vector<int> dims1 = this->dims;
    std::vector<float> data1 = this->data;
    std::vector<int> dims2 = matB.dims;
    std::vector<float> data2  = matB.data;
    std::vector<float> group1(dims1[1]), group2(dims2[0]);
    if(dims1[1] != dims2[0]) throw "Inner dimensions do not match";

    std::vector<int> outDims{dims1[0], dims2[1]};
    std::vector<float> outData(outDims[0]*outDims[1]);
    int index;

    for(int j = 0; j < dims1[0]; j++){
        // Gathering values from the first matrix
        for(int i = 0; i < dims1[1]; i++){
            index = j+i*dims1[0];
            group1[i] = data1[index];
        }
        for(int i = 0; i < dims2[1]; i++){
            // Gathering values from second matrix
            for(int k = 0; k < dims2[0]; k++){
                index = k+i*dims2[0];
                group2[k] = data2[index];
            }

            float sum = 0;
            for(int c = 0; c < group1.size(); c++){
                sum += group1[c]*group2[c];
            }
            index = j+i*dims1[0];
            outData[index] = sum;
        }
    }
    return Matrix2D(outData, outDims);
}

Matrix2D Matrix2D::scalarMult(float scalar){
    std::vector<float> output = this->data;
    for(int i = 0; i < output.size(); i++){
        output[i] *= scalar;
    }
    return Matrix2D(output, this->dims);
}

Matrix2D Matrix2D::transpose(){
    std::vector<int> outDims{dims[1], dims[0]};
    std::vector<float> outData(data.size());
    for(int i = 0; i < dims[1]; i++){
        for(int j = 0; j < dims[0]; j++){
            int oIndex = j+i*dims[0];
            int tIndex = i+j*outDims[0];
            outData[tIndex] = data[oIndex];
        }
    }
    return Matrix2D(outData, outDims);
}

// Determinant functions
static Matrix2D shrinkMat(Matrix2D mat, int row, int col){
    std::vector<int> dims = mat.getDims();
    std::vector<float> data = mat.getData();
    std::vector<int> outDims{dims[0]-1, dims[1]-1};
    std::vector<float> outData(outDims[0]*outDims[1]);

    int count = 0;
    for(int i = 0; i < dims[1]; i++){
        if(i == col) continue;
        for(int j = 0; j < dims[0]; j++){
            if(j == row) continue;
            int index = j+i*dims[0];
            outData[count] = data[index];
            count++;
        }
    }
    return Matrix2D(outData, outDims);
}

static float determinantRecurse(Matrix2D mat){
    std::vector<int> dims = mat.getDims();
    std::vector<float> data = mat.getData();
    float sum = 0;
    if(dims[0] != 2){
        for(int i = 0; i < dims[1]; i++){
            int sign = i % 2 == 0 ? 1 : -1;
            sum += sign * data[i*dims[0]]*determinantRecurse(shrinkMat(mat, 0, i));
        }
    } else {
        sum = data[0]*data[3]-data[1]*data[2];
    }
    return sum;
}

float Matrix2D::getDeterminant(){
    if(dims[0]!=dims[1]) throw "Can't take determinant of non-square matrices";
    return determinantRecurse(*this);
}

// Inverse related functions
Matrix2D getCofactor(Matrix2D mat){
    std::vector<int> dims = mat.getDims();
    std::vector<float> data = mat.getData();
    std::vector<int> outDims{dims[0], dims[1]};
    std::vector<float> outData(outDims[0]*outDims[1]);
    
    for(int i = 0; i < dims[1]; i++){
        int count;
        count = i%2 == 0 ? 0 : 1;
        for(int j = 0; j < dims[0]; j++){
            float minor = shrinkMat(mat, j, i).getDeterminant();
            int sign = count%2 == 0 ? 1 : -1;
            int index = j+i*dims[0];
            outData[index] = sign*minor;
            count++;
        }
    }
    return Matrix2D(outData, outDims);
}

Matrix2D Matrix2D::getInverse(){
    float det = this->getDeterminant();
    if(det == 0) throw "Can't get inverse of matrix with determinant of 0";
    Matrix2D cofactor = getCofactor(*this);
    Matrix2D adjoint = cofactor.transpose();
    return adjoint.scalarMult(1.0/det);
}

Matrix2D Matrix2D::identityMat(int size){
    std::vector<float> data(size*size);
    for(int i = 0; i < size; i++){
        int index = i*(1+size);
        data[index] = 1.0;
    }
    return Matrix2D(data, std::vector<int>{size, size});
}


std::string Matrix2D::toString(){
    std::stringstream sstm;
    sstm << "Info \nDimensions: ";
    sstm << dims[0] << " x " << dims[1] << "\n";

    sstm << "Data:\n" << std::setprecision(3);
    for(int j = 0; j < dims[0]; j++){
        for(int i = 0; i < dims[1]; i++){
            int index = j+i*dims[0];
            if((dims[1] > 11 && i == 5) || (dims[0] > 11 && j == 5)) {
                sstm << std::setw(4) << "..." << " ";
            } else {
                sstm <<std::setw(4) << data[index] << " ";
            }
            if(i == dims[1]-1) sstm << "\n";
            if(dims[1] > 11 && i == 5) i = dims[1]-6;
        }
        if(dims[0] > 11 && j == 5) j = dims[0]-6;
    }
    return sstm.str();
}
