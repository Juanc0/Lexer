#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

void func(istream &input){
  string line;
  input >> line;
  // getline(input, line);
  cout << line;
}

int main() {
  // int a = 0x00A8;}
  wcout << (wchar_t)0x00A8 << endl;
  // wstring algo = L"asd¨fas";
  // wcout << algo << endl;
  // int iMax;
  // for(size_t i = 0, iMax = wcslen(algo); i < iMax; ++i){
  //    std::cout << " " << static_cast<unsigned int>(static_cast<unsigned short>(algo[i]));
  // }


  // ifstream programfile("program-example.txt");
  // func(programfile);
  // string line;
  // int i = 1;
  // while(getline(programfile, line)) {
  //   istringstream iss(line);
  //   cout << i << "  " << line << "\n";
  //   i ++;
  // }

  // programfile.close();

  return 0;
}
