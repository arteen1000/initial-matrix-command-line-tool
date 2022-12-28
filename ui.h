//
//  ui.hpp
//  matrix-multiplication
//
//  Created by Arteen Abrishami on 12/26/22.
//

#ifndef ui_h
#define ui_h

#include "matrix.h"
#include <sstream>
#include <limits>
#include <string>

class UI{
public:
    // ******
    // MASTER
    // ******
    
    void master();
    ~UI();
    
    // ********************
    // READ AND PARSE INPUT
    // ********************
    
    bool isValidInput(const std::string&);
    int countDigits(int num);
    int countSpaces(const std::string&);

protected:
    
    void readInput();
    
    // ****
    // MAIN
    // ****
    
    void matrixOperationPrompt();
    void chooseOperation();
    
    void verifyStatus();
    
    void performOperation();
    void sendOutput();
    
    void allocateDependencies();
    void deallocateDependencies();
    
    void reinitializeConstructs();
    
    // ********************
    // 1-PROMPTS (MANAGERS)
    // ********************
    
    void promptScalarMultiply(); // (1)
    void promptMatrixAddition(); // (2)
    void promptMatrixMultiply(); // (3)
    void promptDeterminant();    // (4)
    
    // **************************
    // 2-PROMPTS (INPUT HANDLERS)
    // **************************
    
    void promptScalar();
    void promptMatrixA();
    void promptMatrixB();
    
    // ***********************
    // 3-PROMPT (MATRIX INPUT)
    // ***********************
    
    void inputMatrix(Entries*, int, int);
    
    // ********************
    // 1-VERIFY (VERIFIERS)
    // ********************
    
    void verifyMatrixMultiplication();
    void verifyDeterminant();
    
    void verifyMatrixB();
    void verifyMatrixA();
    
    // ******
    // OUTPUT
    // ******
    
    void setMatrixC();
    void outputMatrix(Entries*, int, int);
    void outputMatrixC();
    
    // *************
    // CACHE OPTIONS
    // *************
    
//    void cache();
//    void cacheInfo();
private:
    // *****
    // STATE
    // *****
    
    int m_operation = -1;   // op code
    int m_input = 0;    // input code
    int m_count = 0;    // count # ops
    int m_spaces = 0;   // # spaces -> input validation
    
    // ********
    // OPERANDS
    // ********
    Entries m_k = std::numeric_limits<double>::quiet_NaN();
    Entries *m_matrixA = nullptr;
    Entries *m_matrixB = nullptr;
    Entries *m_matrixC = nullptr;
    
    // ******************
    // OPERAND ATTRIBUTES
    // ******************
    int m_rowsA = ~(1 << 31);
    int m_colsA = ~(1 << 31);
    
    int m_rowsB = ~(1 << 31);
    int m_colsB = ~(1 << 31);
    
    int m_rowsC = ~(1 << 31);
    int m_colsC = ~(1 << 31);
    
    // ***
    // AUX
    // ***
    
    Matrix m_Matrix;
    std::istringstream m_buffer;
};

#endif /* ui_hpp */

