//
//  main.cpp
//  matrix-multiplication
//
//  Created by Arteen Abrishami on 12/25/22.
//

#include "ui.h"
#include <iostream>
#include <string>
#include <sstream>

// ****
// MAIN
// ****

int main(){

    int cont = 0;
    UI master;

    do{
        master.master();

        std::cout << "Type (0) to exit program or (1) to perform another operation: ";
        std::string s;
        std::getline(std::cin, s);

        std::istringstream buffer(s);
        buffer >> cont;
    }
    while(cont);
}










// **********
// MISC TESTS
// **********


//int main(){
//
//    double test = std::numeric_limits<double>::quiet_NaN();
//    int i = test;
//    std::cout << i;
//    int k = (1<<31);
//    std::cout << k;
//
//}   // careful for this if changing Entries from double

