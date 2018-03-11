#include <iostream>
#include <cstdio>
#include <cstring>//for strlen in lexer constructor
#include <map>


using namespace std;

class Token {
  private:
    int row;
    int column;
    char* type;
    char* lexeme;
  public:
    Token(int row, int column, char type[], char lexeme[]);
    void print();
};
Token::Token(int _row, int _column, char _type[], char _lexeme[]){
    row = _row;
    column = _column;
    type = _type;
    lexeme = _lexeme;
}
void Token::print(){
    cout << row << endl;
    cout << column << endl;
    cout << type << endl;
    cout << lexeme << endl;
}

class Lexer {
  private:
    // map<char*,char*>
    short row;
    short column;
    short numNonFinalsStates;
    short numCharacters;
    short indexFirstFinalState;
    char* availableCharacters;
    short numAvailableCharacters;
    short** dfa;
  public:
    Lexer();
    ~Lexer();
    short getNumNonFinalsStates();
    short getNumCharacters();
    short getIndexFirstFinalState();
    char* getAvailableCharacters();
    short getNumAvailableCharacters();
    short** getDfa();
    short transition(short state, short character);
    void printDfa();
    Token nextToken(char* str);
};
Lexer::Lexer(){
    this->row = 0;
    this->column = 0;

    numNonFinalsStates = 16;
    numCharacters = 128;
    indexFirstFinalState = 20;
    availableCharacters = "()[]{}*/%^#:,><=!&|+-.\" \tabcdefghijklmniopqrstuvwxyzABCDEFGHIJKLMNIOPQRSTUVWXYZ0123456789";
    numAvailableCharacters = (unsigned)strlen(availableCharacters);
    //  Initialize all matrix element with zero (0)
    dfa = new short*[numNonFinalsStates];
    for(short i=0; i<numNonFinalsStates; i++){
        dfa[i] = new short[numCharacters];
        for(short j=0; j< numCharacters; j++)
            dfa[i][j] = 0;
    }

    //  Unit tokens with unique match
    //  TODO:   Take it to any character loop
    for(short i=0; i<=12; i++)
        dfa[0][(short)availableCharacters[i]] = indexFirstFinalState;
    //  Mixed tokens with multiple matches consideration (Float number case #1: without a number before)
    for(short i=13; i<=21; i++)
      dfa[0][(short)availableCharacters[i]] = i-10;
    // dfa[0][(short)'\n'] = indexFirstFinalState+7;
    dfa[0][(short)' '] = 0;
    dfa[0][(short)'\t'] = 0;

    // Two element token match
    for(short i=1; i<=4; i++)
        dfa[i][(short)'='] = indexFirstFinalState+1;
    dfa[5][(short)'&'] = indexFirstFinalState+1;
    dfa[6][(short)'|'] = indexFirstFinalState+1;
    dfa[7][(short)'+'] = indexFirstFinalState+1;
    dfa[8][(short)'-'] = indexFirstFinalState+1;


    //  Float number (case #2 with a number before)
    dfa[11][(short)'.'] = 12;

    //  "Strings"
    dfa[0][(short)'\"'] = 14;
    for(short i=0; i<numCharacters; i++){
      if(i != (short)'\"'){
        dfa[14][i] = 15; // 14 --> 15 loop alphanumeric + ' '
        dfa[15][i] = 15;
      }else
        dfa[15][i] = indexFirstFinalState+6;
    }

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

    //  Any character loop
    short increment;
    for(short j=0; j<numAvailableCharacters; j++){
        //  Unit tokens with multiple match check
        for(short i=1; i<=13; i++){
            //  TODO: Check if [0-9]'.' map to an integer or a double number
            //  TODO: (11,12 -> 25),(12,13 -> 26)
            if(i==12) continue;
            if(dfa[i][(short)availableCharacters[j]] == 0){
                increment = (i<10? 2: i-7);
                // increment = (i>=10? i-5: 2);
                //  TODO:   Think about it when i==13
                if(i==13) increment--;
                dfa[i][(short)availableCharacters[j]] = indexFirstFinalState+increment;
            }
        }
    }
}
Lexer::~Lexer(){
    delete availableCharacters;
    for(short i=0; i<numAvailableCharacters; i++)
        delete dfa[i];
    delete dfa;
}
short Lexer::getNumNonFinalsStates(){ return numNonFinalsStates; }
short Lexer::getNumCharacters(){ return numCharacters; }
short Lexer::getIndexFirstFinalState(){ return indexFirstFinalState; }
char* Lexer::getAvailableCharacters(){ return availableCharacters; }
short Lexer::getNumAvailableCharacters(){ return numAvailableCharacters; }
short** Lexer::getDfa(){ return dfa; }
short Lexer::transition(short state, short character){ return dfa[state][character]; }
void Lexer::printDfa(){
    for(int i=0; i<numNonFinalsStates; i++){
        for(int j=10; j< numCharacters; j++){
            printf("%2i ",dfa[i][j]);// if(!((j+1)%10)) printf("\t");
        }
        printf("\n");
    }
}
// Token Lexer::nextToken(char* str){
//   short currentState = 0;
//   short i = 0;
//   while(true){  //  jkasaaasfaklsdf
//     currentState = transition(currentState, str[i])
//     switch (currentState) {
//       case 0:
//         printf("Se murió\n");
//         return NULL;
//       case indexFirstFinalState:
//         printf("Unit token");
//         // revisar hash con substring(0,i); // i ==1
//         char* tokenType = myhash(substr(str, 0, 1));
//         return Token token = new Token(row, column, tokenType, substr(str, 0, 1));
//         break;
//       case indexFirstFinalState+1:
//         printf("two characters token");
//         // revisar hash con substring(0,i); // i == 2
//         char* tokenType = myhash(substr(str, 0, 2));
//         Token token = new Token(row, column, tokenType, substr(str, 0, 1));
//         return afdkajlkl
//         break;
//       case indexFirstFinalState+2:
//         break;
//       case indexFirstFinalState+3:
//         break;
//       case indexFirstFinalState+4:
//         break;
//       case indexFirstFinalState+5:
//         break;
//       case indexFirstFinalState+6:
//         break;
//       case indexFirstFinalState+7:
//         column++;
//         break;
//       default:
//         i++;
//         break;
//     }
//   }
// }

int main(){
  Lexer* lexer = new Lexer();
  // lexer->printDfa();
  short a = lexer->getNumAvailableCharacters();
  char* b = lexer->getAvailableCharacters();
  cout << a << endl;
  for(int i=0; i<a; i++){
    cout << "i: " << i << " character " << b[i] << " int " << (int)b[i] << " " << lexer->transition(0,b[i]) << endl;
  }
  delete lexer;
  return 0;
}
