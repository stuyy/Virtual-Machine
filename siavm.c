#include <stdio.h>
#include "vmlib.h"

int main(int argc, char** argv)
{
  unsigned char bytes[10000]; // Allocate 10000 bytes to the unsigned char array.

  // Create 16 registers.
  int registers[16];
  int programCounter = 0;
  int OP1, OP2, RES;

  if(argc != 2)
    printf("Invalid amount of arguments.");

  else {
    int byteCount = readFile(argv[1], bytes);
    printf("The number of bytes read were: %d\n", byteCount);
    int flag = 1;
    while(flag)
    {
      // Call Fetch.
      fetch(bytes, &programCounter);
      flag = 0;
      // Call Dispatch.

      // Call Execute.

      // Call Store.
    }
  }
  return 0;
}

int readFile(char * fileName, unsigned char bytes[]) // This process is loading the memory.
{
  int i = 0;
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

void fetch(unsigned char bytes[], int * pc) {

  int instruction = bytes[*byte] >> 4;
  switch(instruction)
  {
    case 0:
    break;
  }
}
