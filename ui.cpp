//
//  ui.cpp
//  matrix-multiplication
//
//  Created by Arteen Abrishami on 12/26/22.
//

#include "ui.h"
#include "matrix.h"
#include <iostream>
#include <sstream>
#include <string>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::istringstream;
using std::string;


// ******
// MASTER
// ******

int UI::countDigits(int num){
    int digits = 0;
    if (num <= 0) digits = 1;    // not applicable but makes it portable
    while(num){
        num /= 10;
        digits++;
    }
    return digits;
}

int UI::countSpaces(const string& s){
    int n = (int) s.size();
    int i = 0, c = 0;
    while (i != n){
        if (s[i++] == ' ')
            c++;
    }
    return c;
}

UI::~UI(){
    // size 26 without digits, want to get correct # of * around it
    string s;
    if (m_count == 1){
        cout << endl << "**************************" << endl;
        cout<< "You performed " << m_count << " operation!" << endl;
        cout << "**************************" << endl << endl;
    }
    else{
        int n = countDigits(m_count);
        for (int i = 0 ; i < 26 + n ; i++) s += "*";
        
        cout << endl << s << endl;
        cout<< "You performed " << m_count << " operations!" << endl;
        cout << s << endl << endl;
    }
}

void UI::master(){
    
    matrixOperationPrompt();
    chooseOperation();
    allocateDependencies();
    performOperation();
    sendOutput();
    deallocateDependencies();
    reinitializeConstructs();
}

// ********************
// READ AND PARSE INPUT
// ********************

bool UI::isValidInput(const std::string &s)
{
    if (s.empty()) return false;
    switch(m_input){
        case 0:     // continue or terminate
            return s.find_first_not_of("01") == std::string::npos;
        case 1:     // pick option or row dims
            return s.find_first_not_of("0123456789") == std::string::npos;
        case 2:     // pick scalar
            return s.find_first_not_of("0123456789-") == std::string::npos;
        case 3:     // matrix input
        default:
            break;
    }
    
    m_spaces = countSpaces(s);  // must be one less than # of cols
    return s.find_first_not_of("0123456789- ") == std::string::npos;
}

void UI::readInput(){
prompt:
    string s;
    getline(cin, s);
    if (!isValidInput(s)){
        cout << "Invalid input. Try again: ";
        goto prompt;
    }
    m_buffer = istringstream(s);
}

// ****
// MAIN
// ****

void UI::matrixOperationPrompt(){
    
    if(!m_count++){
        cout << endl << "*****************" << endl;
        cout << "MATRIX OPERATIONS" << endl;
        cout << "*****************" << endl << endl;
    }
    else{
        cout << endl << "**************" << endl;
        cout << "NEXT OPERATION" << endl;
        cout << "**************" << endl << endl;
    }
    
    cout << "What operation would you like to perform?" << endl << endl;;
    cout << "(0) kA = C" << endl;
    cout << "(1) A + B = C" << endl;
    cout << "(2) AB = C" << endl;
    // cout << "(3) det(A) = k" << endl;
    
    cout << endl << "Please input the digit corresponding to your option: ";
    m_input = 1;
    readInput();
    m_buffer >> m_operation;
}

void UI::chooseOperation(){
    switch(m_operation){
        case 0:
            promptScalarMultiply();
            break;
        case 1:
            promptMatrixAddition();
            break;
        case 2:
            promptMatrixMultiply();
            break;
        // case 3:
        //     promptDeterminant();
        //     break;
        default:
            cout << "Invalid operation. Program terminating." << endl;
            exit(-1);
    }
}


void UI::performOperation(){
    switch (m_operation) {
        case 0:
            m_Matrix.performScalarMultiply(m_k, m_matrixA, m_matrixC, m_rowsC, m_colsC);
            break;
        case 1:
            m_Matrix.performMatrixAddition(m_matrixA, m_matrixB, m_matrixC, m_rowsC, m_colsC);
            break;
        case 2:
            m_Matrix.performMatrixMultiply(m_matrixA, m_matrixB, m_matrixC, m_rowsA, m_colsA, m_colsB);
            break;
        // case 3:
        //     m_k = m_Matrix.performDeterminant(m_matrixA, m_rowsA, m_colsA);
        //     break;
        default:
            exit(-1);
    }
}

void UI::sendOutput(){
    switch(m_operation){
        case 0:
        case 1:
        case 2:
            outputMatrixC();
            break;
        // case 3:
        //     // determinant
        //     break;
        default:
            exit(-1);
    }
}

void UI::allocateDependencies(){
    switch(m_operation){
        case 0:
        case 1:
        case 2:
            setMatrixC();
            m_matrixC = m_Matrix.createMatrix(m_rowsC, m_colsC);
            break;
        // case 3:
        //     break;
        default:
            cout << "Failed to allocate dependencies." << endl;
            exit(-1);
    }
}

void UI::deallocateDependencies(){
    switch(m_operation){
        case 0:
            m_Matrix.freeMatrix(m_matrixC, m_rowsC, m_colsC);
            m_Matrix.freeMatrix(m_matrixA, m_rowsA, m_colsA);
            break;
        case 1:
            m_Matrix.freeMatrix(m_matrixC, m_rowsC, m_colsC);
            m_Matrix.freeMatrix(m_matrixA, m_rowsA, m_colsA);
            m_Matrix.freeMatrix(m_matrixB, m_rowsB, m_colsB);
            break;
        case 2:
            m_Matrix.freeMatrix(m_matrixC, m_rowsC, m_colsC);
            m_Matrix.freeMatrix(m_matrixA, m_rowsA, m_colsA);
            m_Matrix.freeMatrix(m_matrixB, m_rowsB, m_colsB);
            break;
        // case 3:
        //     m_Matrix.freeMatrix(m_matrixA, m_rowsA, m_colsA);
        //     break;
        default:
            cout << "Failed to deallocate dependencies." << endl;
            exit(-1);
    }
}

void UI::reinitializeConstructs(){
    
    m_rowsA = ~(1 << 31);
    m_colsA = ~(1 << 31);
    
    m_rowsB = ~(1 << 31);
    m_colsB = ~(1 << 31);
    
    m_rowsC = ~(1 << 31);
    m_colsC = ~(1 << 31);
    
    m_operation = -1;
    m_input = 0;
    m_spaces = 0;
    
    m_k = std::numeric_limits<Entries>::quiet_NaN();
    m_matrixA = nullptr;
    m_matrixB = nullptr;
    m_matrixC = nullptr;
}

// ********************
// 1-PROMPTS (MANAGERS)
// ********************

void UI::promptScalarMultiply(){
    
    cout << endl << "*********************" << endl;
    cout << "SCALAR MULTIPLICATION" << endl;
    cout << "*********************" << endl << endl;
    
    promptScalar();
    promptMatrixA();
    
}

void UI::promptMatrixAddition(){
    cout << endl << "***************" << endl;
    cout << "MATRIX ADDITION" << endl;
    cout << "***************" << endl << endl;
    
    promptMatrixA();
    promptMatrixB();
}

void UI::promptMatrixMultiply(){
    cout << endl << "*********************" << endl;
    cout << "MATRIX MULTIPLICATION" << endl;
    cout << "*********************" << endl << endl;
    
    promptMatrixA();
    promptMatrixB();
}

// void UI::promptDeterminant(){
//     cout << endl << "***********" << endl;
//     cout << "DETERMINANT" << endl;
//     cout << "***********" << endl << endl;
    
//     promptMatrixA();
// }

// **************************
// 2-PROMPTS (INPUT HANDLERS)
// **************************

void UI::promptScalar(){
    m_input = 2;
    do{
        cout << "Please enter the value for the scalar 'k': ";
        readInput();
        m_buffer >> m_k;
    }while (!(m_k == m_k));
}

void UI::promptMatrixA(){
    cout << endl << "********" << endl;
    cout << "MATRIX A" << endl;
    cout << "********" << endl << endl;
    
    m_input = 1;
    do{
        cout << "Please enter the number of rows in matrix A: ";
        readInput();
        m_buffer >> m_rowsA;
    }while (m_rowsA == ~(1 << 31));
    do{
        cout << "Please enter the number of cols in matrix A: ";
        readInput();
        m_buffer >> m_colsA;
    }while (m_colsA == ~(1 << 31));
    cout << endl;
    
    verifyMatrixA();
    
    cout << "Please enter the entries in each row, separated by spaces, when prompted." << endl;
    
    m_matrixA = m_Matrix.createMatrix(m_rowsA, m_colsA);
    
    inputMatrix(m_matrixA, m_rowsA, m_colsA);
//    outputMatrix(m_matrixA, m_rowsA, m_colsA);
}

void UI::promptMatrixB(){
    cout << endl << "********" << endl;
    cout << "MATRIX B" << endl;
    cout << "********" << endl << endl;
    m_input = 1;
    do{
        cout << "Please enter the number of rows in matrix B: ";
        readInput();
        m_buffer >> m_rowsB;
    }while (m_rowsB == ~(1 << 31));
    do{
        cout << "Please enter the number of cols in matrix B: ";
        readInput();
        m_buffer >> m_colsB;
    }while (m_colsB == ~(1 << 31));
    cout << endl;
    
    verifyMatrixB();
    
    cout << "Please enter the entries in each row, separated by spaces, when prompted." << endl;
    
    m_matrixB = m_Matrix.createMatrix(m_rowsB, m_colsB);
    
    inputMatrix(m_matrixB, m_rowsB, m_colsB);
//    outputMatrix(m_matrixB, m_rowsB, m_colsB);
}



// ***********************
// 3-PROMPT (MATRIX INPUT)
// ***********************

void UI::inputMatrix(Entries* matrix, int rows, int cols){
    if (cols == 1) m_input = 2;
    else m_input = 3;
    
    cout << endl;
    for (int i = 0 ; i < rows; i++){
    retry:
        cout << "Row " << i+1 << ": ";
        readInput();
        if (m_spaces != cols - 1) { cout << "Invalid input. Try again." << endl; goto retry;}
        for (int j = 0 ; j < cols ; j++){
            m_buffer >> matrix[i*cols + j];
        }
    }
    cout << endl;
}


// *********
// VERIFIERS
// *********

void UI::verifyMatrixMultiplication(){
    if (m_colsB == m_rowsA){
        m_rowsC = m_rowsB;
        m_colsC = m_colsA;
    }
}

// void UI::verifyDeterminant(){
// }

void UI::verifyMatrixA(){
    if (m_rowsA < 1 || m_colsA < 1){
        cout << "Invalid dimensions. Program terminating." << endl;
        exit(-1);
    }
}
void UI::verifyMatrixB(){
    if (m_rowsB < 1 || m_colsB < 1){
        cout << "Invalid dimensions. Program terminating." << endl;
        exit(-1);
    }
    else if ((m_operation == 1) && (m_rowsB != m_rowsA || m_colsA != m_colsB))
    {
        cout << "Matrix B must be the same dimensions as Matrix A for addition. Program terminating." << endl;
        exit(-1);
    }
    else if ((m_operation == 2) && (m_colsA != m_rowsB)){
        cout << "Rows in B must be the same as columns in A for multiplication. Program terminating." << endl;
        exit(-1);
    }
}

// ******
// OUTPUT
// ******

void UI::setMatrixC(){
    switch(m_operation){
        case 0:
            m_colsC = m_colsA;
            m_rowsC = m_rowsA;
            break;
        case 1:
            m_colsC = m_colsB;
            m_rowsC = m_rowsB;
            break;
        case 2:
            m_rowsC = m_rowsA;
            m_colsC = m_colsB;
            break;
        // case 3:
        //     break;
        default:
            cout << "Program terminating when attempting to set Matrix C dimensions." << endl;
            exit(-1);
    }
}


void UI::outputMatrix(Entries* matrix, int rows, int cols){
    
    for (int i = 0 ; i < rows ; i++){
        cout << "Row " << i+1 << ": ";
        for (int j = 0 ; j < cols ; j++)
            cout << matrix[i*cols +j] << " ";
        cout << endl;
    }
    cout << endl;
}

void UI::outputMatrixC(){
    cout << "********" << endl;
    cout << "MATRIX C" << endl;
    cout << "********" << endl << endl;
    
    outputMatrix(m_matrixC, m_rowsC, m_colsC);
}














// *************
// CACHE OPTIONS
// *************

//void UI::cache(){
//    int cache = 0;
//    cout << "*************" << endl;
//    cout << "CACHE OPTIONS" << endl;
//    cout << "*************" << endl << endl;
//
//    cout << "By default, system is optimized for a Intel(R) Core(TM) i9-9880H CPU @ 2.30GHz processor." << endl;
//    cout << "Would you like to provide your own cache information?" << endl;
//    cout << "Select (0) to skip this step or (1) to provide your own cache information: ";
//    cin >> cache;
//
//    switch(cache){
//        default:
//            cout << "Invalid option." << endl;
//        case 0:
//            cout << "Keeping default optimizations." << endl << endl;
//            break;
//        case 1:
//            cacheInfo();
//    }
//}

//void UI::cacheInfo(){
//    int differ = 0;
//    cout << "The default cache assumptions are as follows: " << endl;
//    cout << "L1 data cache size: 32KB" << endl;
//    cout << "L2 cache size: 256KB" << endl;
//    cout << endl;
//    cout << "Does your system differ from these specs?" << endl;
//    cout << "Select (1) Yes or (0) No: ";
//    cin >> differ;
//
//    switch(differ){
//        default:
//            cout << "Invalid option." << endl;
//        case 0:
//            cout << "Keeping default optimizations." << endl << endl;
//            break;
//        case 1:
//            cout << "Please enter your specs in 'KB' when prompted." << endl;
//            cout << "L1 data cache size: ";
//            cin >> L1;
//            L1 *= 1000;
//            cout << "L2 cache size: ";
//            cin >> L2;
//            L2 *= 1000;
//            cout << "System will optimize for your workload." << endl << endl;
//    }
//}

