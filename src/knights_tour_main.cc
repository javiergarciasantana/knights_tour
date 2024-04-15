// AUTHOR: Javier Garcia Santana
// DATE: 14/2/2023
// EMAIL: javier.santana@tprs.stud.vu.lt
// VERSION: 2.0
// SUBJECT: Artificial Intelligence
// EXCERCISE Nº: 2
// COMMENTS:
//
// COMPILATION: make

#include <iostream>
#include <string>

#include "chess_table.h"

int main(int argc, char* argv[]) {
//(x,y,n,s)
  if (argc == 1) {
    chessTable table;
    return 0;
  }
  chessTable table(std::stoi(argv[1]) - 1, std::stoi(argv[2]) - 1, std::stoi(argv[3]), std::stoi(argv[4]));
  return 0;
}