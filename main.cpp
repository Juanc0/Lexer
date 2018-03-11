#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

//  Compile with
//  g++ -std=c++0x main.cpp -o main


class Token{
private:
    int row;
    int column;
    string type;
    string lexeme;
public:
    Token(int row, int column, string type, string lexeme);
    string getType();
    void print();
};
Token::Token(int _row, int _column, string _type, string _lexeme){
    row = _row;
    column = _column;
    type = _type;
    lexeme = _lexeme;
}
void Token::print(){
  if (type == "rw")
    cout << "<" << lexeme << "," << row << "," << column << ">" << endl;
  else if (type == "token_string" || type == "token_integer" || type == "token_float" || type == "id")
    cout << "<" << type << "," << lexeme << "," << row << "," << column << ">" << endl;
  else
    cout << "<" << type << "," << row << "," << column << ">" << endl;
}
string Token::getType(){return type;}

class Lexer{
  private:
    short numNonFinalsStates;
    short numCharacters;
    short indexFirstFinalState;
    string availableCharacters;
    short numAvailableCharacters;
    short** dfa;
    long row;
    long column;
    string currentLine;
    unordered_map<string, string> tokenTypes;
    unordered_set<string> reservedWords;
  public:
    Lexer();
    ~Lexer();

    short getNumNonFinalsStates();
    short getNumCharacters();
    short getIndexFirstFinalState();
    string getAvailableCharacters();
    short getNumAvailableCharacters();
    short** getDfa();
    long getRow();
    long getColumn();
    string getCurrentLine();

    short transition(short state, short character);
    void printDfa();
    Token* nextToken(istream &programfile);
};
Lexer::Lexer(){
    numNonFinalsStates = 15;
    numCharacters = 128;
    indexFirstFinalState = 20;
    availableCharacters = "()[]{}*/%^#:;,_?><=!&|+-.\"\n\tabcdefghijklmniopqrstuvwxyzABCDEFGHIJKLMNIOPQRSTUVWXYZ0123456789";
    numAvailableCharacters = availableCharacters.length();
    //  Initialize all matrix element with zero (0)
    dfa = new short*[numNonFinalsStates];
    for(short i=0; i<numNonFinalsStates; i++){
        dfa[i] = new short[numCharacters];
        for(short j=0; j< numCharacters; j++)
            dfa[i][j] = 0;
    }

    row = 0;
    column = 0;
    currentLine = "";
    // ifstream programfile("program-example.txt");
    // is = programfile;
    // is = cin;

    //  Initialize tokenTypes hashmap
    tokenTypes.insert({
      {"{","token_llave_izq"},
      {"}","token_llave_der"},
      {"#","token_com"},
      {"[","token_cor_izq"},
      {"]","token_cor_der"},
      {"(","token_par_izq"},
      {")","token_par_der"},
      {">","token_mayor"},
      {"<","token_menor"},
      {">=","token_mayor_igual"},
      {"<=","token_menor_igual"},
      {"==","token_igual_num"},
      {".","token_point"},
      {"!=","token_dif_num"},
      {"&&","token_and"},
      {"||","token_or"},
      {"!","token_not"},
      {"+","token_mas"},
      {"++","token_add"},
      {"-","token_menos"},
      {"--","token_less"},
      {"*","token_mul"},
      {"/","token_div"},
      {"%","token_mod"},
      {"^","token_pot"},
      {"=","token_assign"},

      // these are not defined in the restrepo table
      {":","token_puntos"},
      {";","token_punto_coma"},
      {",","token_coma"},
      {"_","token_guion_bajo"}
    });
    //  Initialize reservedWords hashmap
    reservedWords.insert({
      {"end"},
      {"false"},
      {"for"},
      {"funcion"},
      {"if"},
      {"importar"},
      {"in"},
      {"log"},
      {"sqrt"},
      {"true"},
      {"retorno"},
      {"while"},
    });



    //  Unit tokens with unique match
    //  TODO:   Take it to any character loop
    for(short i=0; i<=15; i++)
        dfa[0][(short)availableCharacters[i]] = indexFirstFinalState;
    //  Mixed tokens with multiple matches consideration (Float number case #1: without a number before)
    for(short i=16; i<=23; i++)
        dfa[0][(short)availableCharacters[i]] = i-15;
    //  TODO: check this error -1 or 0
    dfa[0][(short)' '] = indexFirstFinalState+6;
    dfa[0][(short)'\t'] = indexFirstFinalState+6;

    // Two element token match
    for(short i=1; i<=4; i++)
        dfa[i][(short)'='] = indexFirstFinalState;
    dfa[5][(short)'&'] = indexFirstFinalState;
    dfa[6][(short)'|'] = indexFirstFinalState;
    dfa[7][(short)'+'] = indexFirstFinalState;
    dfa[8][(short)'-'] = indexFirstFinalState;

    //  Float number (case #2 with a number before)
    dfa[11][(short)'.'] = 12;

    //  "Strings"
    dfa[0][(short)'\"'] = 14;
    for(short i=0; i<numCharacters; i++)
        if(i != (short)'\"')
            dfa[14][i] = 14; // 14 --> 14 loop alphanumeric + ' '
        else
            dfa[14][i] = indexFirstFinalState+5;

    //  Alphabetical loop
    for(short i=65; i<=90; i++){
        dfa[0][i] = 10;
        dfa[0][i+32] = 10;
        dfa[10][i] = 10;
        dfa[10][i+32] = 10;
    }
    //  Numeric loop
    for(short i=48; i<=57; i++){
        dfa[0][i] = 11;
        dfa[11][i] = 11;
        dfa[10][i] = 10;
        dfa[9][i] = 13; // float without a number before
        dfa[12][i] = 13; // float with a number before
        dfa[13][i] = 13;
    }
    dfa[10][(short)'_'] = 15;
    dfa[10][(short)'-'] = 15;

    //  Any character loop
    short increment;
    for(short j=0; j<numAvailableCharacters; j++){
        //  Unit tokens with multiple match check
        for(short i=1; i<=13; i++){
            //  TODO: Check if [0-9]'.' map to an integer or a double number or error
            if(i==12 || i==5 || i== 6)continue;
            if(dfa[i][(short)availableCharacters[j]] == 0){
                increment = (i<10? 1: i-8);
                // increment = (i>=10? i-5: 2);
                //  TODO:   Think about it when i==13
                if(i==13)
                    increment--;
                dfa[i][(short)availableCharacters[j]] = indexFirstFinalState+increment;
            }
        }

    }

    for(int i=0; i<numNonFinalsStates; i++){
      if(i==12 || i==5 || i== 6)continue;
      if(dfa[i][0] == 0)
        increment = (i<10? 1: i-8);
      if(i==13)
          increment--;
      dfa[i][0] = indexFirstFinalState+increment;
    }

    for(int i=1; i<13; i++){
      if(i==12 || i==5 || i== 6)continue;
      if(dfa[i][(short)' '] == 0)
        increment = (i<10? 1: i-8);
      if(i==13)
          increment--;
      dfa[i][(short)' '] = indexFirstFinalState+increment;
    }
}
Lexer::~Lexer(){
    for(short i=0; i<numNonFinalsStates; i++)
        delete dfa[i];
    delete dfa;
}
string Lexer::getAvailableCharacters(){return availableCharacters;}
// unordered_map<string, string> Lexer::getTokenTypes(){return tokentypes;}
// unordered_set<string> Lexer::getReservedWords(){return reservedWords;}
short Lexer::transition(short state, short character){return dfa[state][character];}
void Lexer::printDfa(){
    for(int i=0; i<numNonFinalsStates; i++){
        for(int j=10; j< numCharacters; j++){
            printf("%2i ",dfa[i][j]);
            // if(!((j+1)%10)) printf("\t");
        }
        printf("\n");
    }
}
// Token* Lexer::nextToken(ifstream& ifs){
Token* Lexer::nextToken(istream &programfile){
  // ifstream programfile("program-example.txt");
  //  CurrentLine ckeck
  if(programfile.eof())
    return NULL;
  if(column == currentLine.length()){
    getline(programfile, currentLine);
    row++;
    column = 0;
  }

  //  find next token
  short currentState = 0;
  short i = 0;
  string tokenType;
  string lexeme;
  while(true){
    currentState = transition(currentState, (short)currentLine[column+i]);
    // cout << currentState << "\t" << currentLine[column+i] << "\t" << (int)currentLine[column+i] << endl;
    switch (currentState) {
      case 0:
        cout << ">>> Error lexico(linea:" << row << ",posicion:" << column+1 << ")" << endl;
        return NULL;
      case 24:
        //  Float number
        tokenType = "token_float";
        break;
      case 23:
        //  integer
        tokenType = "token_integer";
        break;
      case 22:
        //  identifiers <id, nombre, row, col>
        lexeme = currentLine.substr(column, i);
        tokenType = !lexeme.compare("in")? "token_in" : (
          reservedWords.find(lexeme) != reservedWords.end()? "rw" : "id"
        );
        break;
      case 21:
        //  tokens with an additional character
        i--;
      case 20:
        //  complete tokens (with one and two characters)
        lexeme = currentLine.substr(column, i+1);
        tokenType = tokenTypes[lexeme];
        // tokenType = tokenTypes.find(lexeme);

        if(currentLine[column] == '#'){
          if(programfile.eof())
            return NULL;
          Token* token = new Token(row, column+1, tokenType, lexeme);
          getline(programfile, currentLine);
          row++;
          column = 0;
          i=0;
          currentState = 0;
          continue;
        }

        i++;
        break;
      case 25:
        //  String
        tokenType = "token_string";
        i++;
        break;
      case 26:
        column++;
        currentState = 0;
        continue;
      default:
        i++;
        continue;
    }
    i--;
    lexeme = currentLine.substr(column, i+1);
    if(currentState == indexFirstFinalState+5)
      lexeme = currentLine.substr(column+1, i-1);

    Token* token = new Token(row, column+1, tokenType, lexeme);
    column += i+1;
    currentState = 0;
    return lexeme==""? NULL: token;
  }
}

int main(){
    ifstream programfile("program-example.txt");
    Lexer* lexer = new Lexer();

    // short a = lexer->getNumAvailableCharacters();
    // cout << a << endl;
    // string b = lexer->getAvailableCharacters();
    // cout << b << endl;

    Token* token;
    while((token = lexer->nextToken(programfile)) != NULL){
      token->print();
    }
    // for (int i = 0; i < 50; i++) {
    //   lexer->nextToken(programfile)->print();
    // }

    programfile.close();
    delete lexer;
    return 0;
}
