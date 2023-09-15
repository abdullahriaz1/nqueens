#include <iostream>
#include <stack>
#include <string>
#include <cstring>
#include <fstream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
using namespace std;

void printBoard(vector<vector<int>> board, int n) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

bool safe(vector<vector<int>> board, int n, int row, int col) {
  if (board[row][col] == 1) {
    return false;
  }
  for (int i = 0; i < n; i ++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 1) {
        if ((i == row) || (j == col) || (abs(row - i) == abs(col - j))) {
          return false;
        }
      }
    }
  }
  return true;
}

class Recur {
  public:
    vector<vector<int>> board;
    int row;
};

vector<vector<int>> solve_s(vector<vector<int>> board, int n) {
  Recur first_push;
  first_push.board = board;
  first_push.row = 0;
  stack<class Recur>s;
  s.push(first_push);
  while (!s.empty()) {
    Recur top = s.top();
    s.pop();
    //all rows have a qeen in them, so return the solved board
    if (top.row == n) {
      return top.board;
    }
    bool queen_in_row = false;
    for (int i = 0; i < top.board[top.row].size(); i++) {
      if (top.board[top.row][i] == 1) {
        //this row has a queen, move to next row
        Recur new_push;
        new_push.board = top.board;
        new_push.row = top.row + 1;
        s.push(new_push);
        queen_in_row = true;
      }
    }
    //if there is no queen in the row, loop through the columns and try placing a queen, and pushing to the next row.
    if (!queen_in_row) {
      for (int i = 0; i < board[top.row].size(); i++) {
        if (safe(top.board, n, top.row, i)) {
          Recur next_push;
          next_push.board = top.board;
          next_push.row = top.row + 1;
          next_push.board[top.row][i] = 1;
          s.push(next_push);
        }
      }
    }
  }
  // if no solution is found, return a vector<vector<int>> with -1 in it.
  vector<vector<int>> l (1,vector<int>(1,-1));
  return l;
}

vector<vector<int>> nqueens(vector<vector<int>> board, int n) {
  return solve_s(board, n);
}

int main (int argc, char ** argv) {
  if (argc < 3) {
    throw std::invalid_argument("incorrect file format");
  }
  ifstream inFile;
  ofstream outFile;
  inFile.open(argv[1]);
  outFile.open(argv[2]);
  string line;
  while (getline(inFile, line)) {
    if (line.length() == 0) {
      continue;
    }
    stringstream ss(line);
    string tok;
    char delimiter = ' ';
    int n;
    int col;
    int row;
    int i = 0;

    getline(ss, tok, delimiter);
    n = stoi(tok);
    vector<vector<int>> board (n, vector<int>(n,0));
    i += 1;
    bool given_fair = true;
    while (getline(ss, tok, delimiter)) {
      if (i % 2 == 1) {
        col = stoi(tok) - 1;
      }
      else {
        row = stoi(tok) - 1;
        if (safe(board, n, row, col)) {
          board[row][col] = 1;
        }
        else {
          given_fair = false;
          break;
        }
      }
      i++;
    }

    vector<vector<int>> res = nqueens(board, n);
    if (res[0][0] == -1 || !given_fair) {
      //write "No Solution"
      outFile << "No solution" << endl;
    }
    else {
      //loop through columns and add "<col> <row>" to line
      string o = "";
      for (int i = 0; i < res[0].size(); i++) {
        for (int j = 0; j < res.size(); j++) {
          if (res[j][i] == 1) {
            string c = to_string(i + 1);
            string r = to_string(j + 1);
            string a = c + " " + r + " ";
            o = o + a;
          }
        }
      }
      outFile << o << endl;
    }
  }
  inFile.close();
  outFile.close();
  return 1;
}
