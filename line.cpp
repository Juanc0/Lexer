#include <iostream>
#include <fstream>
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

<<<<<<< HEAD
  while(getline(programfile, line)) {
    cout << i << "  " << line << "\n";
    i ++;
  }
=======
  // while(getline(programfile, line)) {
  //   istringstream iss(line);
  //   cout << i << "  " << line << "\n";
  //   i ++;
  // }
>>>>>>> 4e32d0aac89711487acf2eb72697b3bee2442bd0

  programfile.close();

  return 0;
}
