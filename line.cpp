#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void func(istream &input){
  string line;
  input >> line;
  // getline(input, line);
  cout << line;
}

int main() {
  ifstream programfile("program-example.txt");
  func(programfile);
  // string line;
  // int i = 1;

  // while(getline(programfile, line)) {
  //   istringstream iss(line);
  //   cout << i << "  " << line << "\n";
  //   i ++;
  // }

  programfile.close();

  return 0;
}
