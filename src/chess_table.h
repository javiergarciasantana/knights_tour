#include <iostream>
#include <fstream>
#include <vector>

#ifndef CHESS_TABLE_H
#define CHESS_TABLE_H

class chessTable {
 public:
  chessTable() : initial_x_(0), initial_y_(0), limit_(5), initial_step_(1), trials_(0) {  

   if (!output_file.is_open() || !output_file_2.is_open()) { 
      exit(EXIT_SUCCESS); 
    }
    printData(std::cout);
    printData(output_file);
    printData(output_file_2);
    table_ = std::vector<std::vector<int>>(limit_, std::vector<int>(limit_, -1));
    table_[initial_y_][initial_x_] = initial_step_;
    output_file_2 << "\nPART 2. Trace";
    if (Tour(initial_x_, initial_y_, initial_step_ + 1) == 0) {
      std::cout << "\n    SOLUTION DOES NOT EXIST" << std::endl << "    Trials=" << trials_ << std::endl;
      output_file << "\n    SOLUTION DOES NOT EXIST" << std::endl << "    Trials=" << trials_ << std::endl;
      output_file_2 << "\n    SOLUTION DOES NOT EXIST" << std::endl << "    Trials=" << trials_ << std::endl;
    } else {
      printTable(std::cout);
      printTable(output_file);
      printTable(output_file_2);
    }
  }

  chessTable(int x, int y, int l, int s) : initial_x_(x), initial_y_(y), limit_(l), initial_step_(s), 
             trials_(0) {

    if (!output_file.is_open() || !output_file_2.is_open()) { 
      exit(EXIT_SUCCESS); 
    }
    printData(std::cout);
    printData(output_file);
    printData(output_file_2);
    table_ = std::vector<std::vector<int>>(limit_, std::vector<int>(limit_, -1));
    table_[initial_y_][initial_x_] = initial_step_;
    output_file_2 << "\nPART 2. Trace";
    if (Tour(initial_x_,initial_y_, initial_step_ + 1) == 0) {
      std::cout << "\n    SOLUTION DOES NOT EXIST" << std::endl << "    Trials=" << trials_ << std::endl;
      output_file << "\n    SOLUTION DOES NOT EXIST" << std::endl << "    Trials=" << trials_ << std::endl;
      output_file_2 << "\n    SOLUTION DOES NOT EXIST" << std::endl << "    Trials=" << trials_ << std::endl;
    } else {
      printTable(std::cout);
      printTable(output_file);
      printTable(output_file_2);
    }
  }


  void printData(std::ostream& out) const {
    out << "PART 1. Data\n" << "    1) Board: " << limit_ << "x" << limit_ 
    << ".\n" << "    2) Initial position: X=" << initial_x_ + 1 << ", Y=" 
    << initial_y_ + 1 << ", L=" << initial_step_ << std::endl;
  }

  void printTrace(std::ostream& out, int u, int v, int step, int move) const {
    out << "\n     " << trials_ << ") ";
    for (int i = 2; i < step; ++i) {
      out << "-";
    }
    out << "R" << move + 1 << ". U=" << u + 1 << ", V=" << v + 1 << ". L=" << step << ".";
  }

  void printTable(std::ostream& out) const {
    int x_axis = table_.size();
    out << "\nPART 3. Results \n" << "  1) Path is found. Trials=" << trials_ << std::endl;
    out << "  2)Path graphically: \nY, V ^" << std::endl;
    for (int i = table_.size() - 1; i >= 0; --i) {
      out << "   " << x_axis << " |"; 
      --x_axis;
      for (int j = 0; j < table_.size(); ++j) {
        if (table_[i][j] / 10 < 1) {
          out << " ";
        }
        out << " " << table_[i][j];
      }
      out << std::endl;
    }
    out << "     ------------------";
    for (int i = 5; i < limit_; ++i) {
      out << "---";
    }
    out << "> X, U" << std::endl;
    out << "        ";
    for (int i = 1; i <= table_.size(); ++i) {
      out << i << "  ";
    }
    out << std::endl;
  }

  bool Move(const int x_move, const int y_move) {
    //std::cout << "X: " << x_ + x_move << " Y: " << y_ + y_move << std::endl;
    if (x_move >= limit_ || y_move >= limit_ || x_move < 0 || y_move < 0) {
      output_file_2 << " Out.";
    }
     else if (table_[y_move][x_move] != -1) {
      output_file_2 << " Thread.";
    }
    return (x_move >= 0 && x_move < limit_ && y_move >= 0 && y_move < limit_
            && table_[y_move][x_move] == -1);
  }

  int Tour(int x, int y, int step) {
    
    if (step == (limit_ * limit_) + 1) {
      return 1;
    }
    int x_next, y_next;

    for (int k = 0; k < 8; ++k) {

      x_next = x + xMove[k];
      y_next = y + yMove[k];
      ++trials_;

      printTrace(output_file_2, x_next, y_next, step, k);
    
      if (Move(x_next, y_next)) {

        output_file_2 << " Free. BOARD[" << x_next + 1 << "," << y_next + 1 << "]:=" << step;
        table_[y_next][x_next] = step;
      
        if (Tour(x_next, y_next, step + 1) == 1) {
          return 1;
        } else {
          table_[y_next][x_next] = -1;
        }
      } 
    }
    output_file_2 << " Backtrack.";
    return 0;
  }
  
 private:
  int limit_;
  int trials_;
  int initial_step_;
  int initial_x_, initial_y_;
  std::vector<std::vector<int> > table_;
  std::ofstream output_file{"out-short.txt"};
  std::ofstream output_file_2{"out-long.txt"};
  int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
  int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
};

#endif