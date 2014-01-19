#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
/*
List of Brainfuck symbols:
>  - increment data pointer
<  - decrement data pointer
+  - increment byte at data pointer
-  - decrement byte at data pointer
.  - output byte at data pointer
,  - accept one byte of input
[  - if byte at data pointer is zero, skip to next command after matching ], else next command after [
]  - if byte at data pointer is zero, next command, else next command after previous [
*/

class Brainfuck {
    char* instructionTape;
    char* dataTape;
    unsigned int dataPointer;
    unsigned int instrPointer;
  public:
    Brainfuck(const char* tape){
      instructionTape = new char[strlen(tape)];
      strcpy(instructionTape, tape);
      dataTape = new char[2000];
      memset(dataTape, 0, sizeof(char)*2000);
      
      dataPointer = 0;
      instrPointer = 0;
    }
    void interpret(char);
    void run();
};
  

void Brainfuck::interpret(char symbol){
  switch(symbol){
    case '>':
      dataPointer++;
      break;
    case '<':
      dataPointer--;
      break;
    case '+':
      dataTape[dataPointer]++;
      break;
    case '-':
      dataTape[dataPointer]--;
      break;
    case '.':
      putchar(dataTape[dataPointer]);
      break;
    case ',':
      dataTape[dataPointer] = getchar();
      break;
    case '[':        
      //TODO
      break;
    case ']':
      //TODO
      break;
    default: 
      cout << "Invalid symbol!" << endl;
      break;
  }
}

void Brainfuck::run(){
  cout << "Running interpreter..." << endl;
  while(instrPointer < strlen(instructionTape)){
    interpret(instructionTape[instrPointer]);
    instrPointer++;
  }
}

int main(int argc, char* argv[]){
  Brainfuck sth(">+++++++>++++++++++>+++>+<<<<>+++++++>++++++++++>+++>+<<<<>+++++++>++++++++++>+++>+<<<<>+++++++>++++++++++>+++>+<<<<>+++++++>++++++++++>+++>+<<<<>+++++++>++++++++++>+++>+<<<<>+++++++>++++++++++>+++>+<<<<>+++++++>++++++++++>+++>+<<<<>+++++++>++++++++++>+++>+<<<<>+++++++>++++++++++>+++>+<<<<>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.");
  
  sth.run();
  return 0;
}
