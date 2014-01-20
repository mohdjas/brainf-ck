#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <stack>
using namespace std;

class Brainfuck {
    char* instructionTape;
    char* dataTape;
    unsigned int dataPointer;
    unsigned int instrPointer;
    stack<unsigned int> brackets;
  public:
    Brainfuck(ifstream& tape){
      tape.seekg(0, tape.end);
      int length = tape.tellg();
      tape.seekg(0, tape.beg); //reset pointer to beginning of file
      instructionTape = new char[length];
      tape.read(instructionTape, length);
      
      dataTape = new char[2000];
      memset(dataTape, 0, sizeof(char)*2000);
      dataPointer = 0;
      instrPointer = 0;
    }
    
    Brainfuck(const char* tape){
      instructionTape = new char[strlen(tape)+1];
      strcpy(instructionTape, tape);

      dataTape = new char[2000];
      memset(dataTape, 0, sizeof(char)*2000);
      dataPointer = 0;
      instrPointer = 0;
    }
    void interpret(char);
    void run();
    void run(ifstream&);
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
      brackets.push(instrPointer);
      if (dataTape[dataPointer] == 0){
      /*
        Push the opening brackets onto the stack and
        if a closing bracket is encountered, pop it.
        This ensures that the current code block is 
        skipped entirely.        
      */
        while (!brackets.empty()){
          instrPointer++;
          if (instructionTape[instrPointer] == ']')
            brackets.pop();
          else if (instructionTape[instrPointer] == '[')
            brackets.push(instrPointer);
        }
      }
      break;
    case ']':
      /*
        We subtract 1 from the index because we
        increment it after each symbol is read.
      */
      if (dataTape[dataPointer] != 0){
        instrPointer = brackets.top() - 1;
      }
      brackets.pop();
      break;
    default: 
      break;
  }
}

void Brainfuck::run(){
  while(instrPointer < strlen(instructionTape)){
    interpret(instructionTape[instrPointer]);
    instrPointer++;
  }
  cout << endl;
}

int main(int argc, char* argv[]){
  ifstream bf_file (argv[1]);
  if (bf_file.is_open()){                 //is the argument a valid file input?
    Brainfuck obj(bf_file);
    obj.run();    
    bf_file.close();
    return 0;
  }
  else if (argv[1] != NULL){              //or is it a string?
    Brainfuck obj(argv[1]);
    obj.run();
    return 0;
  }
  cerr << "Error: please provide valid input or file-name." << endl;
  return -1;
}
