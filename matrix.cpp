//
//  matrixops.cpp
//  matrix-multiplication
//
//  Created by Arteen Abrishami on 12/25/22.
//

#include "matrix.h"

//int L1 = 32000;
//int L2 = 256000;    // leave some leeway

// ************************
// ALLOCATOR & DE-ALLOCATOR
// ************************

//Entries** Matrix::createMatrix(int rows, int cols){
//    Entries** matrix = new Entries*[rows];
//    for (int i = 0 ; i < rows ; i++){
//        matrix[i] = new Entries[cols]();
//    }
//    return matrix;
//}   // cols would be allocated contiguously, becomes more like a multi-level array than a 2D -> slower

Entries* Matrix::createMatrix(int rows, int cols){
    Entries* matrix = new Entries[rows * cols]();
    return matrix;
}

//void Matrix::freeMatrix(Entries** matrix, int rows, int cols){
//    for (int i = 0 ; i < rows ; i++)
//        delete [] matrix[i];
//    delete [] matrix;
//    matrix = nullptr;
//}

void Matrix::freeMatrix(Entries* matrix, int rows, int cols){
    delete [] matrix;
    matrix = nullptr;
}

// ****************************************************
// OPERATORS (return nullptr if operation not possible)
// ****************************************************

//void Matrix::performScalarMultiply(Entries** A, int rows, int cols, Entries k, Entries** C){
//
//    for (int i = 0 ; i < rows ; i++){
//        for (int j = 0 ; j < cols ; j++){
//            C[i][j] = A[i][j] * k;
//        }
//    }
//}

void Matrix::performScalarMultiply(Entries k, Entries* A, Entries* C, int rows, int cols){
    
    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < cols ; j++){
            C[i*cols + j] = A[i*cols + j] * k;
        }
    }
}

//void Matrix::performMatrixAddition(Entries** A, Entries** B, Entries** C, int rows, int cols){
//
//    for (int i = 0 ; i < rows ; i++){
//        for (int j = 0 ; j < cols ; j++){
//            C[i][j] = A[i][j] + B[i][j];
//        }
//    }
//}

void Matrix::performMatrixAddition(Entries* A, Entries* B, Entries* C, int rows, int cols){
    
    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < cols ; j++){
            C[i*cols + j] = A[i*cols + j] + B[i*cols +j];
        }
    }
}

void Matrix::performMatrixMultiply(Entries* A, Entries* B, Entries* C , int rowsA_rowsC, int colsA_rowsB, int colsB_colsC){
    
    Entries placeholder = 0;
    // can tile here, useless for matrices < ~ 44 x 44, not a useful use case in this context
    for (int i = 0 ; i < rowsA_rowsC; i++){
        for (int k = 0 ; k < colsA_rowsB; k++){
            placeholder = A[i*colsA_rowsB + k];
            for (int j = 0 ; j < colsB_colsC; j++){
                C[i*colsB_colsC + j] += placeholder * B[k*colsB_colsC + j];
            }
        }
    }
         
         
}
/*
 rowsA = rowsC
 colsA = rowsB
 colsC = colsB
*/



