#include "Matrix2D.h"

#include <sstream>
#include <iostream>
#include <iomanip>

Matrix2D::Matrix2D(std::vector<float> data, std::vector<int> dims):
data(data), dims(dims){}

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

    sstm << "Data:\n";
    for(int j = 0; j < dims[0]; j++){
        for(int i = 0; i < dims[1]; i++){
            int index = j+i*dims[0];
            if((dims[1] > 11 && i == 5) || (dims[0] > 11 && j == 5)) {
                sstm << std::setw(3) << "..." << " ";
            } else {
                sstm <<std::setw(3) << data[index] << " ";
            }
            if(i == dims[1]-1) sstm << "\n";
            if(dims[1] > 11 && i == 5) i = dims[1]-6;
        }
        if(dims[0] > 11 && j == 5) j = dims[0]-6;
    }
    return sstm.str();
}
