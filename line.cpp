#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
  ifstream programfile("program-example.txt");
  string line;
  int i = 1;

  while(getline(programfile, line)) {
    cout << i << "  " << line << "\n";
    i ++;
  }

  programfile.close();

  return 0;
}
