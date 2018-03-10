#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
  ifstream programfile("program-example.txt");
  string line;
  int i = 1;

  while(getline(programfile, line)) {
    istringstream iss(line);
    cout << i << "  " << line << "\n";
    i ++;
  }

  programfile.close();

  return 0;
}
