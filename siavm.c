#include <stdio.h>
#include <stdlib.h>
#include "fetch.c"
#include "execute.c"
#include "dispatch.c"
#include "store.c"

int readFile(char * fileName, unsigned char bytes[]) // This process is loading the memory.
{
  int i = 0;
  long fileLength;
  FILE * file = fopen(fileName, "rb"); // Open the file and read it in in binary mode.
  if(file == NULL)
    printf("There was an error reading the file %s\n", fileName);
  else {
    int c;
    while((c = fgetc(file)) != EOF)
      bytes[i++] = (unsigned char)c; // Populate the array.
  }
  return i; // Return the total number of bytes read.
}

int main(int argc, char** argv)
{
  unsigned char bytes[10000]; // Allocate 10000 bytes to the unsigned char array.

  // CPU Infrastructure
  int REGISTERS[16] = {0}; // 16 Registers
  int programCounter = 0; // Program Counter
  int OP1, OP2;
  int RESULT;
  unsigned char buffer[4];
  if(argc != 2)
    printf("Invalid amount of arguments.");

  else {
    int byteCount = readFile(argv[1], bytes);
    //printf("The number of bytes read were: %d\n", byteCount);
    int flag = 1;
    int reg = -1;
    while(flag)
    {
      fetch(bytes, &programCounter, &flag, buffer);
      printf("Current Instruction to Dispatch: %02x %02x %02x %02x\n", buffer[0], buffer[1], buffer[2], buffer[3]);
      printf("Program Counter = %d\n", programCounter);
      dispatch(buffer, &OP1, &OP2, REGISTERS, bytes, &reg, byteCount);
      execute(buffer, &OP1, &OP2, &RESULT, REGISTERS);
      store(buffer, &RESULT, REGISTERS, &reg, &programCounter);
      printf("The next byte is: %02x\n", bytes[programCounter]);

    }
  }
  return 0;
}

